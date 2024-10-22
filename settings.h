#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>

class Settings
{
    Settings();
    Settings(const Settings& s) = delete;
    Settings& operator=(const Settings& s)= delete;
public:
    static QSettings* instance();

};

#endif // SETTINGS_H
