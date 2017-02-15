#include "turntableapplication.h"
#include "depotcontroller.h"

DepotController::DepotController(TurntableApplication *appRef, QObject *parent)
    : QObject(parent)
    , IController(appRef)
{
    connect(m_app,  &TurntableApplication::messageReceived,
            this,   &DepotController::messageReceived);
}

void DepotController::messageReceived(const std::string &msg)
{

}
