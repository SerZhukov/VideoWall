#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include "mediasource.h"

struct StreamGroupData {
    QMultiMap<QString, QString> rtspLinks;
    QMultiMap<QString, QString> coverPath;
    QMultiMap<QString, QString> videoPath;
};

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = nullptr);
    virtual ~ SettingsManager();
    //запись объекта и rtsp ссылок в реестр OC используя функционал QSettings
    void saveData(const QString& nameObject, const MediaSource& mediaSource);
    //выгрузка объектов и rtsp ссылок в QMap    
    QMap<QString, StreamGroupData> loadAlt();
    //delete all item
    void clearData();
    //delete one item
    void remove (const QString& key);
private:
    bool m_isCover = false;
    static QSettings m_settings;
};

#endif // SETTINGSMANAGER_H
