#include <QGuiApplication>
#include <QDebug>
#include <QSettings>

#include "helpers.h"

Helpers::Helpers(QObject *parent) : QObject(parent) {

}

void Helpers::syncSettings() {
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.sync();
}
