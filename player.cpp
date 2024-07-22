#include "player.h"

Player::Player(QWidget *parent)
    : QWidget{parent}
{
    handler = new HandlerRTSP(rtsp_, this);
    playerWindow = new MainWindow(this);
    screen = new VideoPlayer;
    screen->show();
    handler->setPlayerWindow(playerWindow);
    QObject::connect(handler, &HandlerRTSP::sendFrame, playerWindow, &MainWindow::setFrame);
    QObject::connect(handler, &HandlerRTSP::sendFrame, screen, &VideoPlayer::setFrame);

}

void Player::setRTSP(const std::string &rtsp)
{
    rtsp_ = rtsp;
}

void Player::play()
{
    handler->setRTSP(rtsp_);
    playerWindow->show();
    handler->play();
}

void Player::play_alt()
{
    qDebug() << "void Player::play_alt()";
    handler->setRTSP(rtsp_);

    handler->playVideoFrame();

}
