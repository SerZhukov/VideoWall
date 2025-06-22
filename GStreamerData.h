#ifndef GSTREAMERDATA_H
#define GSTREAMERDATA_H

#include <gst/gst.h>

struct VideoData {
    GstElement *pipeline = nullptr;
    GstElement *source = nullptr;
    GstElement *convert = nullptr;
    GstElement *textoverlay = nullptr;
    GstElement *sink = nullptr;
    void clear()
    {
        pipeline = nullptr;
        source = nullptr;
        convert = nullptr;
        textoverlay = nullptr;
        sink = nullptr;
    }
};

struct AudioData
{
    GstElement *convert =  nullptr;
    GstElement *resample = nullptr;
    GstElement *volume = nullptr;
    GstElement *sink = nullptr;
    void clear()
    {
        convert =  nullptr;
        resample = nullptr;
        volume = nullptr;
        sink = nullptr;
    }
};

#endif // GSTREAMERDATA_H
