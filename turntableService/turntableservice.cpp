#include <iostream>
#include <QCommandLineParser>

#include "turntableservice.h"

CommandLineParseResult TurntableService::parseCommandLine(QCommandLineParser& parser)
{
    QHostAddress networkAddr(defaultIP);
    quint16 networkPort = defaultPort;
    int32_t nbSteps = defaultSteps;

    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();
    const QCommandLineOption ipOption("ip", "The IP address (and therefore the interface) to use.", "ip", QString(defaultIP));
    const QCommandLineOption portOption("port", "The port to use for TCP communication.", "port", QString::number(defaultPort));
    const QCommandLineOption stepsOption("steps", "The number of steps for the motor.", "steps", QString::number(defaultSteps));

    parser.addOptions({ ipOption, portOption, stepsOption });

    if (!parser.parse(QCoreApplication::arguments())) {
        qCritical() << parser.errorText();
        return CommandLineError;
    }

    if (parser.isSet(versionOption)) {
        parser.showVersion();
        return CommandLineVersionRequested;
    }
    if (parser.isSet(helpOption)) {
        parser.showHelp();
        return CommandLineHelpRequested;
    }
    if (parser.isSet(ipOption)) {
        const QString ipArg = parser.value(ipOption);
        if (!networkAddr.setAddress(ipArg)) {
            qCritical() << "Could not parse given IP address, using " << defaultIP << "as default.";
            return CommandLineError;
        }
    }
    if (parser.isSet(portOption)) {
        const QString portArg = parser.value(portOption);
        bool parseValid;
        int parsedPort = portArg.toInt(&parseValid);

        if (!parseValid) {
            qCritical() << "Could not parse given port number, using " << defaultPort << " as default.";
            return CommandLineError;
        }

        if (parsedPort < 1024 || parsedPort > UINT16_MAX) {
            qCritical() << "Given port number is out of bounds (1024 - 65535).";
            return CommandLineError;
        }

        networkPort = parsedPort;
    }
    if (parser.isSet(stepsOption)) {
        const QString stepsArg = parser.value(stepsOption);
        bool parseValid;
        int parsedSteps = stepsArg.toInt(&parseValid);

        if (!parseValid) {
            qCritical() << "Could not parse given steps amount, using " << defaultSteps << " as default.";
            return CommandLineError;
        }

        if (parsedSteps <= 0) {
            qCritical() << "Given port number is out of bounds (1024 - 65535).";
            return CommandLineError;
        }

        nbSteps = parsedSteps;
    }

    motor = new TurntableMotor(nbSteps, this);
    connect(motor, &TurntableMotor::movementNotify, this, &TurntableService::motorMoved);
    connect(motor, &TurntableMotor::movementStarted, this, &TurntableService::motorStarted);
    connect(motor, &TurntableMotor::movementStopped, this, &TurntableService::motorStopped);

    network = new TurntableNetwork(networkAddr, networkPort, this);
    connect(network, &TurntableNetwork::messageReceived, this, &TurntableService::messageReceived);
    connect(network, &TurntableNetwork::clientConnected, this, &TurntableService::clientConnected);
    connect(network, &TurntableNetwork::clientDisconnected, this, &TurntableService::clientDisconnected);

    return CommandLineOk;
}

