#ifndef TURNTABLECONTROLLER_H
#define TURNTABLECONTROLLER_H

#include <QObject>
#include <string>
#include "icontroller.h"
#include "models/tracksmodel.h"


enum class GetConfigState {
    NotAwaiting,
    BeginReceived
};

class TurntableController : public QObject, IController
{
    Q_OBJECT    
    Q_PROPERTY(TracksModel* tracksData READ tracksData NOTIFY tracksDataChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(bool resetting READ resetting NOTIFY resettingChanged)
    Q_PROPERTY(int position READ position NOTIFY positionChanged)
    Q_INTERFACES(IController)

public:
    explicit TurntableController(TurntableApplication* appRef = 0, QObject *parent = 0);
    TracksModel* tracksData() { return &m_tracks; }
    bool busy() { return m_state == ControllerState::Busy; }
    bool resetting() const { return m_resetting; }
    int position() const { return m_position; }

signals:
    void tracksDataChanged();
    void busyChanged();
    void positionChanged();
    void resettingChanged();
    void resetDone(bool success);

public slots:
    void messageReceived(const std::string& msg);
    void reset();
    void move(int position);
    void stop();
    void getConfig();

private:
    //GetConfigState m_getCfgState = GetConfigState::NotAwaiting;
    void setControllerState(ControllerState value) {
        if (m_state == value)
            return;
        m_state = value;
        busyChanged();
    }
    void setResetting(bool value) {
        if (m_resetting == value)
            return;
        m_resetting = value;
        resettingChanged();
    }
    void setPosition(int value) {
        if (m_position == value)
            return;
        m_position = value;
        positionChanged();
    }

    bool m_moving;
    bool m_resetting;
    int m_position = -1;

    TracksModel m_tracks;
};

#endif // TURNTABLECONTROLLER_H
