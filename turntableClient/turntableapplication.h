#ifndef TURNTABLEAPPLICATION_H
#define TURNTABLEAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <string>
#include "dccclientnetwork.h"
#include "controllers/turntablecontroller.h"

class TurntableApplication : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(DccClientNetwork* network READ network)
    Q_PROPERTY(TurntableController* turntable READ turntable)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit TurntableApplication(int& argc, char **argv[]);

    bool connected() const { return m_connected; }
    DccClientNetwork* network() { return &m_network; }
    TurntableController* turntable() { return &m_turntable; }

signals:
    void connectedChanged();
    void messageReceived(const QString& msg);

protected:
    void setConnected(bool value) {
        if (value != m_connected) {
            m_connected = value;
            emit connectedChanged();
        }
    }

private slots:
    void networkConnected(const QString &hostname, quint16 port);
    void networkDisconnected();
    void networkMessageReceived(const std::vector<char> &rawMessage);

private:
    bool m_connected = false;
    QQmlApplicationEngine m_engine;
    DccClientNetwork m_network;
    TurntableController m_turntable;
};

#endif // TURNTABLEAPPLICATION_H
