#include "handlergstreamer.h"
#include "bus_callback.h"
#include <QByteArray>

HandlerGStreamer::HandlerGStreamer(QObject *parent)
    : QThread{parent}
{
    // Initialize GStreamer
    gst_init(nullptr, nullptr);
}

void HandlerGStreamer::stopLoop()
{
    qDebug() << "void Player::stopLoop()";
    g_main_loop_quit(loop);
}

const VideoData &HandlerGStreamer::getData()
{
    return videoData;
}

HandlerGStreamer::~HandlerGStreamer()
{
    qDebug() << "HandlerGStreamer::~HandlerGStreamer()";
}

void HandlerGStreamer::setRtsp(const QString &rtspLink)
{
    qDebug() << "void HandlerGStreamer::setRtsp(const QString &rtspLink)";
    qDebug() << rtspLink;
    m_rtspLink = rtspLink;
}

void HandlerGStreamer::setWinId(const WId wid)
{
    m_wid = wid;
}

void HandlerGStreamer::setOverlayText(const QString& overlayText)
{
    m_overlayText = overlayText;
}

void HandlerGStreamer::mute()
{
    g_object_set(audioData.volume, "mute", true, nullptr);
}

void HandlerGStreamer::unmute()
{
    g_object_set(audioData.volume, "mute", false, nullptr);
}

void HandlerGStreamer::playVideo()
{
    gst_element_set_state(videoData.pipeline, GST_STATE_PLAYING);
}

void HandlerGStreamer::pauseVideo()
{

    gst_element_set_state(videoData.pipeline, GST_STATE_PAUSED);
}

void HandlerGStreamer::stopVideo()
{
    stopLoop();
    wait();
    emit videoStopped();
}

void HandlerGStreamer::run()
{
    qDebug() << "PLayer::run thread: " << QThread::currentThreadId();
    startPipeline();
}

void HandlerGStreamer::pad_added_video(GstElement *src, GstPad *new_pad, VideoData *videoData)
{
    GstPad *sink_pad = gst_element_get_static_pad (videoData->convert, "sink");
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = nullptr;
    GstStructure *new_pad_struct = nullptr;
    const gchar *new_pad_type = nullptr;

    qDebug() << "Received new pad " << GST_PAD_NAME (new_pad) << " from " << GST_ELEMENT_NAME (src);

    // If our converter is already linked, we have nothing to do here
    if (gst_pad_is_linked (sink_pad)) {
        g_print ("We are already linked. Ignoring.\n");
        // Unreference the sink pad
        gst_object_unref (sink_pad);
        return;
    }

    // Check the new pad's type
    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name (new_pad_struct);
    if (!g_str_has_prefix (new_pad_type, "video/x-raw")) {
        g_print ("It has type '%s' which is not raw video. Ignoring.\n", new_pad_type);
        // Unreference the new pad's caps, if we got them
        if (new_pad_caps != nullptr)
            gst_caps_unref (new_pad_caps);
        // Unreference the sink pad
        gst_object_unref (sink_pad);
        return;
    }
    // Attempt the link
    ret = gst_pad_link (new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
        g_print ("Type is '%s' but link failed.\n", new_pad_type);
    } else {
        g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }
    // Unreference the new pad's caps, if we got them
    if (new_pad_caps != NULL)
        gst_caps_unref (new_pad_caps);
    // Unreference the sink pad
    gst_object_unref (sink_pad);
}

void HandlerGStreamer::pad_added_audio(GstElement *src, GstPad *new_pad, AudioData *audioData)
{
    GstPad *sink_pad = gst_element_get_static_pad(audioData->convert, "sink");
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = nullptr;
    GstStructure *new_pad_struct = nullptr;
    const gchar *new_pad_type = nullptr;
    qDebug() << "Received new pad " << GST_PAD_NAME (new_pad) << " from " << GST_ELEMENT_NAME (src);
    // If our converter is already linked, we have nothing to do here
    if(gst_pad_is_linked(sink_pad))
    {
        qDebug() << "We are already linked. Ignoring.";
        gst_object_unref(sink_pad);
        return;
    }
    // Check the new pad's type
    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name (new_pad_struct);
    if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
        qDebug() << "It has type " << new_pad_type << "which is not raw audio. Ignoring.";
        // Unreference the new pad's caps, if we got them
        if (new_pad_caps != nullptr)
        {
            gst_caps_unref (new_pad_caps);
        }
        // Unreference the sink pad
        gst_object_unref (sink_pad);
        return;
    }
    // Attempt the link
    ret = gst_pad_link (new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
        g_print ("Type is '%s' but link failed.\n", new_pad_type);
    } else {
        g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }
    // Unreference the new pad's caps, if we got them
    if (new_pad_caps != NULL)
    {
        gst_caps_unref (new_pad_caps);
    }
    // Unreference the sink pad
    gst_object_unref (sink_pad);
}

