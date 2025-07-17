#ifndef MEDIASOURCE_H
#define MEDIASOURCE_H

#include <QMultiMap>

enum class Type
{
    Rtsp,
    Cover,
    Video,
};

struct MediaSource
{
    Type type;
    QString  settingsGroupName;
    QMultiMap<QString, QString> source;
};

#endif // MEDIASOURCE_H
