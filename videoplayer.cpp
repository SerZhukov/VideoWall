#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}
{
    m_scene = new QGraphicsScene;
    m_view = new GraphicsView(m_scene);
    m_view->setLineWidth(1);
    m_view->setFrameStyle(QFrame::Box | QFrame::Plain);
    m_layout = new QVBoxLayout;
    m_layout->addWidget(m_view);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);
    QPixmap frame("://resources//start_cover_cam");
    m_background = new QGraphicsPixmapItem(frame);
    m_background->setAcceptDrops(true);
    m_scene->setSceneRect(frame.rect());
    m_scene->addItem(m_background);
    m_view->fitInView(m_background, Qt::IgnoreAspectRatio);
    m_view->centerOn(m_background);
    //received the signal about dropping the RTSP link in GraphicsView
    connect(m_view, &GraphicsView::rtspLinkDropped, this, &VideoPlayer::emitRtspLink);
    //received the signal about dropping the text overlay in GraphicsView
    connect(m_view, &GraphicsView::textOverlayDropped, this, &VideoPlayer::emitTextOverlay);
    //the signal about starting rtsp stream
    connect(m_view, &GraphicsView::startRtspStream, this, &VideoPlayer::emitStartRtspStream);
    //set m_pathCover when the cover is dropped onto the widget
    connect(m_view, &GraphicsView::coverPathDropped, this, &VideoPlayer::setCover);
    //received the signal about clearnig screen(stop rtsp stream) in GraphicsView
    connect(m_view, &GraphicsView::clearScreen, this, &VideoPlayer::emitClearScreen);
}

VideoPlayer::~VideoPlayer()
{
    if(m_cover)
    {
        delete m_cover;
    }
}

void VideoPlayer::emitRtspLink(const QString &rtspLink)
{
    emit sendRtspLink(rtspLink);
}

void VideoPlayer::emitTextOverlay(const QString &textOverlay)
{
    emit sendTextOverlay(textOverlay);
}

void VideoPlayer::emitStartRtspStream()
{
    if(m_setCover)
    {
        deleteCover();
    }
    emit startRtspStream();
    m_setRtspStream = true;
}

void VideoPlayer::emitClearScreen()
{
    if(m_setCover)
    {
        deleteCover();
    }
    else if(m_setRtspStream)
    {
        emit clearScreen();
        m_setRtspStream = false;
    }
    else
    {
        return;
    }
}

void VideoPlayer::setCover(const QString &coverPath)
{
    if(m_setRtspStream)
    {
        emit clearScreen();
        m_setRtspStream = false;
    }
    deleteCover();
    QPixmap cover(coverPath);
    m_cover = new QGraphicsPixmapItem(cover);
    m_scene ->addItem(m_cover);
    m_scene->setSceneRect(cover.rect());
    m_view->fitInView(m_cover, Qt::IgnoreAspectRatio);
    m_view->centerOn(m_cover);
    m_setCover = true;
    m_setRtspStream = false;
}

void VideoPlayer::deleteCover()
{
    if (m_cover)
    {
        m_scene->removeItem(m_cover);
        delete m_cover;
        m_cover = nullptr;
        m_setCover = false;
    }
}


WId VideoPlayer::getWId()
{
    return m_view->winId();
}



