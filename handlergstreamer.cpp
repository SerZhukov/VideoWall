#include "handlergstreamer.h"
#include "bus_callbackRTSP.h"
#include "bus_callback.h"
#include <QByteArray>

HandlerGStreamer::HandlerGStreamer(StreamContext* streamContext, QObject *parent)
    : QThread{parent}, m_streamContext{streamContext}
{
    // Initialize GStreamer
    gst_init(nullptr, nullptr);
    m_videoDataRTSP.clear();
    m_videoDataVideo.clear();

}

void HandlerGStreamer::stopLoop()
{
    qDebug() << "void Player::stopLoop()";
    g_main_loop_quit(loop);
}

const VideoData &HandlerGStreamer::getDataVideo()
{
    return m_videoDataVideo;
}

const VideoDataRTSP &HandlerGStreamer::getDataRTSP()
{
    return m_videoDataRTSP;
}

HandlerGStreamer::~HandlerGStreamer()
{
}

void HandlerGStreamer::setRtsp(const QString &rtspLink)
{
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
    g_object_set(m_videoDataRTSP.audio_volume, "mute", true, nullptr);
}

void HandlerGStreamer::unmute()
{
    g_object_set(m_videoDataRTSP.audio_volume, "mute", false, nullptr);
}

void HandlerGStreamer::playVideo()
{
    gst_element_set_state(m_videoDataRTSP.pipeline, GST_STATE_PLAYING);
}

void HandlerGStreamer::pauseVideo()
{

    gst_element_set_state(m_videoDataRTSP.pipeline, GST_STATE_PAUSED);
}

void HandlerGStreamer::stopVideo()
{
    stopLoop();
    wait();
    emit videoStopped();
}

void HandlerGStreamer::emitStartRtspStream()
{
    emit startRtspStream();
}

void HandlerGStreamer::emitSendLoadInfo(const QString &str)
{
    emit sendLoadInfo(str);
}

void HandlerGStreamer::run()
{
    startPipelineRTSP();
}

