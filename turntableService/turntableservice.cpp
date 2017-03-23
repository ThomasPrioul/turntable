#include <sstream>
#include <iostream>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <QCommandLineParser>
#include <QtGlobal>
#include "turntableservice.h"
#include "networkconfig.h"

namespace query = NetworkConfig::Query;
namespace notif = NetworkConfig::Notification;

bool startsWith(const std::string& longStr, const std::string& shortStr)
{
    return shortStr.length() <= longStr.length()
        && std::equal(shortStr.begin(), shortStr.end(), longStr.begin());
}

TurntableService::TurntableService(int& argc, char** argv[])
  : QCoreApplication(argc, *argv)
  , motor(this)
  , network(this)
{
    QCoreApplication::setApplicationName("turntableservice");
    QCoreApplication::setOrganizationName("Thomas Prioul - Polytech' Tours");
    QCoreApplication::setApplicationVersion("0.1");

    catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
}

AppInitResult TurntableService::initialize()
{
    QHostAddress networkAddr(NetworkConfig::defaultIP);
    quint16 networkPort = NetworkConfig::defaultPort;
    int32_t nbSteps = NetworkConfig::defaultSteps;
    bool motorReverse = false;
    int32_t motorTrackPolarityThreshold = 9500;

    QCommandLineParser parser;
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();
    const QCommandLineOption ipOption("ip", "The IP address (and therefore the interface) to use.", "ip", QString(NetworkConfig::defaultIP));
    const QCommandLineOption portOption("port", "The port to use for TCP communication.", "port", QString::number(NetworkConfig::defaultPort));
    const QCommandLineOption stepsOption("steps", "The number of steps for the motor.", "steps", QString::number(NetworkConfig::defaultSteps));
    const QCommandLineOption reverseOption("reverse", "Invert the motor's direction.");
    const QCommandLineOption polarityOption("polaritySwitch", "Invert the polarity at the specified position in steps", "polaritySwitch", QString::number(9500));

    parser.setApplicationDescription(R"(Turntable background service
Thomas Prioul
Polytech' Tours - 2017)");
    parser.addOptions({ ipOption, portOption, stepsOption, reverseOption, polarityOption });

    if (!parser.parse(QCoreApplication::arguments())) {
        std::cerr << parser.errorText().toStdString();
        return AppInitResult::Error;
    }

    // Check args

    if (parser.isSet(versionOption)) {
        parser.showVersion();
        return AppInitResult::VersionRequested;
    }

    if (parser.isSet(helpOption)) {
        parser.showHelp();
        return AppInitResult::HelpRequested;
    }

    if (parser.isSet(ipOption)) {
        const QString ipArg = parser.value(ipOption);
        if (!networkAddr.setAddress(ipArg)) {
            std::cerr << "Could not parse given IP address, using " << NetworkConfig::defaultIP << "as default." << std::endl;
            return AppInitResult::Error;
        }
    }

    if (parser.isSet(portOption)) {
        const QString portArg = parser.value(portOption);
        bool parseValid;
        int parsedPort = portArg.toInt(&parseValid);

        if (!parseValid) {
            std::cerr << "Could not parse given port number, using " << NetworkConfig::defaultPort << " as default." << std::endl;
            return AppInitResult::Error;
        }

        if (parsedPort < 1024 || parsedPort > UINT16_MAX) {
            std::cerr << "Given port number is out of bounds (1024 - 65535)." << std::endl;
            return AppInitResult::Error;
        }

        networkPort = parsedPort;
    }

    if (parser.isSet(stepsOption)) {
        const QString stepsArg = parser.value(stepsOption);
        bool parseValid;
        int parsedSteps = stepsArg.toInt(&parseValid);

        if (!parseValid) {
            std::cerr << "Could not parse given steps amount, using " << NetworkConfig::defaultSteps << " as default." << std::endl;
            return AppInitResult::Error;
        }

        if (parsedSteps <= 0) {
            std::cerr << "Given steps number cannot be negative." << std::endl;
            return AppInitResult::Error;
        }

        nbSteps = parsedSteps;
    }

    if (parser.isSet(polarityOption)) {
        const QString polarityArg = parser.value(polarityOption);
        bool parseValid;
        int parsedThreshold = polarityArg.toInt(&parseValid);

        if (!parseValid) {
            std::cerr << "Could not parse given polarity threshold, using " << 9500 << " as default." << std::endl;
            return AppInitResult::Error;
        }

        motorTrackPolarityThreshold = parsedThreshold;
    }

    if (parser.isSet(reverseOption)) {
        motorReverse = true;
    }

    // Init sub-objects

    motor.setNbSteps(nbSteps);
    motor.setReverse(motorReverse);
    motor.setPolarityThreshold(motorTrackPolarityThreshold);
    connect(&motor, &TurntableMotor::movementNotify, this, &TurntableService::motorMovementNotification);
    connect(&motor, &TurntableMotor::movementStarted, this, &TurntableService::motorMovementStarted);
    connect(&motor, &TurntableMotor::movementStopped, this, &TurntableService::motorMovementStopped);
    connect(&motor, &TurntableMotor::resetStarted, this, &TurntableService::motorResetStarted);
    connect(&motor, &TurntableMotor::resetStopped, this, &TurntableService::motorResetStopped);

    if (!network.start(networkAddr, networkPort))
        return AppInitResult::Error;

    connect(&network, &TurntableNetwork::messageReceived, this, &TurntableService::messageReceived);
    connect(&network, &TurntableNetwork::clientConnected, this, &TurntableService::clientConnected);
    connect(&network, &TurntableNetwork::clientDisconnected, this, &TurntableService::clientDisconnected);

    if (!tracks.loadFile())
        return AppInitResult::Error;

    // Reset on init
    std::cout << "App init : resetting turntable" << std::endl;
    motor.resetAsync();
    std::cout << "Init OK" << std::endl;
    std::cout << "Steps: " << nbSteps << std::endl;
    std::cout << "ReverseDir: " << (motorReverse ? "yes" : "no") << std::endl;
    std::cout << "Polarity treshold: " << motorTrackPolarityThreshold << std::endl;

    return AppInitResult::Ok;
}

void TurntableService::clientConnected()
{
    isClientConnected = true;
}

void TurntableService::clientDisconnected()
{
    isClientConnected = false;
}

void TurntableService::messageReceived(const std::vector<char> &rawMessage)
{
    std::string msg(rawMessage.begin(), rawMessage.end());

#ifdef QT_DEBUG
    std::cout << "Recu: " << msg << std::endl;
#endif

    if (startsWith(msg, query::move)) {
        std::istringstream reader(msg);

        if (startsWith(msg, query::moveToTrack)) {
            std::string trackName;
            int32_t position;

            // Handle move to track
            if (reader.seekg(query::moveToTrack.length() + 1)) {
                if (std::getline(std::getline(reader, trackName, '"'), trackName, '"') && (position = tracks.getTrackPosition(trackName)) != -1) {
                    motor.goToPositionAsync(position);
                }
                else {
                    std::cerr << "Failed to read trackname in message: " << msg << std::endl;
                }
            }
            else {
                std::cerr << "Could not find track name in message: " << msg << std::endl;
            }
        }
        else if (startsWith(msg, query::moveToPosition)) {
            int32_t position;

            // Handle move to position
            if (reader.seekg(query::moveToPosition.length())) {
                if (reader >> position) {
                    motor.goToPositionAsync(position);
                }
                else {
                    std::cerr << "Failed to read position in message: " << msg << std::endl;
                }
            }
            else {
                std::cerr << "Could not find target motor position in message: " << msg << std::endl;
            }
        }
        else {
            int32_t direction = true;
            reader.seekg(query::move.length());
            reader >> direction;
            motor.moveIndefinitelyAsync((bool)direction);
        }
    }
    else if (startsWith(msg, query::stop)) {
        motor.stop();
    }
    else if (startsWith(msg, query::reset)) {
        motor.resetAsync();
    }
    else if (startsWith(msg, query::position)) {
        if (isClientConnected) {
            std::ostringstream output;
            output << notif::position << motor.pos() << '\n';
            network.sendMessage(output);
        }
    }
    else if (startsWith(msg, query::sendConfig)) {
        if (isClientConnected) {
            std::ostringstream output;
            output << notif::beginSendConfig << '\n';
            for (auto i : tracks.getTracks()) {
                int relay = 0;
                if (i.second.polarity)
                    relay = 1;
                output << notif::trackDefinition << '"' << i.first << "\" " << i.second.position << " " << relay <<'\n';
            }
            output << notif::endSendConfig << '\n';
            network.sendMessage(output);
        }
    }
    else if (startsWith(msg, query::nbSteps)) {
        if (isClientConnected) {
            std::ostringstream output;
            output << notif::nbSteps << ' ' << motor.steps() << '\n';
            network.sendMessage(output);
        }
    }
    else if (startsWith(msg, query::polarity)) {
        if (isClientConnected) {
            std::ostringstream output;
            output << notif::polarity << ' ' << (bool)motor.polarity() << '\n';
            network.sendMessage(output);
        }
    }
    else if (startsWith(msg, query::addTrack)) {
        std::istringstream reader(msg);
        std::string track;
        int32_t position;
        bool polarity;

        if (reader.seekg(query::addTrack.length())) {
            if (std::getline(std::getline(reader, track, '"'), track, '"') >> position >> polarity) {
                tracks.addTrack(track, position, polarity);

                if (isClientConnected) {
                    std::ostringstream output;
                    output << notif::addTrack << '"' << track << "\" " << position << " " << polarity << '\n';
                    network.sendMessage(output);
                }
            }
            else {
                std::cerr << "Could not parse track name or position in message: " << msg << std::endl;
            }
        }
        else {
            std::cerr << "Could not find arguments in message: " << msg << std::endl;
        }

        checkPolarity();
    }
    else if (startsWith(msg, query::deleteTrack)) {
        std::istringstream reader(msg);
        std::string track;

        if (reader.seekg(query::deleteTrack.length())) {
            if (std::getline(std::getline(reader, track, '"'), track, '"')) {
                tracks.deleteTrack(track);

                if (isClientConnected) {
                    std::ostringstream output;
                    output << notif::deleteTrack<< '"' << track << "\"\n";
                    network.sendMessage(output);
                }
            }
            else {
                std::cerr << "Could not parse track name in message: " << msg << std::endl;
            }
        }
        else {
            std::cerr << "Could not find arguments in message: " << msg << std::endl;
        }

        checkPolarity();
    }
}

void TurntableService::motorMovementNotification(int32_t newPosition)
{
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::position << newPosition << '\n';
        network.sendMessage(output);
    }
#ifdef QT_DEBUG
    std::cout << "Motor pos = " << newPosition << std::endl;
#endif
}

