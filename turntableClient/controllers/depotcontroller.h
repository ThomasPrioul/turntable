#ifndef DEPOTCONTROLLER_H
#define DEPOTCONTROLLER_H

#include <QObject>
#include "icontroller.h"

class DepotController : public QObject, IController
{
    Q_OBJECT
    Q_INTERFACES(IController)

public:
    explicit DepotController(TurntableApplication* appRef = 0, QObject *parent = 0);

signals:

public slots:
    void messageReceived(const std::string& msg);
};

#endif // DEPOTCONTROLLER_H
