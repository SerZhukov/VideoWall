#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}
{

    item_ = new QGraphicsPixmapItem;
    scene_ = new QGraphicsScene(QRectF(0, 0, 500, 500), this);
    view_ = new QGraphicsView(scene_, this);
    layout_ = new QVBoxLayout(this);
    layout_->addWidget(view_);
    view_->show();
}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::setFrame(const QImage frame)
{

    if(!frame_.convertFromImage(frame))
    {
        //qDebug() << "Error convert QImage to QPixmap";
    }
    else
    {
        scene_->clear();
        scene_->addPixmap(frame_);
    }
}
