#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <string>

namespace NetworkConfig  {

    const char defaultIP[] = "127.0.0.1";
    const quint16 defaultPort = 2017;
    const int32_t defaultSteps = 19200;

    namespace Query {
        const std::string reset = "RR";
        const std::string stop = "RS";
        const std::string move = "RD";
        const std::string moveToTrack = "RD track";
        const std::string moveToPosition = "RD pos";
        const std::string position = "RP";
        const std::string sendConfig = "RC";
        const std::string addTrack = "RV add"; // RV add <trackName> <pos>
        const std::string deleteTrack = "RV del"; // RV del <trackName>
    }

    namespace Notification {
        const std::string moveStarted = "SD start";
        const std::string moveStopped = "SD stop";
        const std::string resetStarted = "SR start";
        const std::string resetStopped = "SR stop "; // SR stop <success: 0 or 1>
        const std::string position = "SP ";
        const std::string beginSendConfig = "SC begin";
        const std::string endSendConfig = "SC end";
        const std::string track = "SV ";
        const std::string addTrack = "SV add ";
        const std::string deleteTrack = "SV del ";
    }
}

#endif // NETWORKCONFIG_H
