#ifndef TURNTABLESERVICE_H
#define TURNTABLESERVICE_H

#include <QCoreApplication>
#include "turntablenetwork.h"
#include "turntablemotor.h"
#include "turntabletracks.h"

//! Possible results for Application initialization method
enum class AppInitResult
{
    Ok,
    Error,
    VersionRequested,
    HelpRequested
};

/*!
    \class TurntableService
    \brief The TurntableService class represents the core object of the turntable service application.

    This class manages command line argument parsing, as well as initialization and linking between its submodules.
    For example, the class will capture the motor events to send appropriate network messages.
*/
class TurntableService : public QCoreApplication
{
    Q_OBJECT

public:
    // Pass argc and argv by reference or a segfault will happen when calling QCoreApplication::arguments() in initialize().
    explicit TurntableService(int& argc, char** argv[]);

    //! Processes all command line arguments and initializes the application.
    AppInitResult initialize();

private slots:
    // Network event handlers
    void clientConnected();
    void clientDisconnected();
    void messageReceived(const std::vector<char> &rawMessage);

    // Motor event handlers
    void motorMovementNotification(int32_t newPosition);
    void motorMovementStarted(int32_t startPosition);
    void motorMovementStopped(int32_t endPosition);
    void motorResetStarted();
    void motorResetStopped(bool success);

private:
    bool isClientConnected;   
    void checkPolarity();
    TurntableMotor motor;
    TurntableNetwork network;
    TurntableTracks tracks;
    void catchUnixSignals(const std::vector<int>& quitSignals, const std::vector<int>& ignoreSignals = std::vector<int>());
};

#endif // TURNTABLESERVICE_H
