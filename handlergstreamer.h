#ifndef HANDLERGSTREAMER_H
#define HANDLERGSTREAMER_H

#include <QObject>
#include <gst/gst.h>
#include <gst/video/video.h>
#include <glib.h>
#include <QWidget>
#include <QThread>
#include "GStreamerData.h"
#include "ibuscallback.h"
#include "igstreamerdataprovider.h"


class HandlerGStreamer : public QThread, public IGStreamerDataProvider, public IBusCallback
{
    Q_OBJECT
public:
    explicit HandlerGStreamer(QObject *parent = nullptr);
    void stopLoop() override;
    const VideoData& getData() override;
    ~HandlerGStreamer();

public slots:
    void setRtsp(const QString& rtspLink);
    void setWinId(const WId wid);
    void setOverlayText(const QString& text);
    void mute();
    void unmute();
    void playVideo();
    void pauseVideo();
    void stopVideo();
protected:
    void run() override;
private:
    QString m_rtspLink;
    QString m_overlayText;
    VideoData videoData;
    AudioData audioData;
    WId m_wid;
    guint bus_watch_id;
    //This variable is necessary to run the main loop
    GMainLoop* loop;
    // This function will be called by the pad-added signal
    static void pad_added_video(GstElement* src, GstPad* new_pad, VideoData* data);
    static void pad_added_audio(GstElement* src, GstPad* new_pad, AudioData* data);
    //Start main pipeline
    void startPipeline();
signals:
    void videoStopped();

};

#endif // HANDLERGSTREAMER_H
