#include "player.h"

Player::Player(QWidget *parent)
    : QWidget{parent}
{
    //thread_= new QThread(this);
    handler_ = new HandlerRTSP(rtsp_, this);
    screen_ = new VideoPlayer;
    screen_->show();
    connect(handler_, &HandlerRTSP::sendFrame, screen_, &VideoPlayer::setFrame);
    //connect(thread_, &QThread::started, handler_, &HandlerRTSP::playVideoFrame);


}

void Player::setRTSP(const std::string &rtsp)
{
    rtsp_ = rtsp;
}


void Player::play_alt()
{
    //qDebug() << "void Player::play_alt()";
    handler_->setRTSP(rtsp_);
    //handler_->playVideoFrame();
    thread_->start();
}

void Player::play_no_thread()
{
    handler_->setRTSP(rtsp_);
    handler_->playVideoFrame();
}
