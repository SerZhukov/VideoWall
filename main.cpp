#include "mainwindow.h"
#include <QApplication>
#include <gst/gst.h>
#include <gst/video/video.h>
#include <glib.h>
#include "esckeyfilter.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //SettingsManager settings;
    //settings.clearData();
    //Склад материалов
    QString rtsp_url_1 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=1&stream=0.sdp?real_stream";
    //Въезд
    QString rtsp_url_2 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=2&stream=0.sdp?real_stream";
    //Фасад РЦ-1
    QString rtsp_url_3 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=3&stream=0.sdp?real_stream";
    //КПП
    QString rtsp_url_4 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=4&stream=0.sdp?real_stream";
    //Фасад РЦ-2
    QString rtsp_url_5 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=5&stream=0.sdp?real_stream";
    //Фасад РЦ-3
    QString rtsp_url_6 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=6&stream=0.sdp?real_stream";
    //Строительный городок
    QString rtsp_url_7 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=7&stream=0.sdp?real_stream";
    //Сухой склад
    QString rtsp_url_8 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=9&stream=0.sdp?real_stream";
    //МТК
    QString rtsp_url_9 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=10&stream=0.sdp?real_stream";
    //Сухой склад
    QString rtsp_url_10 = "rtsp://mikvideo.ru:10191/user=admin1&password=mikvideo&channel=11&stream=0.sdp?real_stream";

    MainWindow mainWindow;
    mainWindow.show();
    EscKeyFilter *filter = new EscKeyFilter(&mainWindow);
    a.installEventFilter(filter);

    return a.exec();
}
