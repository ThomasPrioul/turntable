#include <iostream>
#include <sstream>
#include <QQmlContext>
#include <QQmlEngine>
#include "turntableapplication.h"
#include "../turntableService/networkconfig.h"

namespace query = NetworkConfig::Query;
namespace notif = NetworkConfig::Notification;

bool startsWith(const std::string& longStr, const std::string& shortStr)
{
    return shortStr.length() <= longStr.length()
        && std::equal(shortStr.begin(), shortStr.end(), longStr.begin());
}

TurntableApplication::TurntableApplication(int &argc, char **argv[])
    : QGuiApplication(argc, *argv)
    , m_engine()
    , m_network(this)
    , m_turntable(this, this)

{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Client plaque tournante");
    QCoreApplication::setOrganizationName("Thomas Prioul");
    QCoreApplication::setApplicationVersion("0.1");

    connect(&m_network, &DccClientNetwork::connected,        this, &TurntableApplication::networkConnected);
    connect(&m_network, &DccClientNetwork::disconnected,     this, &TurntableApplication::networkDisconnected);
    connect(&m_network, &DccClientNetwork::messageReceived,  this, &TurntableApplication::networkMessageReceived);

    // Give network class access to the QML environment
    m_engine.rootContext()->setContextProperty("app", this);
    m_engine.load(QUrl(QString("qrc:/main.qml")));
}

void TurntableApplication::networkConnected(const QString &hostname, quint16 port)
{
    setConnected(true);
    std::cout << "connected" << std::endl;
}

void TurntableApplication::networkDisconnected()
{
    setConnected(false);
    std::cout << "disconnected" << std::endl;
}

void TurntableApplication::networkMessageReceived(const std::vector<char> &rawMessage)
{
    std::string msg(rawMessage.begin(), rawMessage.end());
    std::cout << "Received : " << msg << std::endl;
    emit messageReceived(QString::fromStdString(msg));
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
