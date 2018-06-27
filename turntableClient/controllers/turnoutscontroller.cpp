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

void TurnoutsController::sizeScreen(int panH, int panW)
{
    qDebug("Test Console");
    QString str =  QString("Hauteur = %1 Largeur = %2").arg(QString::number(panH), QString::number(panW));
    qDebug(str.toLatin1());

}
