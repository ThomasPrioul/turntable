#ifndef TRACKITEM_H
#define TRACKITEM_H

#include <QObject>
#include "macros.h"

class TrackItem : public QObject
{
    Q_OBJECT
public:
    explicit TrackItem(QObject *parent = 0);

signals:

public slots:
};

#endif // TRACKITEM_H
