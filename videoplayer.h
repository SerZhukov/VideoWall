//класс для отображения кадра, получает кадр от handlerrtsp.h
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "graphicsview.h"
#include "loadingwidget.h"
#include "streamcontext.h"
#include "errorwidget.h"


class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(StreamContext* streamContext, QWidget *parent = nullptr);

    ~ VideoPlayer();
    enum
    {
        VIDEO_SCREEN,
        LOAD_SCREEN,
        ERROR_SCREEN,
    };
public slots:
    void emitRtspLink(const QString& rtspLink);
    void emitVideoPath(const QString& videoPath);
    void emitTextOverlay(const QString& textOverlay);
    void emitStartRtspStream();
    void emitStartVideoStream();
    void emitClearScreen();
    void setCover(const QString& coverPath);
    WId getWId();
    void setVideoScreen();
    void setErrorScreen();
private:
    StreamContext* m_streamContex = nullptr;
    QGraphicsPixmapItem* m_background = nullptr;
    QGraphicsPixmapItem* m_cover = nullptr;
    QGraphicsTextItem* m_hintText = nullptr;
    QGraphicsScene* m_scene = nullptr;
    GraphicsView * m_view = nullptr;
    LoadingWidget* m_loadingWidget = nullptr;
    ErrorWidget* m_errorWidget = nullptr;
    QVBoxLayout* m_layout = nullptr;
    QStackedLayout* m_stackedLayout = nullptr;
    bool m_setCover = false;
    bool m_setRtspStream = false;
    bool m_setVideoStream = false;
    void deleteCover();
    void setLoadScreen();
signals:
    void sendRtspLink(const QString& rtspLink);
    void sendVideoPath(const QString& videoPath);
    void sendTextOverlay(const QString& textOverlay);
    void startRtspStream();
    void startVideoStream();
    void clearScreen();
};

#endif // VIDEOPLAYER_H
