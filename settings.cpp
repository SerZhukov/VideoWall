#include "settings.h"

Settings::Settings()
{

}

QSettings* Settings::instance()
{
    static QSettings settings;
    return &settings;
}
