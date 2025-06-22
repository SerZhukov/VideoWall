#include "player.h"


Player::Player(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "Player::Player(QWidget *parent)";
    m_streamContex = new StreamContext(this);
    m_handlerGSt = new HandlerGStreamer(m_streamContex);
    m_screen = new VideoPlayer(m_streamContex, this);
    m_screen->setContentsMargins(0,0,0,0);
    //Set Qt window ID for GStreamer to render video into
    m_handlerGSt->setWinId(m_screen->getWId());
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_screen);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);
    setAcceptDrops(true);
    //Set rtsp link when it is dropped
    connect(m_screen, &VideoPlayer::sendRtspLink, m_handlerGSt, &HandlerGStreamer::setRtsp);
    //Set text overlay when it is dropped
    connect(m_screen, &VideoPlayer::sendTextOverlay, m_handlerGSt, &HandlerGStreamer::setOverlayText);
    //Start RTSP stream
    connect(m_screen, &VideoPlayer::startRtspStream, this, &Player::play);
    //Update widget after stopped video
    connect(m_handlerGSt, &HandlerGStreamer::videoStopped, this, [this](){
        m_screen->update();
    });
    // Stop the stream and clear the screen when the "Delete" key is pressed
    connect(m_screen, &VideoPlayer::clearScreen, m_handlerGSt, &HandlerGStreamer::stopVideo);
    //Set VideoScreen after LoadScreen
    connect(m_handlerGSt, &HandlerGStreamer::startRtspStream, m_screen, &VideoPlayer::setVideoScreen);
}

Player::~Player()
{
    qDebug() << "Player::~Player()";
    if(m_handlerGSt->isRunning())
    {
        m_handlerGSt->stopVideo();
        delete m_handlerGSt;
    }
    else
    {
        delete m_handlerGSt;
    }
}


void Player::play()
{
    if(m_handlerGSt->isRunning())
    {
        m_handlerGSt->stopVideo();
        m_handlerGSt->start();
    }
    else
    {
        m_handlerGSt->start();
    }
}




