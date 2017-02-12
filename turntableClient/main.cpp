#include "turntableapplication.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<int32_t>("int32_t");
    TurntableApplication app(argc, &argv);

    return app.exec();
}
