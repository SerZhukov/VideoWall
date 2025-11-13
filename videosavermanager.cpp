#include "videosavemanager.h"

VideoSaveManager::VideoSaveManager(QWidget *parent)
    : QWidget{parent}
{}

QMultiMap<QString, QString> VideoSaveManager::getVideoLinkMap()
{
    return m_videoLinks;
}

const MediaSource &VideoSaveManager::getMediaData()
{
    m_mediaSource.source = m_videoLinks;
    m_mediaSource.type = Type::Video;
    m_mediaSource.settingsGroupName = "Video";
    return m_mediaSource;
}

bool VideoSaveManager::addVideo()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор видео", QDir::homePath(), "Видео (*.mp4 *.avi *.mkv *.mov *.flv *.wmv *.mpeg *.mpg *.webm)");
    if(path.isEmpty())
    {
        return false;
    }
    QString pathUrl = convertUri(path);
    QString nameVideo = getNameVideo(path);
    m_videoLinks.insert(nameVideo, pathUrl);
    return true;
}

QString VideoSaveManager::getNameVideo(const QString &path)
{
    QString fileName = QFileInfo(path).completeBaseName();
    return fileName;
}

QString VideoSaveManager::convertUri(const QString &path)
{
    QUrl url = QUrl::fromLocalFile(path);
    QString pathUrl = url.toString();
    return pathUrl;
}