void TurntableService::motorMovementStarted(int32_t startPosition)
{
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::moveStarted << '\n' <<
                  notif::position << startPosition << '\n';
        network.sendMessage(output);
    }
#ifdef QT_DEBUG
    std::cout << "Motor started moving" << '\n';
    std::cout << "Motor pos = " << startPosition << '\n';
#endif
}

void TurntableService::motorMovementStopped(int32_t endPosition)
{
    checkPolarity();

    if (isClientConnected) {
        std::ostringstream output;
        output << notif::position << endPosition << '\n' <<
                  notif::moveStopped << '\n';
        network.sendMessage(output);
    }
#ifdef QT_DEBUG
    std::cout << "Motor pos = " << endPosition << '\n';
    std::cout << "Motor stopped moving" << std::endl;
#endif
}

void TurntableService::motorResetStarted()
{
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::resetStarted << '\n';
        network.sendMessage(output);
    }
}

void TurntableService::motorResetStopped(bool success)
{
    checkPolarity();

    if (isClientConnected) {
        std::ostringstream output;
        output << notif::resetStopped << (int)success << '\n';
        network.sendMessage(output);
    }
}

void TurntableService::checkPolarity()
{
    // Check polarity
    TrackPolarity pol = TrackPolarity::Normal;

    // 1st : verify threshold
    if (motor.pos() >= motor.polarityThreshold()) {
        pol = TrackPolarity::Inverted;
        std::cout << "Switching relay to inverted because >= threshold" << std::endl;
    }
    else {
        std::cout << "Switching relay to normal because < threshold" << std::endl;
    }

    // 2nd: check if in front of a track
    for (auto i : tracks.getTracks()) {
        if (i.second.position == motor.pos() && i.second.polarity == false) {
            pol = (pol == TrackPolarity::Inverted ? TrackPolarity::Normal : TrackPolarity::Inverted);
            std::cout << "Switching relay again because aligned with an inverted track." << std::endl;
            break;
        }
    }

    std::cout << "Polarity = " << (pol == TrackPolarity::Normal ? "Normal" : "Inverted") << std::endl;
    motor.setPolarity(pol);
}

// https://gist.github.com/azadkuh/a2ac6869661ebd3f8588
void TurntableService::catchUnixSignals(const std::vector<int>& quitSignals, const std::vector<int>& ignoreSignals)
{
    auto handler = [](int sig) -> void {
        std::cout << '\n' << "quit the application (user request signal = " << sig << ')' << std::endl;
        QCoreApplication::quit();
    };

    // all these signals will be ignored.
    for (int sig : ignoreSignals)
        signal(sig, SIG_IGN);

    // each of these signals calls the handler (quits the QCoreApplication).
    for (int sig : quitSignals) {
        network.quit();
        signal(sig, handler);
    }
}
