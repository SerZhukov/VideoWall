#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Qt>

namespace Roles {
    enum Roles
    {
        Display = Qt::DisplayRole,
        Rtsp = Qt::UserRole + 1,
        Cover,
        Video,
    };
}

#endif // CONSTANTS_H
