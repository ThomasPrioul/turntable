#include <iostream>
#include <sstream>
#include "macros.h"
#include "turntableapplication.h"
#include "turntablecontroller.h"
#include "../turntableService/networkconfig.h"

namespace query = NetworkConfig::Query;
namespace notif = NetworkConfig::Notification;

TurntableController::TurntableController(TurntableApplication* appRef, QObject *parent)
    : QObject(parent)
    , IController(appRef)
    , m_tracks(this)
{
    // Static cast to disambiguate between two method signatures
    //static_cast<void (TurntableApplication::*)(const std::string&)>(&TurntableApplication::messageReceived)
    connect(m_app,  &TurntableApplication::messageReceived,
            this,   &TurntableController::messageReceived);
}

void TurntableController::messageReceived(const std::string &msg)
{
    // [1] Receive config info

    if (startsWith(msg, notif::beginSendConfig)) {
        // Set as busy to prevent user interaction
        setControllerState(ControllerState::Busy);

        // Clear tracklist when beginSend notification is received
        m_tracks.clear();
    }
    else if (startsWith(msg, notif::addTrack)) {
        std::stringstream reader(msg);

        if (reader.seekg(notif::addTrack.length())) {
            std::string track;
            int position;

            if (std::getline(std::getline(reader, track, '"'), track, '"')  >> position) {
                // The method will discard duplicated or update the position
                m_tracks.addTrack(QString::fromStdString(track), position);
            }
        }
        else {
            std::cerr << "" << std::endl;
        }
    }
    else if (startsWith(msg, notif::deleteTrack)) {
        std::stringstream reader(msg);

        if (reader.seekg(notif::deleteTrack.length())) {
            std::string track;

            if (std::getline(std::getline(reader, track, '"'), track, '"')) {
                // The method will discard duplicated or update the position
                m_tracks.deleteTrack(QString::fromStdString(track));
            }
        }
        else {
            std::cerr << "" << std::endl;
        }
    }
    else if (startsWith(msg, notif::trackDefinition)) {
        std::stringstream reader(msg);

        if (reader.seekg(notif::trackDefinition.length())) {
            std::string track;
            int position;

            // Read quoted string
            if (std::getline(std::getline(reader, track, '"'), track, '"')  >> position) {
                // The method will discard duplicated or update the position
                m_tracks.addTrack(QString::fromStdString(track), position);
            }
        }
        else {
            std::cerr << "" << std::endl;
        }
    }
    else if (startsWith(msg, notif::endSendConfig)) {
        setControllerState(ControllerState::Idle);
    }
    else if (startsWith(msg, notif::nbSteps)) {
        std::stringstream reader(msg);
        int tmpSteps;

        if (reader.seekg(notif::nbSteps.length()) && reader >> tmpSteps) {
            setSteps(tmpSteps);
        }
    }
    // [1] Receive config info

    // [2] Receive state information
    else if (startsWith(msg, notif::resetStarted)) {
        setControllerState(ControllerState::Busy);
        setResetting(true);
    }
    else if (startsWith(msg, notif::resetStopped)) {
        std::stringstream reader(msg);
        int result;

        if (reader.seekg(notif::resetStopped.length())) {
            if (reader >> result) {
                emit resetDone((bool)result);

                if (result) {
                    setPosition(0);
                }

                setResetting(false);
                setControllerState(ControllerState::Idle);
            }
        }
    }
    else if (startsWith(msg, notif::moveStarted)) {
        setControllerState(ControllerState::Busy);
        m_moving = true;
    }
    else if (startsWith(msg, notif::moveStopped)) {
        setControllerState(ControllerState::Idle);
        m_moving = false;
    }
    else if (startsWith(msg, notif::position)) {
        std::stringstream reader(msg);
        int result;

        if (reader.seekg(notif::position.length())) {
            if (reader >> result) {
                setPosition(result);
            }
        }
    }
}

void TurntableController::reset()
{
    std::ostringstream output;
    output << query::reset << '\n';
    m_app->network()->sendMessage(output.str());
}

void TurntableController::startIndefiniteMove(bool direction)
{
    std::ostringstream output;
    output << query::move << ' ' << (int)direction << '\n';
    m_app->network()->sendMessage(output.str());
}

void TurntableController::moveToPosition(int position)
{
    std::ostringstream output;
    output << query::moveToPosition << ' ' << position << '\n';
    m_app->network()->sendMessage(output.str());
}

void TurntableController::moveToTrack(Track *track)
{
    if (track != nullptr) {
        std::ostringstream output;
        output << query::moveToTrack << " \"" << track->name().toStdString() << "\"\n";
        m_app->network()->sendMessage(output.str());
    }
}

void TurntableController::stop()
{
    std::string stopMsg = query::stop + '\n';
    m_app->network()->sendMessage(stopMsg);
}

void TurntableController::getConfig()
{
    std::ostringstream output;
    output << query::sendConfig << '\n';
    output << query::nbSteps << '\n';
    output << query::position << '\n';
    m_app->network()->sendMessage(output.str());
}

void TurntableController::addServiceTrack(const QString &name, int pos)
{
    std::ostringstream output;
    output << query::addTrack << " \"" << name.toStdString() << "\" " << pos << '\n';
    m_app->network()->sendMessage(output.str());
}

void TurntableController::removeServiceTrack(const QString &name)
{
    std::ostringstream output;
    output << query::deleteTrack << " \"" << name.toStdString() << "\"\n";
    m_app->network()->sendMessage(output.str());
}
