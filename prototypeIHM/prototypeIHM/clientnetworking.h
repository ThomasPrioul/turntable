#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

class ClientNetworking : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetworking(QObject *parent = Q_NULLPTR);

    bool connect(const QString& hostname, uint16_t port);
    bool disconnect();

private slots:
    void receiveMessageHandler();
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();

private:
    QTcpSocket *tcpSocket;
    QDataStream in;
    QNetworkSession *networkSession;

    bool sendClientType(); // CS 7
    bool sendClientRevision(const QString& revision); // CL LW_PilotageTco_6.3
};
