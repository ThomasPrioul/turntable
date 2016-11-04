#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QQuickStyle>

#include "helpers.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Gallery");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    int currentExitCode = 0;
    Helpers helpers;

    do {
        QGuiApplication app(argc, argv);

        QSettings settings;
        QString style = QQuickStyle::name();

        if (!style.isEmpty())
            settings.setValue("style", style);
        else
            QQuickStyle::setStyle(settings.value("style").toString());

        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("tamere", &helpers);
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));

        // Failure to load main.qml
        if (engine.rootObjects().isEmpty())
            return -1;

        currentExitCode = app.exec();
    } while( currentExitCode == Helpers::EXIT_CODE_REBOOT );

    return currentExitCode;
}
