//Class performing import the video into the multimap
#ifndef VIDEOSAVEMANAGER_H
#define VIDEOSAVEMANAGER_H

#include <QWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QUrl>

class VideoSaveManager : public QWidget
{
    Q_OBJECT
public:
    explicit VideoSaveManager(QWidget *parent = nullptr);
    QMultiMap<QString, QString> getVideoLinkMap();
private:
    QString getNameVideo(const QString& path);
    QMultiMap<QString, QString> m_videoLinks;
    QString convertUri(const QString& path);
public slots:
    bool addVideo();

};

#endif // VIDEOSAVEMANAGER_H
