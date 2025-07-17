#ifndef GSTREAMERDATA_H
#define GSTREAMERDATA_H

#include <gst/gst.h>

struct VideoData
{
    GstElement *pipeline = nullptr;
    GstElement *source = nullptr;
    GstElement *queue = nullptr;
    GstElement *convert = nullptr;
    GstElement *sink = nullptr;
    GstElement *audio_queue = nullptr;
    GstElement *audio_convert =  nullptr;
    GstElement *audio_resample = nullptr;
    GstElement *audio_volume = nullptr;
    GstElement *audio_sink = nullptr;
    void clear()
    {
        pipeline = nullptr;
        source = nullptr;
        queue = nullptr;
        convert = nullptr;
        sink = nullptr;
        audio_queue = nullptr;
        audio_convert =  nullptr;
        audio_resample = nullptr;
        audio_volume = nullptr;
        audio_sink = nullptr;
    }
    bool isValid()
    {
        return (pipeline && source && queue && convert  && sink && audio_convert
                && audio_queue && audio_resample && audio_volume && audio_sink);
    }
};


struct VideoDataRTSP
{
    GstElement *pipeline = nullptr;
    GstElement *source = nullptr;
    GstElement *queue = nullptr;
    GstElement *decoder = nullptr;
    GstElement *convert = nullptr;
    GstElement *textoverlay = nullptr;
    GstElement *sink = nullptr;
    GstElement *audio_queue = nullptr;
    GstElement *audio_decoder = nullptr;
    GstElement *audio_convert =  nullptr;
    GstElement *audio_resample = nullptr;
    GstElement *audio_volume = nullptr;
    GstElement *audio_sink = nullptr;
    void clear()
    {
        pipeline = nullptr;
        source = nullptr;
        queue = nullptr;
        decoder = nullptr;
        convert = nullptr;
        textoverlay = nullptr;
        sink = nullptr;
        audio_queue = nullptr;
        audio_decoder = nullptr;
        audio_convert =  nullptr;
        audio_resample = nullptr;
        audio_volume = nullptr;
        audio_sink = nullptr;
    }
    bool isValid()
    {
        return (pipeline && source && queue && decoder && convert && textoverlay && sink && audio_convert
                && audio_queue && audio_decoder && audio_resample && audio_volume && audio_sink);
    }
};


#endif // GSTREAMERDATA_H
