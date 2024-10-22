#include "streamconfig.h"
#include <QDebug>

StreamConfig::StreamConfig(QObject *parent)
    : QObject{parent}
{

}

StreamConfig::~StreamConfig()
{
    qDebug() << "StreamConfig::~StreamConfig()";
}

const QString &StreamConfig::getName() const
{
    return name_;
}

const QSet<QString> &StreamConfig::getRtspSet() const
{
    return rtspSet_;
}




void StreamConfig::setName(const QString &name)
{
    name_ = name;
}

void StreamConfig::addRtsp(const QSet<QString>& rtspSet)
{
    rtspSet_= rtspSet;
}
