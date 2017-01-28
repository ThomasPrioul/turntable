#ifndef TURNTABLENETWORK_H
#define TURNTABLENETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "../turntableClient/circularbuffer.h"

class TurntableNetwork : public QObject
{
    Q_OBJECT
public:
    explicit TurntableNetwork(const QHostAddress& ipAddress, quint16 port, QObject *parent = 0);
    ~TurntableNetwork();

signals:
    void messageReceived(const QByteArray &message);
    void clientConnected();
    void clientDisconnected();

private slots:
    void newSocketConnection();
    void socketDisconnected();
    void socketDataAvailable();

private:
    QTcpServer *tcpServer;
    QTcpSocket *clientSocket;
    CircularBuffer readBuffer;
};

#endif // TURNTABLENETWORK_H
