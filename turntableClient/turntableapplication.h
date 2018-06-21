#ifndef TURNTABLEAPPLICATION_H
#define TURNTABLEAPPLICATION_H

#include <string>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "dccclientnetwork.h"
#include "clientsettings.h"
#include "controllers/turntablecontroller.h"
#include "controllers/lococontroller.h"
#include "controllers/turnoutscontroller.h"

class TurntableApplication : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(DccClientNetwork* network READ network NOTIFY networkChanged)
    Q_PROPERTY(TurntableController* turntable READ turntable NOTIFY turntableChanged)
    Q_PROPERTY(LocoController* locomotives READ locomotives NOTIFY locomotivesChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(ClientSettings* settings READ settings)
    Q_PROPERTY(TurnoutsController* turnouts READ turnouts NOTIFY turnoutsChanged)
    

public:
    explicit TurntableApplication(int& argc, char **argv[]);

    bool connected() const { return m_connected; }
    DccClientNetwork* network() { return &m_network; }
    TurntableController* turntable() { return &m_turntable; }
    LocoController* locomotives() { return &m_locomotives; }
    ClientSettings* settings() { return &m_settings; }
    TurnoutsController* turnouts() { return &m_turnouts; }

signals:
    void connectedChanged();
    void networkChanged();
    void turntableChanged();
    void locomotivesChanged();
    void turnoutsChanged();
    void messageReceived(const std::string& msg);
    void messageReceivedQString(const QString& msg);

protected:
    void setConnected(bool value) {
        if (value == m_connected)
            return;
        m_connected = value;
        emit connectedChanged();
    }

private slots:
    void networkConnected(const QString &hostname, quint16 port);
    void networkDisconnected();
    void networkMessageReceived(const std::vector<char> &rawMessage);

private:
    bool m_connected = false;
    QQmlApplicationEngine m_engine;
    LocoController m_locomotives;
    DccClientNetwork m_network;
    ClientSettings m_settings;
    TurntableController m_turntable;
    TurnoutsController m_turnouts;

};

#endif // TURNTABLEAPPLICATION_H
