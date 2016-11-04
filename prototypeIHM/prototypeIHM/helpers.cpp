#include <QGuiApplication>
#include <QDebug>
#include <QSettings>

#include "helpers.h"

int const Helpers::EXIT_CODE_REBOOT = -123456789;

Helpers::Helpers(QObject *parent) : QObject(parent) {

}

void Helpers::restartApp() {
    qDebug() << "Performing application reboot...";
    qApp->exit(Helpers::EXIT_CODE_REBOOT);
}

void Helpers::syncSettings() {
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.sync();
}
