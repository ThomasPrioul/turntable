#include "turntableapplication.h"
#include "lococontroller.h"

LocoController::LocoController(TurntableApplication *appRef, QObject *parent)
    : QObject(parent)
    , IController(appRef)
{
    connect(m_app,  &TurntableApplication::messageReceived,
            this,   &LocoController::messageReceived);

    m_locomotives.append(new Locomotive(37034));
}

void LocoController::messageReceived(const std::string &msg)
{

}
