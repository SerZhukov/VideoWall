#ifndef IGSTREAMERDATAPROVIDER_H
#define IGSTREAMERDATAPROVIDER_H
#include "GStreamerData.h"

class IGStreamerDataProvider
{
public:
    IGStreamerDataProvider();
    virtual ~ IGStreamerDataProvider() = default;
    virtual const VideoData& getDataVideo() = 0;
    virtual const VideoDataRTSP& getDataRTSP() = 0;

};

#endif // IGSTREAMERDATAPROVIDER_H
