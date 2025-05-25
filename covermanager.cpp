#include "covermanager.h"


CoverManager::CoverManager(QWidget *parent)
    : QWidget{parent}
{}

const QString &CoverManager::getNewPathCover()
{
    return m_newPathCover;
}

bool CoverManager::selectCover()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор обложки", QDir::homePath(), "Изображения (*.png *.jpg)");
    if(path.isEmpty())
    {
        return false;
    }
    m_currentPathCover = path;
    return true;
}

QString CoverManager::getNewPath()
{
    QFileInfo fi(m_currentPathCover);
    QString ext = fi.suffix();
    QDir().mkpath(QCoreApplication::applicationDirPath() + "/covers/");
    QString path = QCoreApplication::applicationDirPath() + "/covers/" + m_nameCover + "." + ext;
    return path;
}

bool CoverManager::copyCover(const QString& currentPath, const QString& newPath)
{
    bool isCopy = QFile::copy(currentPath, newPath);
    return isCopy;
}


bool CoverManager::importCover()
{
    if(selectCover())
    {
        if(!m_nameCover.isEmpty())
        {
            QString newPath = getNewPath();
            if(copyCover(m_currentPathCover, newPath))
            {
                m_newPathCover = newPath;
                return true;
            }
        }
    }
    return false;
}

void CoverManager::setNameCover(const QString &nameCover)
{
    m_nameCover = nameCover;
}
