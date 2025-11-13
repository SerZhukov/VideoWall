#include "player.h"


Player::Player(QWidget *parent)
    : QWidget{parent}
{
    m_streamContex = new StreamContext(this);
    //m_handlerGSt = new HandlerGStreamer(m_streamContex);
    //m_handlerVideo = new HandlerVideoGStreamer(m_streamContex);

    m_handlerGSt = new HandlerGStreamer;
    m_handlerVideo = new HandlerVideoGStreamer;

    m_screen = new VideoPlayer(m_streamContex, this);
    m_screen->setContentsMargins(0,0,0,0);
    //Set Qt window ID for GStreamer to render video into
    m_handlerGSt->setWinId(m_screen->getWId());
    m_handlerVideo->setWinId(m_screen->getWId());
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_screen);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);
    setAcceptDrops(true);
    //Set rtsp link when it is dropped
    connect(m_screen, &VideoPlayer::sendRtspLink, m_handlerGSt, &HandlerGStreamer::setRtsp);
    //Set video path when it is dropped
    connect(m_screen, &VideoPlayer::sendVideoPath, m_handlerVideo, &HandlerVideoGStreamer::setVideoPath);
    //Set text overlay when it is dropped
    connect(m_screen, &VideoPlayer::sendTextOverlay, m_handlerGSt, &HandlerGStreamer::setOverlayText);
    //Start RTSP stream
    connect(m_screen, &VideoPlayer::startRtspStream, this, &Player::playRTSP);
    //Start video
    connect(m_screen, &VideoPlayer::startVideoStream, this, &Player::playVideo);
    //Update widget after stopped video
    connect(m_handlerGSt, &HandlerGStreamer::videoStopped, this, [this](){
        m_screen->update();
    });
    connect(m_handlerVideo, &HandlerVideoGStreamer::videoStopped, this, [this](){
        m_screen->update();
    });
    // Stop the stream and clear the screen when the "Delete" key is pressed
    connect(m_screen, &VideoPlayer::clearScreen, m_handlerGSt, &HandlerGStreamer::stopVideo);
    connect(m_screen, &VideoPlayer::clearScreen, m_handlerVideo, &HandlerVideoGStreamer::stopVideo);
    //Set VideoScreen after LoadScreen
    connect(m_handlerGSt, &HandlerGStreamer::startRtspStream, m_screen, &VideoPlayer::setVideoScreen);
    connect(m_handlerVideo, &HandlerVideoGStreamer::startVideo, m_screen, &VideoPlayer::setVideoScreen);

    connect(m_handlerGSt, &HandlerGStreamer::errorConnectRtspStream, m_screen, &VideoPlayer::setErrorScreen);
}

Player::~Player()
{
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

void Player::playVideo()
{
    if(m_handlerGSt->isRunning())
    {
        m_handlerGSt->stopVideo();
        m_handlerVideo->start();
    }
    else if(m_handlerVideo->isRunning())
    {
        m_handlerVideo->stopVideo();
        m_handlerVideo->start();
    }
    else
    {
        m_handlerVideo->start();
    }
}


void Player::playRTSP()
{
    if(m_handlerGSt->isRunning())
    {
        m_handlerGSt->stopVideo();
        m_handlerGSt->start();
    }
    else if(m_handlerVideo->isRunning())
    {
        m_handlerVideo->stopVideo();
        m_handlerGSt->start();
    }
    else
    {
        m_handlerGSt->start();
    }
}




