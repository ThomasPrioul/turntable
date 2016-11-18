#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QQuickStyle>

#include "helpers.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Proto IHM");
    QGuiApplication::setOrganizationName("Thomas Prioul");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle(QString("Material"));

    QQmlApplicationEngine engine;
    Helpers helpers;

    engine.rootContext()->setContextProperty("appHelpers", &helpers);
    engine.load(QUrl("qrc:/main.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
