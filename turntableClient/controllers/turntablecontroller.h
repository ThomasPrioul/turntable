#ifndef TURNTABLECONTROLLER_H
#define TURNTABLECONTROLLER_H

#include <QObject>
#include "icontroller.h"

class TurntableController : public QObject, IController
{
    Q_OBJECT
    Q_INTERFACES(IController)

public:
    explicit TurntableController(TurntableApplication* appRef, QObject *parent = 0);

public slots :
    void messageReceived(const QString& msg);
    void reset();
    void move(int position);
};

#endif // TURNTABLECONTROLLER_H
