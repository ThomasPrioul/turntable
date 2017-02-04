#include "turntableservice.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<int32_t>("int32_t");
    TurntableService app(argc, &argv);

    auto result = app.initialize();
    if (result == AppInitResult::HelpRequested ||
        result == AppInitResult::VersionRequested)
        return EXIT_SUCCESS;
    else if (result == AppInitResult::Error)
        return EXIT_FAILURE;

    return app.exec();
}
