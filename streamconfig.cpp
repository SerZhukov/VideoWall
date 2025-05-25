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

const QString &StreamConfig::getPathCover() const
{
    return m_pathCover;
}

const QMultiMap<QString, QString> &StreamConfig::getRtspLinkMap() const
{
    return m_rtspMap;
}

void StreamConfig::setName(const QString &name)
{
    m_name = name;
}

void StreamConfig::setPathCover(const QString &path)
{
    m_pathCover = path;
}


void StreamConfig::addRtspLink(const QMultiMap<QString, QString> &rtspMap)
{  
    m_rtspMap = rtspMap;
}
