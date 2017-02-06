#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QHash>

class Motor : public QObject
{
    Q_OBJECT
public:
    explicit Motor(QObject *parent = 0);

signals:
    void trackAdded(const QString& name, int32_t position);
    void trackDeleted(const QString& name);
public slots:

private:
    bool moving = false;
    int32_t position;
    QHash<QString, int32_t> tracks;
};

#endif // MOTOR_H
