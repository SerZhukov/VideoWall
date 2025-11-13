#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent)
    : QObject{parent}
{

}

SettingsManager::~SettingsManager()
{

}

QSettings SettingsManager::m_settings("SZ", "VideoWall");


void SettingsManager::saveData(const QString &nameObject, const MediaSource &mediaSource)
{
    QMultiMap<QString, QString> settingsKeyValues = mediaSource.source;
    QString nameData = mediaSource.settingsGroupName;
    m_settings.beginGroup(nameObject);
    m_settings.beginGroup(nameData);
    for (auto it = settingsKeyValues.cbegin(); it != settingsKeyValues.cend(); ++it)
    {
        m_settings.setValue(it.key(), it.value());
    }
    m_settings.endGroup();
    m_settings.endGroup();
}


QMap<QString, StreamGroupData> SettingsManager::loadAlt()
{
    QMap<QString, StreamGroupData> data;
    const QList objects = m_settings.childGroups();
    for (const QString& object : objects) {
        m_settings.beginGroup(object);
        QMultiMap<QString, QString> rtspLinks;
        QMultiMap<QString, QString> coverPath;
        QMultiMap<QString, QString> videoPath;
        const QList dates = m_settings.childGroups();
        for (const QString& data : dates)
        {
            m_settings.beginGroup(data);
            const QStringList keys = m_settings.allKeys();
            for (const QString& key : keys) {
                QString val = m_settings.value(key).toString();
                if (data == "Rtsp")
                {
                    rtspLinks.insert(key, val);
                }
                if (data == "Cover")
                {
                    coverPath.insert(key, val);
                }
                if (data == "Video")
                {
                    videoPath.insert(key, val);
                }
            }
          m_settings.endGroup();
        }
        StreamGroupData groupData;
        groupData.rtspLinks = rtspLinks;
        groupData.coverPath = coverPath;
        groupData.videoPath = videoPath;
        data.insert(object, groupData);
        m_settings.endGroup();
    }
    return data;    
}

void SettingsManager::clearData()
{
    m_settings.clear();
}

void SettingsManager::remove(const QString& key)
{
    m_settings.remove(key);
}






