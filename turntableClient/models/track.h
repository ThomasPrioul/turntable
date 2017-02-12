#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool edit READ edit WRITE setEdit NOTIFY editChanged)

public:
    Track(QObject *parent = 0) : QObject(parent) { }

    Track(const QString &name, int position, QObject *parent = 0)
        : QObject(parent), m_name(name), m_position(position) { }

    QString name() const { return m_name; }
    int position() const { return m_position; }
    bool edit() const { return m_edit; }

    void setName(const QString& value) {
        if (m_name == value)
            return;
        m_name = value;
        nameChanged();
    }
    void setPosition(int value) {
        if (m_position == value)
            return;
        m_position = value;
        positionChanged();
    }
    void setEdit(bool value) {
        if (m_edit == value)
            return;
        m_edit = value;
        editChanged();
    }

signals:
    void nameChanged();
    void positionChanged();
    void editChanged();

private:
    QString m_name;
    int     m_position;
    bool    m_edit;
};

#endif // TRACK_H
