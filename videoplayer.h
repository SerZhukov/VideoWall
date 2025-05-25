//класс для отображения кадра, получает кадр от handlerrtsp.h
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include "graphicsview.h"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~ VideoPlayer();
public slots:
    void emitRtspLink(const QString& rtspLink);
    void emitTextOverlay(const QString& textOverlay);
    void emitStartRtspStream();
    void emitClearScreen();
    void setCover(const QString& coverPath);
    void deleteCover();
    WId getWId();
private:
    QGraphicsPixmapItem* m_background = nullptr;
    QGraphicsPixmapItem* m_cover = nullptr;
    QGraphicsScene* m_scene = nullptr;
    GraphicsView * m_view = nullptr;
    QVBoxLayout* m_layout = nullptr;
    QString m_pathCover;
    bool m_setCover = false;
    bool m_setRtspStream = false;
signals:
    void sendRtspLink(const QString& rtspLink);
    void sendTextOverlay(const QString& textOverlay);
    void startRtspStream();
    void clearScreen();
};

#endif // VIDEOPLAYER_H
