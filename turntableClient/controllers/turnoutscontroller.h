#ifndef TURNOUTSCONTROLLER_H
#define TURNOUTSCONTROLLER_H

#include <QObject>
#include "icontroller.h"


class TurnoutsController  : public QObject, IController
{
    Q_OBJECT
    Q_INTERFACES(IController)

public:
    explicit TurnoutsController(TurntableApplication* appRef = 0, QObject *parent = 0);

public slots:
    void messageReceived(const std::string& msg);
};

#endif // TURNOUTSCONTROLLER_H
