#include <QGuiApplication>
#include <QDebug>

#include "helpers.h"

int const Helpers::EXIT_CODE_REBOOT = -123456789;

Helpers::Helpers(QObject *parent) : QObject(parent)
{

}

void Helpers::restart()
{
    qDebug() << "Performing application reboot...";
    qApp->exit(Helpers::EXIT_CODE_REBOOT);
}