int TurntableService::initialize(int argc, char *argv[]) {
    QHostAddress networkAddr(defaultIP);
    quint16 networkPort = defaultPort;
    int32_t nbSteps = defaultSteps;

    if (argc > 1) {
        int i = 1;

        // Process command line arguments
        do {
            // Display help
            if (strcasecmp(argv[i], "-h") == 0 ||
                strcasecmp(argv[i], "--help") == 0) {
                //displayHelp();
                return -1;
            }
            // Display version
            else if (strcasecmp(argv[i], "-v") == 0 ||
                     strcasecmp(argv[i], "--version") == 0) {
                std::cout << "0.1" << std::endl;
                return -1;
            }
            // Set IP
            else if (strcasecmp(argv[i], "--ip") == 0) {

                // Check that there is at least another arg to read
                if ((argc - 1) > i) {
                    if (networkAddr.setAddress(QString(argv[++i])))
                        std::cout << "IP Address set as " << argv[i] << std::endl;
                    else
                        std::cout << "Could not parse given IP address, \"" << argv[i] << "\", using " << defaultIP << " as default." << std::endl;
                }
                else {
                    std::cout << "IP address argument missing, usage is:" << std::endl <<
                                 "turntableservice --ip <ip>" << std::endl;
                }
            }
            // Set port
            else if (strcasecmp(argv[i], "--port") == 0) {
                // Check that there is at least another arg to read
                if ((argc - 1) >= i) {
                    QString portArg(argv[++i]);
                    bool conversionOk;
                    int convertedPort = portArg.toInt(&conversionOk);

                    if (conversionOk) {
                        if (convertedPort > 0 && convertedPort < UINT16_MAX) {
                            networkPort = convertedPort;
                            std::cout << "Port set as " << networkPort << std::endl;
                        }
                        else {
                            std::cout << "Given port number \"" << argv[i] << "\" is out of bounds (1024 - 65535)." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Could not parse given port number, \"" << argv[i] << "\", using port \"2017\" as default." << std::endl;
                    }
                }
                else {
                    std::cout << "Port rgument missing, usage is:" << std::endl <<
                                 "turntableservice --port <port>" << std::endl;
                }
            }
            // Set motor steps
            else if (strcasecmp(argv[i], "--steps") == 0) {
                // Check that there is at least another arg to read
                if ((argc - 1) >= i) {
                    QString stepsArg(argv[++i]);
                    bool conversionOk;
                    int convertedSteps = stepsArg.toInt(&conversionOk);

                    if (conversionOk) {
                        if (convertedSteps > 0) {
                            nbSteps = convertedSteps;
                            std::cout << "Steps set as " << nbSteps << std::endl;
                        }
                        else {
                            std::cout << "Can't have 0 steps." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Could not parse given steps number, \"" << argv[i] << "\", using " << defaultSteps << " as default." << std::endl;
                    }
                }
                else {
                    std::cout << "Steps argument missing, usage is:" << std::endl <<
                                 "turntableservice --steps <nbSteps>" << std::endl;
                }
            }
        } while (++i < argc);
    }

    motor = new TurntableMotor(nbSteps, this);
    connect(motor, &TurntableMotor::movementNotify, this, &TurntableService::motorMoved);
    connect(motor, &TurntableMotor::movementStarted, this, &TurntableService::motorStarted);
    connect(motor, &TurntableMotor::movementStopped, this, &TurntableService::motorStopped);

    network = new TurntableNetwork(networkAddr, networkPort, this);
    connect(network, &TurntableNetwork::messageReceived, this, &TurntableService::messageReceived);
    connect(network, &TurntableNetwork::clientConnected, this, &TurntableService::clientConnected);
    connect(network, &TurntableNetwork::clientDisconnected, this, &TurntableService::clientDisconnected);

    return 0;
    //motor.resetAsync();

    //connect(&updateTimer, &QTimer::timeout, this, &TurntableService::updateState);
    //updateTimer->start(1000);
}

void TurntableService::motorMoved(int32_t newPosition)
{
    qDebug() << "Motor pos = " << newPosition;
}

void TurntableService::motorStarted(int32_t startPosition)
{
    qDebug() << "Motor started moving";
    qDebug() << "Motor pos = " << startPosition;
}

void TurntableService::motorStopped(int32_t endPosition)
{
    qDebug() << "Motor pos = " << endPosition;
    qDebug() << "Motor stopped moving";

    if (state == ServiceState::Init) {
        state = ServiceState::AwaitingClient;
    }
}

void TurntableService::clientConnected()
{
    isClientConnected = true;
}

void TurntableService::clientDisconnected()
{
    isClientConnected = false;
}

void TurntableService::messageReceived(const QByteArray &message)
{
    QString strMsg(message);

    if (strMsg.startsWith("goto ")) {
        QTextStream reader(&strMsg);
        int32_t motorNewPosition;
        reader.seek(5);
        reader >> motorNewPosition;
        motor->goToPositionAsync(motorNewPosition);
    }
    else if (strMsg.startsWith("stop")) {
        motor->stop();
    }
    else if (strMsg.startsWith("reset")) {
        motor->resetAsync();
    }
}

//void TurntableService::updateState()
//{
//    switch(state) {
//        case ServiceState::AwaitingClient:
//            if (isClientConnected) {
//                state = ServiceState::ConnectedInit;
//            }
//            break;
//        case ServiceState::ConnectedIdle:
//            if (!isClientConnected) {
//                state = ServiceState::AwaitingClient;
//            }
//            break;
//    }
//}