void HandlerGStreamer::pad_added_rtspsrc(GstElement *src, GstPad *new_pad, VideoDataRTSP *videoData)
{
    qDebug() << "pad_added_rtspsrc";

    GstCaps *new_pad_caps = nullptr;
    GstStructure *new_pad_struct = nullptr;
    const gchar *new_pad_type = nullptr;
    const gchar *media = nullptr;
    qDebug() << "Received new pad " << GST_PAD_NAME (new_pad) << " from " << GST_ELEMENT_NAME (src);
    // Check the new pad's type
    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name (new_pad_struct);
    if (!g_str_has_prefix (new_pad_type, "application/x-rtp")) {

        g_print ("It has type '%s' which is not application/x-rtp. Ignoring.\n", new_pad_type);
        // Unreference the new pad's caps, if we got them
        if (new_pad_caps != nullptr)
            gst_caps_unref (new_pad_caps);
        return;
    }
    else
    {
        media = gst_structure_get_string(new_pad_struct, "media");
        if(media && g_strcmp0(media, "video") == 0)
         {
             GstPad *sink_pad = gst_element_get_static_pad (videoData->queue, "sink");
            if(!sink_pad)
             {
                 qDebug() << "ERROR: sink_pad is NULL.";
                 return;
            }
             GstPadLinkReturn ret;
             // If our converter is already linked, we have nothing to do here
             if (gst_pad_is_linked (sink_pad)) {
                 g_print ("We are already linked. Ignoring.\n");
                 // Unreference the sink pad
                 gst_object_unref (sink_pad);
                 return;
             }
             // Attempt the link
             ret = gst_pad_link (new_pad, sink_pad);
             if (GST_PAD_LINK_FAILED (ret)) {
                 g_print ("Type is '%s' but link failed.\n", media);
             }
             else
             {
                 g_print ("Link succeeded (type '%s').\n", media);
             }
             // Unreference the new pad's caps, if we got them
             if (new_pad_caps != nullptr)
                 gst_caps_unref (new_pad_caps);
             // Unreference the sink pad
             gst_object_unref (sink_pad);
             return;
        }
        if(media && g_strcmp0(media, "audio") == 0)
            {
            gst_bin_add_many (GST_BIN (videoData->pipeline), videoData->audio_queue, videoData->audio_decoder, videoData->audio_convert, videoData->audio_resample,
                             videoData->audio_volume, videoData->audio_sink, nullptr);

            if(!gst_element_link_many (videoData->audio_convert, videoData->audio_resample,
                                       videoData->audio_volume, videoData->audio_sink, nullptr))
            {
                qDebug() << "Elements audio could not be linked.";
                return;
            }
            if(!gst_element_link_many (videoData->audio_queue, videoData->audio_decoder, nullptr))
            {
                qDebug() << "Elements audio could not be linked.";
                return;
            }
            gst_element_sync_state_with_parent(videoData->audio_queue);
            gst_element_sync_state_with_parent(videoData->audio_decoder);
            gst_element_sync_state_with_parent(videoData->audio_convert);
            gst_element_sync_state_with_parent(videoData->audio_resample);
            gst_element_sync_state_with_parent(videoData->audio_volume);
            gst_element_sync_state_with_parent(videoData->audio_sink);

            GstPad *sink_pad = gst_element_get_static_pad (videoData->audio_queue, "sink");
            if(!sink_pad)
            {
                qDebug() << "ERROR: sink_pad is NULL.";
                return;
            }
            GstPadLinkReturn ret;
            // If our converter is already linked, we have nothing to do here
            if (gst_pad_is_linked (sink_pad)) {
                g_print ("We are already linked. Ignoring.\n");
                // Unreference the sink pad
                gst_object_unref (sink_pad);
                return;
            }
            ret = gst_pad_link (new_pad, sink_pad);
            if (GST_PAD_LINK_FAILED (ret)) {
                g_print ("Type is '%s' but link failed.\n", media);
            }
            else
            {
                g_print ("Link succeeded (type '%s').\n", media);
            }
            // Unreference the new pad's caps, if we got them
            if (new_pad_caps != nullptr)
                gst_caps_unref (new_pad_caps);
            // Unreference the sink pad
            gst_object_unref (sink_pad);
            return;

            }
        g_print ("It has type '%s' which is not video or audio. Ignoring.\n", media);
        // Unreference the new pad's caps, if we got them
        if (new_pad_caps != nullptr)
        gst_caps_unref (new_pad_caps);
        return;
    }
}

