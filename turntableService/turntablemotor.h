#ifndef TURNTABLEMOTOR_H
#define TURNTABLEMOTOR_H

#include <QObject>

#ifdef RPI_FIX
    #include <QFutureWatcher>
#else
    #include <future>
#endif

/*!
 * Controls the Turntable's motor.
 * The implementation uses the wiringPi library.
 */
class TurntableMotor : public QObject
{
    Q_OBJECT

public:
    explicit TurntableMotor(QObject *parent = 0);
    ~TurntableMotor();

    int32_t pos() const { return currentPos; }
    int32_t steps() const { return nb_steps; }

    //! Sets the number of steps for the motor. This calculates the necessary constants used in other functions.
    void setNbSteps(int32_t numberOfSteps);

signals:
    //! This event is emitted at the start of a movement request.
    void movementStarted(int32_t position);

    //! This event is emitted at repeated intervals during movement, to help clients keep track of the current position.
    void movementNotify(int32_t position);

    //! This event is emitted whenever a movement stops on the turntable.
    void movementStopped(int32_t position);

    //! This event is emitted at the start of a reset.
    void resetStarted();

    //! This event is emitted at the end of a reset.
    void resetStopped(bool success);

public slots:
    //! Command handler for 'go to position' message.
    void goToPositionAsync(int32_t endPosition);

    //! Command handler for 'move' message.
    void moveIndefinitelyAsync(bool direction);

    //! Command handler for 'find zero' message.
    void resetAsync();

    //! Command handler for 'stop' message.
    void stop();

private:
    // Motor constants
    int32_t nb_steps;// = 19200;
    int32_t max_pos;// = nb_steps - 1;
    int32_t half_steps;// = nb_steps / 2;
    int32_t minus_half_steps;// = -1 * half_steps;

    //! Current motor step
    int32_t currentPos = 0;

    // Helper methods

    //! Performs one motor step in the required direction. This method assumes that the motor has already been enabled. Returns the new position.
    int32_t oneStep(bool direction);

    //! Calculates the shortest direction for the turntable, given A and B.
    bool shortestDirection(int32_t endPosition);

    //! Task watcher, different from null when a task is running.

#ifdef RPI_FIX
    QFutureWatcher<void> worker;
#else
    std::future<void> worker;
#endif
    //! Task cancellation bool
    volatile bool keepRunning;

    //! Motor 'go to' worker method. This should be used in a separate thread.
    void goToPositionWorker(qint32 endPosition);

    //! Motor 'move' worker method. This should be used in a separate thread.
    void moveIndefinitelyWorker(bool direction);

    //! Motor reset worker method (finding 0 position). This should be used in a separate thread.
    void resetWorker();
};

#endif // TURNTABLEMOTOR_H
