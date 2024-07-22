#include "mainwindow.h"
#include <QPainter>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    resize(frame_.size());
    painter.drawImage(0, 0, frame_);
    update();
}

void MainWindow::setFrame(const QImage &frame)
{
    frame_ = frame;
}

