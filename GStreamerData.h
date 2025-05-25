#ifndef GSTREAMERDATA_H
#define GSTREAMERDATA_H

#include <gst/gst.h>

struct VideoData {
    GstElement *pipeline;
    GstElement *source;
    GstElement *convert;
    GstElement *textoverlay;
    GstElement *sink;
};

struct AudioData
{
    GstElement *convert;
    GstElement *resample;
    GstElement *volume;
    GstElement *sink;
};

#endif // GSTREAMERDATA_H
