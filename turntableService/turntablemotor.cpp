#include <wiringPi.h>
#include <iostream>
#include "turntablemotor.h"

constexpr int pin_enable =  13;
constexpr int pin_step = 26;
constexpr int pin_dir = 19;
constexpr int pin_zeroSensor = 21;
constexpr int notifyThreshold = 64;
constexpr unsigned long stepWaitTime = 3;
constexpr bool defaultDirection = true;

template<typename R>
bool is_ready(std::future<R> const& f)
{
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

inline static void enableMotor()
{
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});
    digitalWrite(pin_enable, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});
}

inline static void disableMotor()
{
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});
    digitalWrite(pin_enable, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});
}

inline static void setMotorDirection(bool dir)
{
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});
    digitalWrite(pin_dir, (int)dir);
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});
}

inline static bool getZeroSensorState()
{
    return !((bool)digitalRead(pin_zeroSensor));
}

TurntableMotor::TurntableMotor(QObject *parent) : QObject(parent)
{
    // Use BCM numbering instead of WiringPi numbering
    wiringPiSetupGpio();

    // Setup GPIO
    pinMode(pin_enable, OUTPUT); // PIN_ENABLE
    pinMode(pin_step, OUTPUT); // PIN_STEP
    pinMode(pin_dir, OUTPUT); // PIN_DIR
    pinMode(pin_zeroSensor, INPUT);

    disableMotor();
    digitalWrite(pin_step, 0);
    digitalWrite(pin_dir, defaultDirection);
}

TurntableMotor::~TurntableMotor()
{
    disableMotor();
}

void TurntableMotor::setNbSteps(int32_t numberOfSteps)
{
    // Calculate constants
    nb_steps = numberOfSteps;
    half_steps = nb_steps / 2;
    minus_half_steps = -1 * half_steps;
    max_pos = nb_steps - 1;
}

void TurntableMotor::goToPositionAsync(int32_t endPosition)
{
    if (!worker.valid() || is_ready(worker)) {
        worker = std::async(std::launch::async, &TurntableMotor::goToPositionWorker, this, endPosition);
    }
    else {
        std::cout << "A worker is already running!" << std::endl;
    }
}

void TurntableMotor::moveIndefinitelyAsync(bool direction)
{
    if (!worker.valid() || is_ready(worker)) {
        worker = std::async(std::launch::async, &TurntableMotor::moveIndefinitelyWorker, this, direction);
    }
    else {
        std::cout << "A worker is already running!" << std::endl;
    }
}

void TurntableMotor::resetAsync()
{   
    if (!worker.valid() || is_ready(worker)) {
        worker = std::async(std::launch::async, &TurntableMotor::resetWorker, this);
    }
    else {
        std::cout << "A worker is already running!" << std::endl;
    }
}

void TurntableMotor::stop()
{
    if (worker.valid()) {
        keepRunning = false;
        //worker.get();
    }
}

int32_t TurntableMotor::oneStep(bool direction)
{
    if (direction && ++currentPos >= nb_steps) {
        currentPos = 0;
    }
    else if (!direction && --currentPos < 0)
        currentPos = max_pos;

    digitalWrite(pin_step, 1);

    // Wait time
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});

    digitalWrite(pin_step, 0);

    // Wait time
    std::this_thread::sleep_for(std::chrono::milliseconds{stepWaitTime});

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
    int32_t steps = 0;
    int32_t notifySteps = 0;

    while (keepRunning && (currentPos != endPosition) && steps < nb_steps) {
        oneStep(direction);

        // Only notify every X steps
        if (notifySteps++ >= notifyThreshold) {
            emit movementNotify(currentPos);
            notifySteps = 0;
        }
    }

    disableMotor();
    emit movementStopped(currentPos);
}

void TurntableMotor::moveIndefinitelyWorker(bool direction)
{
    emit movementStarted(currentPos);
    enableMotor();
    setMotorDirection(direction);
    int32_t notifySteps = 0;

    keepRunning = true;

    while (keepRunning) {
        oneStep(direction);

        // Only notify every X steps
        if (notifySteps++ >= notifyThreshold) {
            emit movementNotify(currentPos);
            notifySteps = 0;
        }
    }

    disableMotor();
    emit movementStopped(currentPos);
}

void TurntableMotor::resetWorker()
{
    bool success = true;
    emit resetStarted();
    enableMotor();

    // Arbitrary direction
    setMotorDirection(defaultDirection);

    int32_t steps = 0;
    int32_t notifySteps = 0;

    while (!getZeroSensorState() && steps++ < nb_steps) {
        oneStep(defaultDirection);

        // Only notify every X steps
        if (notifySteps++ >= notifyThreshold) {
            emit movementNotify(currentPos);
            notifySteps = 0;
        }
    }

    // Zero wasn't found
    if (steps >= nb_steps) {
        std::cerr << "Could not find position 0" << std::endl;
        success = false;
    }
    else {
        currentPos = 0;
    }

    disableMotor();
    emit resetStopped(success);
}
