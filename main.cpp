#include <iostream>
#include "player.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include "mainwindow.h"
#include <QApplication>
#include "screenpartitionbuttons.h"
#include "worksreens.h"
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string rtsp_url_1 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=1&stream=1.sdp?real_stream";
    Player player;
    player.setRTSP(rtsp_url_1);
    player.play_alt();
    //player.play_no_thread();
    //MainWindow w;
    //w.show();
    return a.exec();
}
