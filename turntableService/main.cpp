#include <iostream>
#include "turntableservice.h"

int main(int argc, char *argv[])
{
    TurntableService app(argc, &argv);
    QCoreApplication::setApplicationName("turntableservice");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription(R"(Turntable background service
Thomas Prioul
Polytech' Tours - 2017)");

    if (app.parseCommandLine(parser) == CommandLineError) {
        return -1;
    }

    return app.exec();
}