void HandlerGStreamer::pad_added_video_decoder(GstElement *src, GstPad *new_pad, VideoDataRTSP *videoData)
{
    qDebug() << "pad_added_video_decoder";
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
        g_print ("It has type '%s' which is not video/x-raw. Ignoring.\n", new_pad_type);
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

void HandlerGStreamer::pad_added_audio_decoder(GstElement *src, GstPad *new_pad, VideoDataRTSP *videoData)
{
    qDebug() << "pad_added_audio_decoder";
    GstPad *sink_pad = gst_element_get_static_pad (videoData->audio_convert, "sink");
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
    if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
        g_print ("It has type '%s' which is not audio/x-raw. Ignoring.\n", new_pad_type);
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

void HandlerGStreamer::pad_added_videosrc(GstElement *src, GstPad *new_pad, VideoData *videoData)
{
    qDebug() << "pad_added_videosrc";
    GstPad *sink_pad = gst_element_get_static_pad (videoData->queue, "sink");
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
        g_print ("It has type '%s' which is not video/x-raw. Ignoring.\n", new_pad_type);
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

void HandlerGStreamer::startPipelineRTSP()
{
    qDebug() << "void HandlerGStreamer::startPipelineRTSP()";
    createGstElementsRTSP();

    if (!m_videoDataRTSP.isValid()) {
        qDebug() << "Not all elements could be created.";
        return;
    }

    //does not use
    //m_streamContext->setVideoData(m_videoData);

    //Qt window integration
    if (GST_IS_VIDEO_OVERLAY(m_videoDataRTSP.sink))
    {
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(m_videoDataRTSP.sink), m_wid);
    }
    else
    {
        qDebug() << "This sink is not support GstVideoOverlay";
    }

    /* Build the pipeline. Note that we are NOT linking the source at this
    point. We will do it later. */
    gst_bin_add_many (GST_BIN (m_videoDataRTSP.pipeline), m_videoDataRTSP.source, m_videoDataRTSP.queue, m_videoDataRTSP.decoder,
                     m_videoDataRTSP.convert, m_videoDataRTSP.textoverlay, m_videoDataRTSP.sink, nullptr);


    if (!gst_element_link_many (m_videoDataRTSP.queue, m_videoDataRTSP.decoder, nullptr)) {
        qDebug() << "Elements video could not be linked.";
        gst_object_unref (m_videoDataRTSP.pipeline);
        return;
    }

    if (!gst_element_link_many (m_videoDataRTSP.convert, m_videoDataRTSP.textoverlay, m_videoDataRTSP.sink, nullptr)) {
        qDebug() << "Elements video could not be linked.";
        gst_object_unref (m_videoDataRTSP.pipeline);
        return;
    }


    // Set the URI to play
    QByteArray baRtspLink = m_rtspLink.toUtf8();
    const char* rtspLink = baRtspLink.constData();
    g_object_set(m_videoDataRTSP.source, "location", rtspLink, nullptr);


    //Set the textoverlay
    QByteArray baOverlayText = m_overlayText.toUtf8();
    const char* textOverlay = baOverlayText.constData();
    g_object_set(m_videoDataRTSP.textoverlay, "text", textOverlay, "valignment", 2, "font-desc", "Times New Roman, 24",  nullptr);

    //Set aspect ratio
    g_object_set(m_videoDataRTSP.sink, "force-aspect-ratio", false, nullptr);


    /* Connect to the pad-added signal */
    g_signal_connect (m_videoDataRTSP.source, "pad-added", G_CALLBACK (pad_added_rtspsrc), &m_videoDataRTSP);
    g_signal_connect (m_videoDataRTSP.decoder, "pad-added", G_CALLBACK (pad_added_video_decoder), &m_videoDataRTSP);
    g_signal_connect (m_videoDataRTSP.audio_decoder, "pad-added", G_CALLBACK (pad_added_audio_decoder), &m_videoDataRTSP);

    /* Start playing */
    GstStateChangeReturn ret;
    ret = gst_element_set_state (m_videoDataRTSP.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        qDebug() << "Unable to set the pipeline to the playing state";
        gst_object_unref (m_videoDataRTSP.pipeline);
        return;
    }
    // Listen to the bus
    GstBus *bus;
    bus = gst_element_get_bus (m_videoDataRTSP.pipeline);
    m_bus_watch_id = gst_bus_add_watch(bus, bus_callbackRTSP, this);
    gst_object_unref(bus);
    loop = g_main_loop_new(nullptr, false);
    g_main_loop_run(loop);
    qDebug() << "Start Free resources";
    // Free resources
    gst_element_set_state (m_videoDataRTSP.pipeline, GST_STATE_NULL);
    gst_object_unref(m_videoDataRTSP.pipeline);
    g_source_remove (m_bus_watch_id);
    g_main_loop_unref (loop);
    m_videoDataRTSP.clear();
    qDebug() << "Finish Free resources";
}

void HandlerGStreamer::startPipelineVideo()
{
    qDebug() << "void HandlerGStreamer::startPipelineVideo()";
    createGstElementsVideo();

    if (!m_videoDataVideo.isValid()) {
        qDebug() << "Not all elements could be created.";
        return;
    }

    //does not use
    //m_streamContext->setVideoData(m_videoData);

    //Qt window integration
    if (GST_IS_VIDEO_OVERLAY(m_videoDataVideo.sink))
    {
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(m_videoDataVideo.sink), m_wid);
    }
    else
    {
        qDebug() << "This sink is not support GstVideoOverlay";
    }

    /* Build the pipeline. Note that we are NOT linking the source at this
    point. We will do it later. */
    gst_bin_add_many (GST_BIN (m_videoDataVideo.pipeline), m_videoDataVideo.source, m_videoDataVideo.queue,
                     m_videoDataVideo.convert, m_videoDataVideo.sink, nullptr);

    if (!gst_element_link_many (m_videoDataVideo.queue, m_videoDataVideo.convert, m_videoDataVideo.sink, nullptr)) {
        qDebug() << "Elements video could not be linked.";
        gst_object_unref (m_videoDataVideo.pipeline);
        return;
    }

    // Set the URI to play
    QByteArray baRtspLink = m_rtspLink.toUtf8();
    const char* pathVideo = baRtspLink.constData();
    g_object_set(m_videoDataVideo.source, "uri", pathVideo, nullptr);


    //Set aspect ratio
    g_object_set(m_videoDataVideo.sink, "force-aspect-ratio", false, nullptr);

    /* Connect to the pad-added signal */
    g_signal_connect (m_videoDataVideo.source, "pad-added", G_CALLBACK (pad_added_videosrc), &m_videoDataVideo);

    /* Start playing */
    GstStateChangeReturn ret;
    ret = gst_element_set_state (m_videoDataVideo.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        qDebug() << "Unable to set the pipeline to the playing state";
        gst_object_unref (m_videoDataVideo.pipeline);
        return;
    }
    // Listen to the bus
    GstBus *bus;
    bus = gst_element_get_bus (m_videoDataVideo.pipeline);
    m_bus_watch_id = gst_bus_add_watch(bus, bus_callback, this);
    gst_object_unref(bus);
    loop = g_main_loop_new(nullptr, false);
    g_main_loop_run(loop);
    qDebug() << "Start Free resources";
    // Free resources
    gst_element_set_state (m_videoDataRTSP.pipeline, GST_STATE_NULL);
    gst_object_unref(m_videoDataRTSP.pipeline);
    g_source_remove (m_bus_watch_id);
    g_main_loop_unref (loop);
    m_videoDataRTSP.clear();
    qDebug() << "Finish Free resources";
}


void HandlerGStreamer::createGstElementsRTSP()
{
    m_videoDataRTSP.pipeline = gst_pipeline_new ("rtsp-pipeline");
    m_videoDataRTSP.source = gst_element_factory_make ("rtspsrc", "source");
    m_videoDataRTSP.queue = gst_element_factory_make ("queue", "queue");
    m_videoDataRTSP.decoder = gst_element_factory_make ("decodebin", "decoder");
    m_videoDataRTSP.convert = gst_element_factory_make ("videoconvert", "convert");
    m_videoDataRTSP.textoverlay = gst_element_factory_make("textoverlay","text");
    m_videoDataRTSP.sink = gst_element_factory_make ("d3dvideosink", "video_sink");
    m_videoDataRTSP.audio_queue = gst_element_factory_make ("queue", "audio_queue");
    m_videoDataRTSP.audio_decoder = gst_element_factory_make ("decodebin", "audio_decoder");
    m_videoDataRTSP.audio_convert = gst_element_factory_make("audioconvert", "audio_convert");
    m_videoDataRTSP.audio_resample = gst_element_factory_make("audioresample", "audio_resample");
    m_videoDataRTSP.audio_volume = gst_element_factory_make("volume", "volume");
    m_videoDataRTSP.audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");
}

void HandlerGStreamer::createGstElementsVideo()
{
    m_videoDataVideo.pipeline = gst_pipeline_new ("video-pipeline");
    m_videoDataVideo.source = gst_element_factory_make ("uridecodebin", "source");
    m_videoDataVideo.queue = gst_element_factory_make ("queue", "queue");
    m_videoDataVideo.convert = gst_element_factory_make ("videoconvert", "convert");
    m_videoDataVideo.sink = gst_element_factory_make ("d3dvideosink", "video_sink");
    m_videoDataVideo.audio_queue = gst_element_factory_make ("queue", "audio_queue");
    m_videoDataVideo.audio_convert = gst_element_factory_make("audioconvert", "audio_convert");
    m_videoDataVideo.audio_resample = gst_element_factory_make("audioresample", "audio_resample");
    m_videoDataVideo.audio_volume = gst_element_factory_make("volume", "volume");
    m_videoDataVideo.audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");
}





