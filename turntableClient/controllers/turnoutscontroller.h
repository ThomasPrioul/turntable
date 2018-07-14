#ifndef TURNOUTSCONTROLLER_H
#define TURNOUTSCONTROLLER_H

#include <QObject>
#include "icontroller.h"


class TurnoutsController  : public QObject, IController
{
    Q_OBJECT
    Q_PROPERTY(QString sizeLabel READ sizeLabel NOTIFY sizeLabelChanged)
    Q_INTERFACES(IController)

public:
    explicit TurnoutsController(TurntableApplication* appRef = 0, QObject *parent = 0);  
    QString sizeLabel() const { return m_sizeLabel; }

signals:
    void sizeLabelChanged();

public slots:
    void messageReceived(const std::string& msg);
    void sizeScreen(int panH, int panW);
    void cmdTrackTrace(int adress);

private:
    QString m_sizeLabel;
};

#endif // TURNOUTSCONTROLLER_H
