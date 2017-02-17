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
        return QQmlListProperty<Track>(this, m_tracks);
    }

signals:
    void listChanged();

public slots:
    void addTrack(const QString& name, int pos)
    {
        Track* existingItem = nullptr;

        // Check whether there's already a track with the same name
        for (auto i : m_tracks) {
            if (i->name() == name) {
                existingItem = i;
                if (existingItem->position() != pos) {
                    existingItem->setPosition(pos);
                }
                break;
            }
        }

        if (existingItem == nullptr) {
            if (m_tracks.length() == 0)
                m_tracks.append(new Track(name, pos));
            else {
                int i = 0;
                for (; i < m_tracks.length(); i++) {
                    if (m_tracks.at(i)->name().compare(name) > 0) {
                        break;
                    }
                }
                m_tracks.insert(i, new Track(name, pos));
            }

            emit listChanged();
        }
    }

    void deleteTrack(Track* track)
    {
        m_tracks.removeAll(track);
        emit listChanged();
    }

    void deleteTrack(const QString& track)
    {
        Track* existingItem = nullptr;

        for (auto i : m_tracks) {
            if (i->name() == track) {
                existingItem = i;
                break;
            }
        }

        if (existingItem != nullptr) {
            m_tracks.removeAll(existingItem);
        }

        emit listChanged();
    }

    void clear()
    {
        m_tracks.clear();
        emit listChanged();
    }

private:
    QList<Track*> m_tracks;
};

#endif // MOTOR_H
