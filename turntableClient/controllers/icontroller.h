#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class TurntableApplication; // forward decl

enum class ControllerState {
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
    virtual void messageReceived(const std::string& msg) = 0;

protected:
    TurntableApplication* m_app;
    ControllerState m_state = ControllerState::Init;
    bool m_enabled = false;
};

Q_DECLARE_INTERFACE(IController, "IController") // define this out of namespace scope

#endif // CONTROLLER_H
