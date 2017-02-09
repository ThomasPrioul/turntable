#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QQmlListProperty>
#include "track.h"

class TracksModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Track> list READ list NOTIFY listChanged)

public:
    explicit TracksModel(QObject *parent = 0) : QObject(parent)
    {
    }

    QQmlListProperty<Track> list() {
        return QQmlListProperty<Track>(this, _list);
    }

signals:
    void listChanged();

public slots:
    void addTrack(const QString& name, int pos)
    {
        Track* existingItem = nullptr;

        // Check whether there's already a track with the same name
        for (auto i : _list) {
            if (i->name() == name) {
                existingItem = i;
                if (existingItem->position() != pos) {
                    existingItem->setPosition(pos);
                }
                break;
            }
        }

        if (existingItem == nullptr) {
            _list.append(new Track(name, pos));
            emit listChanged();
        }
    }

    void deleteTrack(Track* track)
    {
        _list.removeAll(track);
        emit listChanged();
    }

    void deleteTrack(const QString& track)
    {
        Track* existingItem = nullptr;

        for (auto i : _list) {
            if (i->name() == track) {
                existingItem = i;
                break;
            }
        }

        if (existingItem != nullptr) {
            _list.removeAll(existingItem);
            emit listChanged();
        }
    }

    void clear()
    {
        _list.clear();
        emit listChanged();
    }

private:
    QList<Track*> _list;
};

#endif // MOTOR_H
