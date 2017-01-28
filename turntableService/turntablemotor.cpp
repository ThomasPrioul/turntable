#include <iostream>
#include <QtConcurrent>
#include <QElapsedTimer>

#include <wiringPi.h>
#include "turntablemotor.h"

constexpr int pin_enable =  13;
constexpr int pin_step = 26;
constexpr int pin_dir = 19;
constexpr int pin_zeroSensor = 21;
constexpr int notifyThreshold = 64;
constexpr unsigned long stepTime = 3;

static constexpr bool default_dir = true;

inline static void enableMotor()
{
    digitalWrite(pin_enable, 0);
}

inline static void disableMotor()
{
    digitalWrite(pin_enable, 1);
}

inline static void setMotorDirection(bool dir)
{
    digitalWrite(pin_dir, (int)dir);
}

inline static bool getZeroSensorState()
{
    return !((bool)digitalRead(pin_zeroSensor));
}

TurntableMotor::TurntableMotor(int32_t numberOfSteps, QObject *parent) : QObject(parent)
{
    // Calculate constants
    nb_steps = numberOfSteps;
    half_steps = nb_steps / 2;
    minus_half_steps = -1 * half_steps;
    max_pos = nb_steps - 1;

    // Necessary for workerWatcher->setFuture to work.
    qRegisterMetaType<int32_t>("int32_t");

    // Use BCM numbering instead of WiringPi numbering
    wiringPiSetupGpio();

    // Setup GPIO
    pinMode(pin_enable, OUTPUT); // PIN_ENABLE
    pinMode(pin_step, OUTPUT); // PIN_STEP
    pinMode(pin_dir, OUTPUT); // PIN_DIR
    pinMode(pin_zeroSensor, INPUT);

    disableMotor();
    digitalWrite(pin_step, 0);
    digitalWrite(pin_dir, default_dir);
}

TurntableMotor::~TurntableMotor()
{
    disableMotor();
}

void TurntableMotor::goToPositionAsync(int32_t endPosition)
{
    if (workerWatcher == Q_NULLPTR) {
        workerWatcher = new QFutureWatcher<void>();
        connect(workerWatcher, &QFutureWatcher<void>::finished, this, &TurntableMotor::workerDone);
        connect(workerWatcher, &QFutureWatcher<void>::finished, workerWatcher, &QObject::deleteLater);
        workerWatcher->setFuture(QtConcurrent::run(this, &TurntableMotor::goToPositionWorker, endPosition));
    }
    else {
        qDebug() << "A worker is already running!";
    }
}

void TurntableMotor::resetAsync()
{
    if (workerWatcher == Q_NULLPTR) {
        workerWatcher = new QFutureWatcher<void>();
        connect(workerWatcher, &QFutureWatcher<void>::finished, this, &TurntableMotor::workerDone);
        connect(workerWatcher, &QFutureWatcher<void>::finished, workerWatcher, &QObject::deleteLater);
        workerWatcher->setFuture(QtConcurrent::run(this, &TurntableMotor::resetWorker));
    }
    else {
        qDebug() << "A worker is already running!";
    }
}

void TurntableMotor::stop()
{
    if (workerWatcher != Q_NULLPTR) {
        keepRunning = false;
        workerWatcher->waitForFinished();
    }
}

int32_t TurntableMotor::oneStep(bool direction)
{
    if (direction) {
        if (++currentPos >= nb_steps)
            currentPos = 0;
    }
    else {
        if (--currentPos < 0)
            currentPos = max_pos;
    }

    digitalWrite(pin_step, 1);

    // Wait time
    QThread::msleep(stepTime);

    digitalWrite(pin_step, 0);

    // Wait time
    QThread::msleep(stepTime);

    return currentPos;
}

bool TurntableMotor::shortestDirection(int32_t endPosition)
{
    int32_t diff = endPosition - currentPos;

    if (diff < 0)
        return diff <= (-1 * half_steps);
    else
        return diff < half_steps;
}

void TurntableMotor::goToPositionWorker(qint32 endPosition)
{
    if (endPosition < 0 || endPosition > max_pos)
        return;

    emit movementStarted(currentPos);
    enableMotor();

    bool direction = shortestDirection(endPosition);
    setMotorDirection(direction);

    keepRunning = true;
    uint8_t steps = 0;

    while (keepRunning && (currentPos != endPosition) && steps < nb_steps) {
        oneStep(direction);

        // Notify every X steps
        if ((++steps % notifyThreshold) == 0)
            emit movementNotify(currentPos);
    }

    disableMotor();
    emit movementStopped(currentPos);
}

void TurntableMotor::resetWorker()
{
    emit movementStarted(currentPos);
    enableMotor();

    // Arbitrary direction
    setMotorDirection(default_dir);

    uint32_t steps = 0;
    while (!getZeroSensorState() && steps++ < nb_steps) {
        oneStep(default_dir);

        // Only notify every X steps
        if ((steps % notifyThreshold) == 0)
            emit movementNotify(currentPos);
    }

    // Zero wasn't found
    if (steps >= nb_steps) {
        std::cerr << "Could not find position 0" << std::endl;
    }

    currentPos = 0;
    disableMotor();
    emit movementStopped(currentPos);
}

void TurntableMotor::workerDone()
{
    disconnect(workerWatcher, &QFutureWatcher<void>::finished, this, &TurntableMotor::workerDone);
    workerWatcher = Q_NULLPTR;
}
