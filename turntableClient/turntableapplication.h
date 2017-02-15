#ifndef TURNTABLEAPPLICATION_H
#define TURNTABLEAPPLICATION_H

#include <string>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "dccclientnetwork.h"
#include "clientsettings.h"
#include "controllers/turntablecontroller.h"

class TurntableApplication : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(DccClientNetwork* network READ network NOTIFY networkChanged)
    Q_PROPERTY(TurntableController* turntable READ turntable NOTIFY turntableChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(ClientSettings* settings READ settings)

public:
    explicit TurntableApplication(int& argc, char **argv[]);

    bool connected() const { return m_connected; }
    DccClientNetwork* network() { return &m_network; }
    TurntableController* turntable() { return &m_turntable; }
    ClientSettings* settings() { return &m_settings; }

signals:
    void connectedChanged();
    void networkChanged();
    void turntableChanged();
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
    DccClientNetwork m_network;
    ClientSettings m_settings;
    TurntableController m_turntable;
};

#endif // TURNTABLEAPPLICATION_H
