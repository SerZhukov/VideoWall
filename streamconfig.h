#ifndef STREAMCONFIG_H
#define STREAMCONFIG_H

#include <QObject>
#include <QSet>

class StreamConfig : public QObject
{
    Q_OBJECT
public:
    explicit StreamConfig(QObject *parent = nullptr);
    ~StreamConfig();
private:
    QString name_;
    QSet<QString> rtspSet_;
public:
    const QString& getName() const;
    const QSet<QString>& getRtspSet() const;
public slots:
    void setName(const QString& name);
    void addRtsp(const QSet<QString>& rtspSet);

signals:

};

#endif // STREAMCONFIG_H
