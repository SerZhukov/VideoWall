#ifndef PLAYER_H
#define PLAYER_H
#include "handlerrtsp.h"
#include "mainwindow.h"
#include "videoplayer.h"
#include <iostream>

#include <QWidget>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    void setRTSP(const std::string& rtsp);
    void play();
    void play_alt();
private:
    HandlerRTSP* handler;
    MainWindow* playerWindow;
    VideoPlayer* screen;
    std::string rtsp_;
};

#endif // PLAYER_H
