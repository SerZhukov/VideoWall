#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <QWidget>
#include <QThread>
#include "handlerrtsp.h"
#include "videoplayer.h"

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    void setRTSP(const std::string& rtsp);
    void play_alt();
    void play_no_thread();
private:
    HandlerRTSP* handler_;
    VideoPlayer* screen_;
    std::string rtsp_;
    QThread* thread_;
};

#endif // PLAYER_H
