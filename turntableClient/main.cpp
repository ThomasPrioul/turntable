#include "turntableapplication.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<int32_t>("int32_t");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    TurntableApplication app(argc, &argv);

    return app.exec();
}
