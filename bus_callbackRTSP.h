#ifndef BUS_CALLBACKRTSP_H
#define BUS_CALLBACKRTSP_H

#include <gst/video/video.h>
#include <glib.h>

gboolean bus_callbackRTSP(GstBus *bus, GstMessage *message, gpointer data = nullptr);

#endif // BUS_CALLBACKRTSP_H
