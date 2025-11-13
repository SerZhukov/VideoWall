#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <gst/gst.h>
#include <gst/video/video.h>
#include <glib.h>
#include "esckeyfilter.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    QScreen* screen = QGuiApplication::primaryScreen();
    QSize sizeScreen = screen->size();
    MainWindow mainWindow;
    mainWindow.resize(sizeScreen * 0.6);
    EscKeyFilter *filter = new EscKeyFilter(&mainWindow);
    a.installEventFilter(filter);
    mainWindow.show();
    return a.exec();
}
