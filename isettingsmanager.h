#ifndef ISETTINGSMANAGER_H
#define ISETTINGSMANAGER_H

#include <QString>
#include <QMap>
#include <QMultiMap>

class ISettingsManager
{
public:
    explicit ISettingsManager();
    virtual ~ISettingsManager() = default;
    virtual void saveData(const QString& nameObject, const QMultiMap<QString, QString>& rtspLinkMap) = 0;
    //virtual  QMap<QString, QMultiMap<QString, QString>> loadData() const = 0;
};

#endif // ISETTINGSMANAGER_H
