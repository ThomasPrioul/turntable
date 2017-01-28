#include <QDebug>
#include <QCoreApplication>

#include "turntablenetwork.h"

TurntableNetwork::TurntableNetwork(const QHostAddress &ipAddress, quint16 port, QObject *parent)
    : QObject(parent)
    , tcpServer(Q_NULLPTR)
    , clientSocket(Q_NULLPTR)
    , readBuffer(128)
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(ipAddress, port)) {
        qCritical() << "Unable to start the server: " << tcpServer->errorString() << ".";
        QCoreApplication::exit(-1);
        return;
    }

    qInfo() << "Turntable service listening on " << ipAddress.toString() << ":" << tcpServer->serverPort();

    connect(tcpServer, &QTcpServer::newConnection, this, &TurntableNetwork::newSocketConnection);
}

TurntableNetwork::~TurntableNetwork()
{
    if (clientSocket != Q_NULLPTR) {
        clientSocket->disconnectFromHost();
    }
}

void TurntableNetwork::newSocketConnection()
{
    QTcpSocket* newConnection = tcpServer->nextPendingConnection();

    // Schedule the socket deletion when it is disconnected
    connect(newConnection, &QAbstractSocket::disconnected, newConnection, &QObject::deleteLater);

    qDebug() << "A client is requesting a connection...";

    // Reject connections when another client is connected
    if (clientSocket != Q_NULLPTR) {
        newConnection->write("Only one client is allowed on the turntable service.\n");
        newConnection->write("Please close the other client before trying to reconnect\n");
        newConnection->disconnectFromHost();
        qDebug() << "New client rejected";
    }
    else {

        // Accept the client
        clientSocket = newConnection;
        connect(clientSocket, &QAbstractSocket::disconnected, this, &TurntableNetwork::socketDisconnected);
        connect(clientSocket, &QAbstractSocket::readyRead, this, &TurntableNetwork::socketDataAvailable);

        qInfo() << "New client accepted : "
                 << clientSocket->peerAddress().toString() << ":" << clientSocket->peerPort();

        readBuffer.flush();

        emit clientConnected();

        //newConnection->write("Hello world!\n");
    }
}

void TurntableNetwork::socketDisconnected()
{
    qDebug() << clientSocket->peerAddress().toString() << ":" << clientSocket->peerPort() << " disconnected";
    clientSocket = Q_NULLPTR;
    readBuffer.flush();

    emit clientDisconnected();
}

void TurntableNetwork::socketDataAvailable()
{
    quint64 bytesToRead = clientSocket->bytesAvailable();
    quint64 i = bytesToRead;
    char readChar;

    while (i-- > 0) {
        if (clientSocket->getChar(&readChar)) {
            if (readChar != '\n') {// && readChar != '\r') {
                readBuffer.putChar(readChar);
            }
            else {
                emit messageReceived(readBuffer.readAll());
            }
        }
        else  {
            qDebug() << "Network: Error getting char from socket";
        }
    }
}
