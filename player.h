//Класс для запуска обработчика rtsp ccылок и передачи на кадра на videoplayer.h
#ifndef PLAYER_H
#define PLAYER_H
#include <QWidget>
#include "videoplayer.h"
#include "handlergstreamer.h"
#include <QVBoxLayout>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();
public slots:
    void play();
private:
    HandlerGStreamer* m_handlerGSt;
    VideoPlayer* m_screen;
    QVBoxLayout* m_layout;
};

#endif // PLAYER_H
