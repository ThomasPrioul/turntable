#include <iostream>
#include <sstream>
#include <QQmlContext>
#include <QQmlEngine>
#include "turntableapplication.h"
#include "../turntableService/networkconfig.h"
#include "models/tracksmodel.h"

namespace query = NetworkConfig::Query;
namespace notif = NetworkConfig::Notification;

TurntableApplication::TurntableApplication(int &argc, char **argv[])
    : QGuiApplication(argc, *argv)
    , m_engine()
    , m_network(this)
    , m_settings(this)
    , m_turntable(this, this)

{
    QCoreApplication::setApplicationName("Client plaque tournante");
    QCoreApplication::setOrganizationName("Thomas Prioul");
    QCoreApplication::setApplicationVersion("0.1");

    connect(&m_network, &DccClientNetwork::connected,        this, &TurntableApplication::networkConnected);
    connect(&m_network, &DccClientNetwork::disconnected,     this, &TurntableApplication::networkDisconnected);
    connect(&m_network, &DccClientNetwork::messageReceived,  this, &TurntableApplication::networkMessageReceived);

    // Qml registeration : prevents errors and gives autocomplete
    qmlRegisterType<DccClientNetwork>("turntable.client", 1, 0, "Network");
    //qmlRegisterType<ClientSettings>("turntable.client", 1, 0, "AppSettings");
    qmlRegisterType<Track>("turntable.client.models", 1, 0, "Track");
    qmlRegisterType<TracksModel>("turntable.client.models", 1, 0, "TrackData");
    qmlRegisterType<TurntableController>("turntable.client.controllers", 1, 0, "TurntableController");

    m_settings.load();

    // Give access of the application class instance to the QML environment.
    m_engine.rootContext()->setContextProperty("app", this);
    m_engine.load(QUrl(QString("qrc:/main.qml")));
}

void TurntableApplication::networkConnected(const QString &hostname, quint16 port)
{
    setConnected(true);
    m_turntable.resetController();
    m_turntable.getConfig();
    std::cout << "connected" << std::endl;
}

void TurntableApplication::networkDisconnected()
{
    setConnected(false);
    m_turntable.resetController();
    std::cout << "disconnected" << std::endl;
}

void TurntableApplication::networkMessageReceived(const std::vector<char> &rawMessage)
{
    std::string msg(rawMessage.begin(), rawMessage.end());
    std::cout << "Received : " << msg << std::endl;
    emit messageReceived(msg); // For C++ backend
    emit messageReceivedQString(QString::fromStdString(msg)); // For QML
//    if (startsWith(msg, notif::position)) {
//        std::istringstream reader(msg);
//        int32_t motorNewPosition;

//        if (reader.seekg(notif::position.length())) {
//            if (reader >> motorNewPosition) {

//            }
//            else {
//                std::cerr << "Failed to read position in message: " << msg << std::endl;
//            }
//        }
//        else {
//            std::cerr << "Could not find target motor position in message: " << msg << std::endl;
//        }
//    }
}
