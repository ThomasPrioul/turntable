#ifndef TURNTABLENETWORK_H
#define TURNTABLENETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include "circularbuffer.h"

class TurntableNetwork : public QObject
{
    Q_OBJECT
public:
    explicit TurntableNetwork(QObject *parent = 0);
    ~TurntableNetwork();

    bool start(const QHostAddress &ipAddress, quint16 port);
    void quit()
    {
        if (clientSocket != Q_NULLPTR) {
            clientSocket->disconnectFromHost();
        }
    }

signals:
    void messageReceived(const std::vector<char> &message);
    void clientConnected();
    void clientDisconnected();

public slots:
    void sendMessage(const char *str, size_t len);
    void sendMessage(const std::ostringstream &ostr);
private slots:
    void newSocketConnection();
    void socketDisconnected();
    void socketDataAvailable();

private:
    QTcpServer tcpServer;
    QTcpSocket *clientSocket;
    CircularBuffer<char> readBuffer;
};

#endif // TURNTABLENETWORK_H
