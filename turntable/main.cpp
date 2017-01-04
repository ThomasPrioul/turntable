#include "turntableapplication.h"

int main(int argc, char *argv[])
{
    TurntableApplication app(argc, argv);

    return app.exec();

//    BlockingNetwork net;

//    bool result = net.connectToHost(QString("192.168.32.1"), 2002);
//    qDebug() << "Connected : " << result;
//    net.receiveMessage();

//    net.disconnectFromHost();
}
