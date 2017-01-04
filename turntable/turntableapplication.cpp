#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>
#include "turntableapplication.h"

TurntableApplication::TurntableApplication(int argc, char *argv[]) :
    QGuiApplication(argc, argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setApplicationName("Proto IHM");
    QGuiApplication::setOrganizationName("Thomas Prioul");

    // Give network class access to QML environment
    engine.rootContext()->setContextProperty("network", &network);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
}
