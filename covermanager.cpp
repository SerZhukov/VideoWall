#include "covermanager.h"


CoverManager::CoverManager(QWidget *parent)
    : QWidget{parent}
{}

// const QString &CoverManager::getNewPathCover()
// {
//     return m_newPathCover;
// }

const MediaSource &CoverManager::getMediaData()
{
    return m_mediaSource;
}

bool CoverManager::selectCover()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор обложки", QDir::homePath(), "Изображения (*.png *.jpg)");
    if(path.isEmpty())
    {
        return false;
    }
    m_currentPathCover = path;
    m_nameCover = getNameCover(m_currentPathCover);
    m_newPathCover = getNewPath();
    return true;
}

QString CoverManager::getNewPath()
{
    QFileInfo fi(m_currentPathCover);
    QString ext = fi.suffix();
    QDir().mkpath(QCoreApplication::applicationDirPath() + "/covers/");
    QString path = QCoreApplication::applicationDirPath() + "/covers/" + m_nameCover + "." + ext;
    qDebug() << path;
    return path;
}

bool CoverManager::copyCover(const QString& currentPath, const QString& newPath)
{
    qDebug() << currentPath;
    qDebug() << newPath;
    bool isCopy = QFile::copy(currentPath, newPath);
    qDebug() << isCopy;
    return isCopy;
}

QString CoverManager::getNameCover(const QString &path)
{

    QString nameCover = QFileInfo(path).completeBaseName();
    qDebug() << nameCover;
    return nameCover;
}

void CoverManager::addCover()
{
    m_mediaSource.source.insert(m_nameCover, m_newPathCover);
    m_mediaSource.type = Type::Cover;
    m_mediaSource.settingsGroupName = "Cover";
}


bool CoverManager::importCover()
{
    if(selectCover())
    {
        if(!m_nameCover.isEmpty())
        {
            if(copyCover(m_currentPathCover, m_newPathCover))
            {
                addCover();
                return true;
            }
        }
    }
    return false;
}

// void CoverManager::setNameCover(const QString &nameCover)
// {
//     m_nameCover = nameCover;
// }
