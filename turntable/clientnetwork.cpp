#include <QtNetwork>
#include <QDebug>
#include "clientnetwork.h"

ClientNetwork::ClientNetwork(QObject *parent) :
    QObject(parent), readBuffer(128)
{
    connect(&socket, &QTcpSocket::connected, this, &ClientNetwork::socketConnected);
    connect(&socket, &QTcpSocket::disconnected, this, &ClientNetwork::socketDisconnected);
    connect(&socket, &QTcpSocket::readyRead, this, &ClientNetwork::socketDataAvailable);
}

void ClientNetwork::connectToHost(const QString &hostName, quint16 port)
{
    if(socket.isOpen())
        return;

    this->hostName = hostName;
    this->port = port;

    qDebug() << "Network : connect(" << hostName << ", " << port << ")";
    readBuffer.flush();
    socket.connectToHost(hostName, port);
}

void ClientNetwork::disconnectFromHost()
{
    if (!socket.isOpen())
        return;

    socket.disconnectFromHost();
    readBuffer.flush();

    qDebug() << "Network : disconnect()";
}

void ClientNetwork::socketDataAvailable()
{
    quint64 bytesToRead = socket.bytesAvailable();
    quint64 i = bytesToRead;
    char readChar;

    while (i-- > 0) {
        if (socket.getChar(&readChar)) {
            if (readChar != '\r') {
                readBuffer.putChar(readChar);
            }
            else {
                qDebug() << "Message: " << QString(readBuffer.readAll());
                //emit messageReceived(readBuffer.readAll());
            }
        }
        else  {
            qDebug() << "Network: Error getting char from socket";
        }
    }
}
