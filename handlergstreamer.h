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
#include "streamcontext.h"


class HandlerGStreamer : public QThread, public IGStreamerDataProvider, public IBusCallback
{
    Q_OBJECT
public:
    explicit HandlerGStreamer(StreamContext* streamContext, QObject *parent = nullptr);
    void stopLoop() override;
    const VideoData& getDataVideo() override;
    const VideoDataRTSP& getDataRTSP() override;
    void emitStartRtspStream();
    void emitSendLoadInfo(const QString& str);
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
    StreamContext* m_streamContext;
    QString m_rtspLink;
    QString m_pathVideo;
    QString m_overlayText;
    VideoDataRTSP m_videoDataRTSP;
    VideoData m_videoDataVideo;
    WId m_wid;
    guint m_bus_watch_id;
    //This variable is necessary to run the main loop
    GMainLoop* loop;
    // This function will be called by the pad-added signal
    static void pad_added_rtspsrc(GstElement* src, GstPad* new_pad, VideoDataRTSP* data);
    static void pad_added_video_decoder(GstElement* src, GstPad* new_pad, VideoDataRTSP* data);
    static void pad_added_audio_decoder(GstElement* src, GstPad* new_pad, VideoDataRTSP* data);

    static void pad_added_videosrc(GstElement* src, GstPad* new_pad, VideoData* videoData);
    //Start main pipeline
    void startPipelineRTSP();
    //start video pipeline
     void startPipelineVideo();
    //create Gst elements
    void createGstElementsRTSP();
    void createGstElementsVideo();

signals:
    void videoStopped();
    void startRtspStream();
    void stopRtspStreap();
    void pauseRtspStream();
    void sendLoadInfo(const QString&);

};

#endif // HANDLERGSTREAMER_H
