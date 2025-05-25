#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent)
    : QObject{parent}
{

}

SettingsManager::~SettingsManager()
{

}

QSettings SettingsManager::m_settings("SZ", "VideoWall");

void SettingsManager::saveData(const QString &nameObject, const QMultiMap<QString, QString> &rtspLinks)
{
    m_settings.beginGroup(nameObject);   
    for (auto it = rtspLinks.cbegin(); it != rtspLinks.end(); ++it)
    {
        m_settings.setValue(it.key(), it.value());
    }
    m_settings.endGroup();
}

void SettingsManager::saveCover(const QString &nameObject, const QString &pathCover)
{

    m_settings.beginGroup(nameObject);
    m_settings.setValue("Cover", pathCover);
    m_settings.endGroup();
    m_isCover = true;
}


// QMap<QString, QMultiMap<QString, QString>> SettingsManager::loadData() const
// {
//     QMap<QString, QMultiMap<QString, QString>> objectRtspLinks;
//     const QList groups = m_settings.childGroups();
//     for (const QString& group : groups) {
//         m_settings.beginGroup(group);
//         const QStringList keys = m_settings.allKeys();
//          QMultiMap<QString, QString> rtspLinks;
//         for (const QString& key : keys) {
//             QString rtsp = m_settings.value(key).toString();
//             rtspLinks.insert(key, rtsp);
//         }
//         objectRtspLinks.insert(group, rtspLinks);
//         m_settings.endGroup();
//     }
//     return objectRtspLinks;
// }

QMap<QString, StreamGroupData> SettingsManager::load()
{
    QMap<QString, StreamGroupData> data;
    const QList groups = m_settings.childGroups();
    for (const QString& group : groups) {

        m_settings.beginGroup(group);
        const QStringList keys = m_settings.allKeys();
        QMultiMap<QString, QString> rtspLinks;
        QMultiMap<QString, QString> coverPath;
        for (const QString& key : keys) {
            QString val = m_settings.value(key).toString();
            if(key != "Cover")
            {
                rtspLinks.insert(key, val);
            }
            else
            {
                coverPath.insert(key, val);
            }
        }
        StreamGroupData groupData;
        groupData.rtspLinks = rtspLinks;
        groupData.coverPath = coverPath;
        data.insert(group, groupData);
        m_settings.endGroup();
    }
    return data;
}



void SettingsManager::clearData()
{
    m_settings.clear();
}






