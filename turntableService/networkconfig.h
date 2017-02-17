#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <string>

namespace NetworkConfig  {

    const char defaultIP[] = "127.0.0.1";
    const quint16 defaultPort = 2017;
    const int32_t defaultSteps = 19200;

    // All commands end up with \n, \r is not mandatory

    namespace Query {
        const std::string reset = "RR";
        const std::string stop = "RS";
        const std::string move = "RD"; // RD <pos>
        const std::string moveToTrack = "RD track"; // RD track "<trackname>"
        const std::string moveToPosition = "RD pos"; // RD pos <pos>
        const std::string position = "RP";
        const std::string sendConfig = "RC"; // RC
        const std::string nbSteps = "RI steps"; // RI steps
        const std::string polarity = "RI polarity"; // RI polarity
        const std::string addTrack = "RV add"; // RV add "<trackName>" <pos>
        const std::string deleteTrack = "RV del"; // RV del "<trackName>"
    }

    namespace Notification {
        const std::string moveStarted = "SD start";
        const std::string moveStopped = "SD stop";
        const std::string resetStarted = "SR start";
        const std::string resetStopped = "SR stop "; // SR stop <success: 0 or 1>
        const std::string position = "SP "; // SP <pos>
        const std::string beginSendConfig = "SC begin"; // SC begin
        const std::string endSendConfig = "SC end"; // SC end
        const std::string nbSteps = "SI steps"; // SI steps <nbSteps>
        const std::string polarity = "SI polarity"; // SI polarity <polarity: 0 for inverted, 1 for normal>
        const std::string trackDefinition = "SV "; // SV "<trackname>" <pos>
        const std::string addTrack = "SV add "; // SV add "<trackname>" <pos>
        const std::string deleteTrack = "SV del "; // SV del "<trackname>" <pos>
    }
}

#endif // NETWORKCONFIG_H
