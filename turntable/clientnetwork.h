#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QtNetwork>

#include "circularbuffer.h"

/*
#include <QThread>

class I : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
    static void msleep(unsigned long msecs) {
        QThread::msleep(msecs);
    }
    static void usleep(unsigned long usecs) {
        QThread::usleep(usecs);
    }
};
*/

class ClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetwork(QObject *parent = 0);

    QString HostName() const { return hostName; }
    quint16 Port() const { return port; }

signals:
    void messageReceived(const QByteArray &message);
    void socketError(int socketError, const QString &message);
    void connected(const QString &hostname, quint16 port);
    void disconnected();

public slots:
    Q_INVOKABLE
    void connectToHost(const QString &hostName, quint16 port);

    Q_INVOKABLE
    void disconnectFromHost();

private slots:
    void socketConnected()
    {
        emit connected(hostName, port);
    }

    void socketDisconnected()
    {
        emit disconnected();
    }

    void socketDataAvailable();

private:
    QString hostName;
    quint16 port;
    QTcpSocket socket;
    CircularBuffer readBuffer;
};

#endif // CLIENTNETWORK_H
