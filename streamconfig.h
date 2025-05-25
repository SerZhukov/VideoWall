#ifndef STREAMCONFIG_H
#define STREAMCONFIG_H

#include <QObject>
#include <QMultiMap>

class StreamConfig : public QObject
{
    Q_OBJECT
public:
    explicit StreamConfig(QObject *parent = nullptr);
    ~StreamConfig();

private:
    QString m_name;
    QString m_pathCover;
    QMultiMap<QString, QString> m_rtspMap;

public:
    const QString& getName() const;
    const QString& getPathCover() const;
    const QMultiMap<QString, QString>& getRtspLinkMap() const;

public slots:
    void setName(const QString& name);
    void setPathCover(const QString& path);
    void addRtspLink(const QMultiMap<QString, QString>& rtspMap);

};

#endif // STREAMCONFIG_H
