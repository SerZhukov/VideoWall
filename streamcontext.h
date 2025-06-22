#ifndef STREAMCONTEXT_H
#define STREAMCONTEXT_H

#include <QObject>
#include "GStreamerData.h"

class StreamContext : public QObject
{
    Q_OBJECT
public:
    explicit StreamContext(QObject *parent = nullptr);
    void setVideoData(const VideoData& data);
    const VideoData& getVideoData();
private:
    VideoData m_videoData;

signals:
};

#endif // STREAMCONTEXT_H
