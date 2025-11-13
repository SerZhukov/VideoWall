#ifndef STREAMCONFIG_H
#define STREAMCONFIG_H

#include <QObject>
#include <QMultiMap>
#include "mediasource.h"

class StreamConfig : public QObject
{
    Q_OBJECT
public:
    explicit StreamConfig(QObject *parent = nullptr);
    ~StreamConfig();

private:
    QString m_name;
    QMultiMap<QString, QString> m_rtspMap;
    MediaSource m_mediaSource;

public:
    const QString& getName() const;
    const MediaSource& getMediaData();

public slots:
    void setName(const QString& name);
    void addRtspLink(const QMultiMap<QString, QString>& rtspMap);

};

#endif // STREAMCONFIG_H
