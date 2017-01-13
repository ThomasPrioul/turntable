#ifndef TURNTABLEAPPLICATION_H
#define TURNTABLEAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QThread>
#include "clientnetwork.h"

class TurntableApplication : public QGuiApplication
{
    Q_OBJECT
public:
    TurntableApplication(int argc, char *argv[]);

private:
    QQmlApplicationEngine engine;
    ClientNetwork network;
};

#endif // TURNTABLEAPPLICATION_H
