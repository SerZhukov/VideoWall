#include <gst/video/video.h>
#include <glib.h>
#include <QDebug>
#include "GStreamerData.h"
#include "ibuscallback.h"
#include "igstreamerdataprovider.h"
#include "handlergstreamer.h"
#include <QTextStream>

/*Callback function for handling messages from the bus*/

gboolean bus_callback(GstBus *bus, GstMessage *message, gpointer data = nullptr)
{

    //qDebug() << "Recived message: " << GST_MESSAGE_TYPE(message);
    HandlerGStreamer* ptrPlayer = static_cast<HandlerGStreamer*>(data);
    IBusCallback* iBusCallback = dynamic_cast<HandlerGStreamer*>(ptrPlayer);
    IGStreamerDataProvider*  iPlayerData = dynamic_cast<HandlerGStreamer*>(ptrPlayer);

    VideoData dataPlayer = iPlayerData->getDataVideo();
    if(!dataPlayer.pipeline)
    {
        QString logInfo = "CustomData is not valid";
        qDebug() << logInfo;
        ptrPlayer->emitSendLoadInfo(logInfo);
        return false;
    }
    switch (GST_MESSAGE_TYPE(message)){
    case GST_MESSAGE_ERROR:
    {
        GError *err;
        gchar *debug;
        gst_message_parse_error(message, &err, &debug);
        QString logInfo;
        QTextStream stream(&logInfo);
        qDebug() << "Error received from element " << GST_OBJECT_NAME(message->src) << ": "
                 << err->message;
        qDebug() << "Debugging information: " << (debug ? debug : "none");
        stream << "Error received from element " << GST_OBJECT_NAME(message->src) << ": "
               << err->message << '\n' << "Debugging information: " << (debug ? debug : "none");
        ptrPlayer->emitSendLoadInfo(logInfo);
        g_error_free(err);
        g_free(debug);
        //iBusCallback->stopLoop();
        break;
    }
    case GST_MESSAGE_EOS:
    {
        qDebug() << "End-Of-Stream reached.";
        QString logInfo = "End-Of-Stream reached.";
        ptrPlayer->emitSendLoadInfo(logInfo);
        iBusCallback->stopLoop();
        break;
    }
    case GST_MESSAGE_STATE_CHANGED:
        /* We are only interested in state-changed messages from the pipeline */
        if (GST_MESSAGE_SRC(message) == GST_OBJECT(dataPlayer.pipeline))
        {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (message, &old_state, &new_state, &pending_state);
            QString logInfo;
            QTextStream stream(&logInfo);
            qDebug() <<  "Pipeline state changed from " << gst_element_state_get_name (old_state) << " to "
                     << gst_element_state_get_name (new_state);
            stream <<  "Pipeline state changed from " << gst_element_state_get_name (old_state) << " to "
                   << gst_element_state_get_name (new_state);
            ptrPlayer->emitSendLoadInfo(logInfo);
            if(new_state == GST_STATE_PLAYING)
            {
                ptrPlayer->emitStartRtspStream();
            }
        }
        break;
    default:
        break;
    }
    return true;
}
