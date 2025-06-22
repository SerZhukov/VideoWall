#include "videoplayer.h"

VideoPlayer::VideoPlayer(StreamContext* streamContext, QWidget *parent)
    : QWidget{parent}, m_streamContex{streamContext}
{
    m_scene = new QGraphicsScene;
    m_view = new GraphicsView(m_streamContex, m_scene);

    setAcceptDrops(true);
    m_view->setLineWidth(1);
    m_view->setFrameStyle(QFrame::Box | QFrame::Plain);
    m_loadingWidget = new LoadingWidget;
    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->addWidget(m_view);
    m_stackedLayout->addWidget(m_loadingWidget);
    m_layout = new QVBoxLayout;
    m_layout->addLayout(m_stackedLayout);
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
    //received the signal obout interrupting loading. Stoped rtsp stream and changed screen.
    connect(m_loadingWidget, &LoadingWidget::interruptLoad, this, [this]()
            {
        emit clearScreen();
        setVideoScreen();
    });
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
    setLoadScreen();
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
    m_scene->setSceneRect(cover.rect());
    m_scene ->addItem(m_cover);  
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

void VideoPlayer::setVideoScreen()
{
    m_stackedLayout->setCurrentIndex(VIDEO_SCREEN);
}

void VideoPlayer::setLoadScreen()
{
    m_stackedLayout->setCurrentIndex(LOAD_SCREEN);
    m_loadingWidget->startAnimation();
}

void VideoPlayer::test()
{
    qDebug() << "void VideoPlayer::test()";
}





