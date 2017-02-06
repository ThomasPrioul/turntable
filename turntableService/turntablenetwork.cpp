#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <string>

#include "turntablenetwork.h"

TurntableNetwork::TurntableNetwork(QObject *parent)
    : QObject(parent)
    , tcpServer(this)
    , clientSocket(Q_NULLPTR)
    , readBuffer(128)
{
    connect(&tcpServer, &QTcpServer::newConnection, this, &TurntableNetwork::newSocketConnection);
}

TurntableNetwork::~TurntableNetwork()
{
    quit();
}

bool TurntableNetwork::start(const QHostAddress &ipAddress, quint16 port)
{
    if (!tcpServer.listen(ipAddress, port)) {
        std::cerr << "Unable to start the server: " << tcpServer.errorString().toStdString() << "." << std::endl;
        return false;
    }

    std::cout << "Turntable service listening on " << ipAddress.toString().toStdString() << ":" << tcpServer.serverPort() << std::endl;
    return true;
}

void TurntableNetwork::sendMessage(const char* str, size_t len)
{
    if (clientSocket != Q_NULLPTR) {
        clientSocket->write(str, len);
    }
}

void TurntableNetwork::sendMessage(const std::ostringstream &ostr)
{
    const std::string& str = ostr.str();
    sendMessage(str.c_str(), str.length());
}

void TurntableNetwork::newSocketConnection()
{
    QTcpSocket* newConnection = tcpServer.nextPendingConnection();

    // Schedule the socket deletion when it is disconnected
    connect(newConnection, &QAbstractSocket::disconnected, newConnection, &QObject::deleteLater);

    std::cout << "A client is requesting a connection..." << std::endl;

    // Reject connections when another client is connected
    if (clientSocket != Q_NULLPTR) {
        newConnection->write("Only one client is allowed on the turntable service.\n");
        newConnection->write("Please close the other client before trying to reconnect\n");
        newConnection->disconnectFromHost();
        std::cout << "New client rejected" << std::endl;
    }
    else {

        // Accept the client
        clientSocket = newConnection;
        connect(clientSocket, &QAbstractSocket::disconnected, this, &TurntableNetwork::socketDisconnected);
        connect(clientSocket, &QAbstractSocket::readyRead, this, &TurntableNetwork::socketDataAvailable);

        std::cout << "New client accepted : " << clientSocket->peerAddress().toString().toStdString() << ":" << clientSocket->peerPort() << std::endl;
        readBuffer.flush();
        emit clientConnected();
    }
}

void TurntableNetwork::socketDisconnected()
{
    std::cout << clientSocket->peerAddress().toString().toStdString() << ":" << clientSocket->peerPort() << " disconnected" << std::endl;
    clientSocket = Q_NULLPTR;
    readBuffer.flush();

    emit clientDisconnected();
}

void TurntableNetwork::socketDataAvailable()
{
    quint64 bytesToRead = clientSocket->bytesAvailable();
    char readChar(0);

    while (bytesToRead-- > 0) {
        if (clientSocket->getChar(&readChar)) {
            if (readChar != '\n') {
                readBuffer.put(readChar);
            }
            else {
                emit messageReceived(readBuffer.readAll());
            }
        }
        else {
            std::cerr << "Network: Error getting char from socket" << std::endl;
        }
    }
}
