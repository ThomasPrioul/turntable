#include <QtNetwork>
#include "network.h"

Network::Network(QObject *parent) : QThread(parent), quit(false)
{

}

Network::~Network()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void Network::connectToHost(const QString &hostName, quint16 port)
{
    //QMutexLocker locker(&mutex);
    mutex.lock();

    this->hostName = hostName;
    this->port = port;

    if (!isRunning())
        start();
    else
        cond.wakeOne();

    mutex.unlock();
}

void Network::disconnectFromHost()
{

}

void Network::run()
{
    mutex.lock();
    QString serverName = hostName;
    quint16 serverPort = port;
    mutex.unlock();

    while (!quit)
    {
        QTcpSocket socket;
        socket.connectToHost(serverName, serverPort);

        if (!socket.waitForConnected()) {
            emit error(socket.error(), socket.errorString());
            return;
        }

        QDataStream in(&socket);
        in.setVersion(QDataStream::Qt_4_0);
        QString received;

        do
        {
            if (!socket.waitForReadyRead(10000)) {
                emit error(socket.error(), socket.errorString());
                return;
            }

            in.startTransaction();
            in >> received;
        } while (!in.commitTransaction());

        mutex.lock();
        emit messageReceived(received);

        cond.wait(&mutex);
        serverName = hostName;
        serverPort = port;
        mutex.unlock();
    }
}
