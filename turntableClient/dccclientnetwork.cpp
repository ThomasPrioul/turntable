#include <QtNetwork>
#include <iostream>
#include "dccclientnetwork.h"

DccClientNetwork::DccClientNetwork(QObject *parent)
    : QObject(parent)
    , m_connected(false)
    , m_connecting(false)
    , m_readBuffer(512)
{
    connect(&m_socket, &QTcpSocket::connected, this, &DccClientNetwork::socketConnected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &DccClientNetwork::socketDisconnected);
    connect(&m_socket, &QTcpSocket::readyRead, this, &DccClientNetwork::socketDataAvailable);
    connect (&m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &DccClientNetwork::socketError);
}

DccClientNetwork::~DccClientNetwork()
{
    disconnectFromHost();
}

void DccClientNetwork::connectToHost(const QString &hostName, quint16 port)
{
    if (m_connected || m_connecting)
        return;

    m_connecting = true;

    this->m_hostname = hostName;
    this->m_port = port;

    m_readBuffer.flush();
    m_socket.connectToHost(hostName, port);
}

void DccClientNetwork::disconnectFromHost()
{
    if (!m_connected || m_connecting)
        return;

    m_connected = false;
    m_readBuffer.flush();
    m_socket.disconnectFromHost();
}

void DccClientNetwork::sendMessage(const std::string& message)
{
    if (m_connected) {
        m_socket.write(message.c_str(), message.length());
        emit messageSentQString(QString::fromStdString(message));
    }
}

void DccClientNetwork::socketConnected()
{
    m_connected = true;
    m_connecting = false;
    emit connected(m_hostname, m_port);
}

void DccClientNetwork::socketDisconnected()
{
    m_connected = false;
    emit disconnected();
}

void DccClientNetwork::socketError(QAbstractSocket::SocketError error)
{
    std::cerr << error << m_socket.errorString().toStdString() << std::endl;
    m_socket.disconnectFromHost();
    m_connecting = false;
}

void DccClientNetwork::socketDataAvailable()
{
    quint64 bytesToRead = m_socket.bytesAvailable();
    char readChar(0);

    while (bytesToRead-- > 0) {
        if (m_socket.getChar(&readChar)) {
            if (readChar != '\n' && readChar != '\r') {
                m_readBuffer.put(readChar);
            }
            else {
                emit messageReceived(m_readBuffer.readAll());
            }
        }
        else {
            std::cerr << "Network: Error getting char from socket" << std::endl;
        }
    }
}
