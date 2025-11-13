#include "streamconfig.h"
#include <QDebug>

StreamConfig::StreamConfig(QObject *parent)
    : QObject{parent}
{

}

StreamConfig::~StreamConfig()
{

}

const QString &StreamConfig::getName() const
{
    return m_name;
}


const MediaSource& StreamConfig::getMediaData()
{
    m_mediaSource.source = m_rtspMap;
    m_mediaSource.type = Type::Rtsp;
    m_mediaSource.settingsGroupName = "Rtsp";
    return m_mediaSource;
}

void StreamConfig::setName(const QString &name)
{
    m_name = name;
}

void StreamConfig::addRtspLink(const QMultiMap<QString, QString> &rtspMap)
{  
    m_rtspMap = rtspMap;
}
