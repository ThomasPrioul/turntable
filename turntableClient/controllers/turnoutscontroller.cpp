#include "turnoutscontroller.h"
#include "turntableapplication.h"

TurnoutsController::TurnoutsController(TurntableApplication* appRef, QObject *parent)
    : QObject(parent)
    , IController(appRef)
{
    // Static cast to disambiguate between two method signatures
    //static_cast<void (TurntableApplication::*)(const std::string&)>(&TurntableApplication::messageReceived)
    connect(m_app,  &TurntableApplication::messageReceived,
            this,   &TurnoutsController::messageReceived);
}

void TurnoutsController::messageReceived(const std::string &msg)
{
}