void HandlerGStreamer::startPipeline()
{
     qDebug() << "void HandlerGStreamer::startPipeline()";
    /* Create the elements */
    videoData.source = gst_element_factory_make ("uridecodebin", "source");
    videoData.convert = gst_element_factory_make ("videoconvert", "video_convert");
    videoData.textoverlay = gst_element_factory_make("textoverlay","text");
    videoData.sink = gst_element_factory_make ("d3dvideosink", "video_sink");
    audioData.convert = gst_element_factory_make("audioconvert", "audio_convert");
    audioData.resample = gst_element_factory_make("audioresample", "audio_resample");
    audioData.volume = gst_element_factory_make("volume", "volume");
    audioData.sink = gst_element_factory_make("autoaudiosink", "audio_sink");

    /* Create the empty pipeline */
    videoData.pipeline = gst_pipeline_new ("rtsp-pipeline");

    if (!videoData.pipeline || !videoData.source || !videoData.convert || !videoData.textoverlay || !videoData.sink || !audioData.convert
        ||!audioData.resample ||!audioData.volume ||!audioData.sink) {
        qDebug() << "Not all elements could be created.";
        return;
    }

    //Qt window integration
    if (GST_IS_VIDEO_OVERLAY(videoData.sink))
    {
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(videoData.sink), m_wid);
    }
    else
    {
        qDebug() << "This sink is not support GstVideoOverlay";
    }

    /* Build the pipeline. Note that we are NOT linking the source at this
    point. We will do it later. */
    gst_bin_add_many (GST_BIN (videoData.pipeline), videoData.source, videoData.convert, videoData.textoverlay, videoData.sink,
                     audioData.convert, audioData.sink, audioData.resample, audioData.volume, nullptr);

    if (!gst_element_link_many (videoData.convert, videoData.textoverlay, videoData.sink, nullptr)) {
        qDebug() << "Elements video could not be linked.";
        gst_object_unref (videoData.pipeline);
        return;
    }

    if(!gst_element_link_many(audioData.convert, audioData.resample, audioData.volume, audioData.sink, nullptr))
    {
        qDebug() << "Elements audio could not be linked.";
        gst_object_unref (videoData.pipeline);
        return;
    }

    // Set the URI to play
    QByteArray baRtspLink = m_rtspLink.toUtf8();
    const char* rtspLink = baRtspLink.constData();
    g_object_set(videoData.source, "uri", rtspLink, nullptr);


    //Set the textoverlay
    QByteArray baOverlayText = m_overlayText.toUtf8();
    const char* textOverlay = baOverlayText.constData();
    g_object_set(videoData.textoverlay, "text", textOverlay, "valignment", 2, "font-desc", "Times New Roman, 24",  nullptr);

    /* Connect to the pad-added signal */
    g_signal_connect (videoData.source, "pad-added", G_CALLBACK (pad_added_video), &videoData);
    g_signal_connect (videoData.source, "pad-added", G_CALLBACK (pad_added_audio), &audioData);



    /* Start playing */
    GstStateChangeReturn ret;
    ret = gst_element_set_state (videoData.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        qDebug() << "Unable to set the pipeline to the playing state";
        gst_object_unref (videoData.pipeline);
        return;
    }

    // Listen to the bus
    GstBus *bus;
    bus = gst_element_get_bus (videoData.pipeline);
    bus_watch_id = gst_bus_add_watch(bus, bus_callback, this);
    gst_object_unref(bus);
    loop = g_main_loop_new(nullptr, false);
    g_main_loop_run(loop);

    qDebug() << "Start Free resources";
    // Free resources
    gst_element_set_state (videoData.pipeline, GST_STATE_NULL);
    gst_object_unref(videoData.pipeline);
    g_source_remove (bus_watch_id);
    g_main_loop_unref (loop);
    qDebug() << "Finish Free resources";
}





