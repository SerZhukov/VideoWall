#include "streamcontext.h"

StreamContext::StreamContext(QObject *parent)
    : QObject{parent}
{}

void StreamContext::setVideoData(const VideoData& data)
{
    m_videoData = data;
}

const VideoData &StreamContext::getVideoData()
{
    return m_videoData;
}


