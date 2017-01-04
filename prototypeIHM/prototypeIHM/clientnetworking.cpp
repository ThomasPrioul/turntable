#include <QDebug>
#include "clientnetworking.h"

ClientNetworking::ClientNetworking(QObject *parent)
    : QObject(parent)
    , tcpSocket(new QTcpSocket(this))
    , networkSession(Q_NULLPTR)
{
    // Register handler for tcpSocket 'dataReceived' event
    QObject::connect(tcpSocket, &QIODevice::readyRead, this, &ClientNetworking::receiveMessageHandler);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);

    // Register handler for error
    connect(tcpSocket,
            static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
            this,
            &ClientNetworking::displayError);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {

        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered)
        {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &ClientNetworking::sessionOpened);

        getFortuneButton->setEnabled(false);
        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
}


void ClientNetworking::receiveMessageHandler()
{
    in.startTransaction();

    QString newMessage;
    in >> newMessage;
    qDebug() << QString("Message received: ") << newMessage;
}

void ClientNetworking::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;

    case QAbstractSocket::HostNotFoundError:
        qDebug() << QString("The host was not found. Please check the "
                            "host name and port settings.");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << QString("The connection was refused by the peer. "
                            "Make sure the server is running, "
                            "and check that the host name and port "
                            "settings are correct.");
        break;

    default:
        qDebug() << QString("The following error occurred:")  << tcpSocket->errorString();
    }
}

void ClientNetworking::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}
