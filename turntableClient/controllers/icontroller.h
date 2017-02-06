#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class TurntableApplication; // forward decl

enum class ComponentState {
    Init = 0,
    Idle = 1,
    Busy = 2
};

class IController
{
public:
    IController(TurntableApplication* appRef) : m_app(appRef)
    {

    }

    virtual ~IController(){} // do not forget this

public slots:
    virtual void messageReceived(const QString& msg) = 0;

protected:
    TurntableApplication* m_app;
    ComponentState m_state = ComponentState::Init;
    bool m_enabled = false;
};

Q_DECLARE_INTERFACE(IController, "IController") // define this out of namespace scope

#endif // CONTROLLER_H
