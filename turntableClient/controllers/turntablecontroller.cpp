#include <sstream>
#include <iostream>
#include "turntablecontroller.h"
#include "turntableapplication.h"
#include "../turntableService/networkconfig.h"

namespace query = NetworkConfig::Query;
namespace notif = NetworkConfig::Notification;

TurntableController::TurntableController(TurntableApplication* appRef, QObject *parent)
    : QObject(parent)
    , IController(appRef)
{
    connect(m_app, &TurntableApplication::messageReceived, this, &TurntableController::messageReceived);
}

void TurntableController::messageReceived(const QString &msg)
{
    std::cout << "TurntableComponent: received: " << msg.toStdString() << std::endl;
}

void TurntableController::reset()
{
    std::ostringstream output;
    output << query::reset << '\n';
    m_app->network()->sendMessage(output.str());
}

void TurntableController::move(int position)
{
    std::ostringstream output;
    output << query::move << ' ' << position << '\n';
    m_app->network()->sendMessage(output.str());
}
