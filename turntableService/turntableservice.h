#ifndef TURNTABLESERVICE_H
#define TURNTABLESERVICE_H

#include <QCoreApplication>
#include "turntablenetwork.h"
#include "turntablemotor.h"

enum class ServiceState {
    Init,
    AwaitingClient,
    ConnectedInit,
    ConnectedIdle,
    ConnectedMoving
};

enum CommandLineParseResult
{
    CommandLineOk,
    CommandLineError,
    CommandLineVersionRequested,
    CommandLineHelpRequested
};

class TurntableService : public QCoreApplication
{
    Q_OBJECT

public:
    explicit TurntableService(int& argc, char** argv[]) : QCoreApplication(argc, *argv) {}

    //! Processes all command line arguments and initializes the application.
    CommandLineParseResult parseCommandLine(QCommandLineParser& parser);

    int initialize(int argc, char *argv[]);

private slots:
    // Motor slots
    void motorMoved(int32_t newPosition);
    void motorStarted(int32_t startPosition);
    void motorStopped(int32_t endPosition);

    // Network slots
    void clientConnected();
    void clientDisconnected();
    void messageReceived(const QByteArray &message);

private:
    static constexpr const char* defaultIP = "127.0.0.1";
    static constexpr quint16 defaultPort = 2017;
    static constexpr int32_t defaultSteps = 19200;

    bool isClientConnected;
    ServiceState state;
    TurntableNetwork* network;
    TurntableMotor* motor;
};

#endif // TURNTABLESERVICE_H
