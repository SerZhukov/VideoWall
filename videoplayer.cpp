#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}
{

    item = new QGraphicsPixmapItem;
    scene = new QGraphicsScene(QRectF(0, 0, 500, 500), this);
    view = new QGraphicsView(scene, this);
    layout = new QVBoxLayout(this);
    layout->addWidget(view);
    view->show();
    qDebug() << "VideoPlayer::VideoPlayer(QWidget *parent)";

}

VideoPlayer::~VideoPlayer()
{
    qDebug() << "VideoPlayer::~VideoPlayer()";
}

void VideoPlayer::setFrame(const QImage frame)
{
    //qDebug() << "void VideoPlayer::setFrame(const QImage frame)";
    if(!frame_.convertFromImage(frame))
    {
        //qDebug() << "Error convert QImage to QPixmap";
    }
    else
    {
        scene->addPixmap(frame_);
        //qDebug() << "setFrame correct";
    }
}
