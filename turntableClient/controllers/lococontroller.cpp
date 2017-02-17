#include <iostream>
#include <sstream>
#include <string>
#include "macros.h"
#include "turntableapplication.h"
#include "lococontroller.h"

const std::string powerCommand = std::string("CP");
const std::string powerResponse = std::string("DP");
const std::string locoDirectionResponse = std::string("MS");

LocoController::LocoController(TurntableApplication *appRef, QObject *parent)
    : QObject(parent)
    , IController(appRef)
{
    connect(m_app,  &TurntableApplication::messageReceived,
            this,   &LocoController::messageReceived);

    m_locomotives.append(new Locomotive(7, m_app->network()));
}

void LocoController::powerOn()
{
    std::string output("CP 1\n");
    m_app->network()->sendMessage(output);
}

void LocoController::powerOff()
{
    std::string output("CP 0\n");
    m_app->network()->sendMessage(output);
}

void LocoController::messageReceived(const std::string &msg)
{
    if (startsWith(msg, powerResponse)) {
        std::istringstream reader(msg);
        bool state = false;

        if (reader.seekg(powerResponse.length()) &&
            reader >> state) {
            if (m_powerActive != state) {
                m_powerActive = state;
                emit powerActiveChanged();
            }
        }
    }
    else if (startsWith(msg, locoDirectionResponse)) {
        std::istringstream reader (msg);
        int locoId;
        std::string locoDir;

        if (reader.seekg(locoDirectionResponse.length()) && reader >> locoId && reader >> locoDir) {
            Locomotive* loco = findLoco(locoId);
            if (loco != nullptr) {

                loco->setDirection(locoDir == "N");
            }
        }
    }
}

Locomotive* LocoController::findLoco(int id) {
    for (int i = 0; i < m_locomotives.length(); i++)
    {
        if (m_locomotives.at(i)->id() == id) {
            return m_locomotives.at(i);
        }
    }

    return nullptr;
}

void LocoController::refresh(int id)
{
    Locomotive* p_loco = findLoco(id);

    if (p_loco != nullptr) {
        std::ostringstream str;
        str << "LF " << id << '\n';
        m_app->network()->sendMessage(str.str());
    }

    //if (m_locomotives.con)
}


