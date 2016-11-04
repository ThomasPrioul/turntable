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

    int currentExitCode = 0;
    int styleCounter = 0;

    do {
        QGuiApplication app(argc, argv);

        switch (styleCounter) {
        case 0:
            QQuickStyle::setStyle(QString("Default"));
            break;

        case 1:
            QQuickStyle::setStyle(QString("Material"));
            break;

        case 2:
            QQuickStyle::setStyle(QString("Universal"));
            break;

        default:
            styleCounter = -1;
            break;
        }

        styleCounter++;

//        QSettings settings("settings.ini", QSettings::IniFormat);
//        QString style = QQuickStyle::name();

//        if (!style.isEmpty()) {
//            settings.setValue("style", style);
//        }
//        else {
//            QString style = settings.value("style").toString();
//            QQuickStyle::setStyle(style);
//        }
        QQmlApplicationEngine engine;
        Helpers helpers;
        engine.rootContext()->setContextProperty("appHelpers", &helpers);
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));

        // Failure to load main.qml
        if (engine.rootObjects().isEmpty())
            return -1;

        currentExitCode = app.exec();
    } while( currentExitCode == Helpers::EXIT_CODE_REBOOT );

    return currentExitCode;
}
