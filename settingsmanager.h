#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include "isettingsmanager.h"
#include "mediasource.h"

struct StreamGroupData {
    QMultiMap<QString, QString> rtspLinks;
    QMultiMap<QString, QString> coverPath;

};

class SettingsManager : public QObject, public ISettingsManager
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = nullptr);
    virtual ~ SettingsManager();
    //запись объекта и rtsp ссылок в реестр OC используя функционал QSettings
    void saveData(const QString& nameObject, const QMultiMap<QString, QString>& rtspLinks) override;

    void saveDataAlt(const QString& nameObject, const MediaSource& mediaSource);
    //запись настроек обложки
    void saveCover(const QString& nameObject, const QString& pathCover);
    //выгрузка объектов и rtsp ссылок в QMap    
    //QMap<QString, QMultiMap<QString, QString>> loadData() const override;
    QMap<QString, StreamGroupData> load();
    //сброс всех настроек
    void clearData();
private:
    bool m_isCover = false;
    static QSettings m_settings;
};

#endif // SETTINGSMANAGER_H
