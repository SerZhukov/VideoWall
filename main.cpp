#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <gst/gst.h>
#include <gst/video/video.h>
#include <glib.h>
#include "esckeyfilter.h"
#include <QStyleFactory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>



MainWindow* mainWindow = nullptr;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    //spdlog::init_thread_pool(8192, 1);
    QScreen* screen = QGuiApplication::primaryScreen();
    QSize sizeScreen = screen->size();
    mainWindow = new MainWindow;
    mainWindow->resize(sizeScreen * 0.6);
    //EscKeyFilter *filter = new EscKeyFilter(mainWindow);
    //a.installEventFilter(filter);
    mainWindow->show();
    //spdlog::shutdown();


    return a.exec();
}
