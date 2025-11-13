//Class performing import the cover into the working directory
#ifndef COVERMANAGER_H
#define COVERMANAGER_H

#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include "mediasource.h"

class CoverManager : public QWidget
{
    Q_OBJECT
public:
    explicit CoverManager(QWidget *parent = nullptr);
    //const QString& getNewPathCover();
    const MediaSource &getMediaData();

private:
    QString m_currentPathCover;
    QString m_newPathCover;
    QString m_nameCover;
    MediaSource m_mediaSource;
    bool selectCover();
    QString getNewPath();
    bool copyCover(const QString& currentPath, const QString& newPath);
    QString getNameCover(const QString &path);
    void addCover();

public slots:
    bool importCover();
    //void setNameCover(const QString& nameCover);
};

#endif // COVERMANAGER_H
