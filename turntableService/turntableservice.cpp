#include <sstream>
#include <iostream>
#include <string>
#include <QCommandLineParser>
#include "turntableservice.h"
#include "networkconfig.h"

namespace query = NetworkConfig::Query;
namespace notif = NetworkConfig::Notification;

bool startsWithMsg(const std::string& str, const std::string& msgType)
{
    constexpr size_t a = 0;
    size_t b = msgType.length() - 1;
    return str.compare(a, b, msgType, a, b) == 0;
}

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
    QCoreApplication::setApplicationVersion("0.1");
}

AppInitResult TurntableService::initialize()
{
    QHostAddress networkAddr(NetworkConfig::defaultIP);
    quint16 networkPort = NetworkConfig::defaultPort;
    int32_t nbSteps = NetworkConfig::defaultSteps;
    QCommandLineParser parser;
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();
    const QCommandLineOption ipOption("ip", "The IP address (and therefore the interface) to use.", "ip", QString(NetworkConfig::defaultIP));
    const QCommandLineOption portOption("port", "The port to use for TCP communication.", "port", QString::number(NetworkConfig::defaultPort));
    const QCommandLineOption stepsOption("steps", "The number of steps for the motor.", "steps", QString::number(NetworkConfig::defaultSteps));

    parser.setApplicationDescription(R"(Turntable background service
Thomas Prioul
Polytech' Tours - 2017)");
    parser.addOptions({ ipOption, portOption, stepsOption });

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

    // Init sub-objects

    motor.setNbSteps(nbSteps);
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

    if (startsWith(msg, query::move)) {
        std::istringstream reader(msg);
        int32_t motorNewPosition;

        if (reader.seekg(query::move.length())) {
            if (reader >> motorNewPosition) {
                motor.goToPositionAsync(motorNewPosition);
            }
            else {
                std::cerr << "Failed to read position in message: " << msg << std::endl;
            }
        }
        else {
            std::cerr << "Could not find target motor position in message: " << msg << std::endl;
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
                output << notif::track << i.first << ';' << i.second << '\n';
            }
            output << notif::endSendConfig << '\n';
            network.sendMessage(output);
        }
    }
    else if (startsWith(msg, query::addTrack)) {
        std::istringstream reader(msg);
        std::string track;
        int32_t position;

        if (reader.seekg(query::addTrack.length())) {
            if (reader >> track >> position) {
                tracks.addTrack(track, position);

                if (isClientConnected) {
                    std::ostringstream output;
                    output << notif::addTrack << track << ';' << position << '\n';
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
    }
    else if (startsWith(msg, query::deleteTrack)) {
        std::istringstream reader(msg);
        std::string track;

        if (reader.seekg(query::deleteTrack.length())) {
            if (reader >> track) {
                tracks.deleteTrack(track);

                if (isClientConnected) {
                    std::ostringstream output;
                    output << notif::deleteTrack << track << '\n';
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
    }
}

void TurntableService::motorMovementNotification(int32_t newPosition)
{
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::position << newPosition << '\n';
        network.sendMessage(output);
    }
    std::cout << "Motor pos = " << newPosition << std::endl;
}

void TurntableService::motorMovementStarted(int32_t startPosition)
{
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::moveStarted << '\n' <<
                  notif::position << startPosition << '\n';
        network.sendMessage(output);
    }
    std::cout << "Motor started moving" << '\n';
    std::cout << "Motor pos = " << startPosition << '\n';
}

void TurntableService::motorMovementStopped(int32_t endPosition)
{
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::position << endPosition << '\n' <<
                  notif::moveStopped << '\n';
        network.sendMessage(output);
    }

    std::cout << "Motor pos = " << endPosition << '\n';
    std::cout << "Motor stopped moving" << std::endl;
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
    if (isClientConnected) {
        std::ostringstream output;
        output << notif::resetStopped << (int)success << '\n';
        network.sendMessage(output);
    }
}

/*
void TurntableService::updateState()
{
    switch(state) {
        case ServiceState::AwaitingClient:
            if (isClientConnected) {
                state = ServiceState::ConnectedInit;
            }
            break;
        case ServiceState::ConnectedIdle:
            if (!isClientConnected) {
                state = ServiceState::AwaitingClient;
            }
            break;
    }
}
*/
