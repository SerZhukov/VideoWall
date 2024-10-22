#include "videoplayer.h"
#include <QFileDialog>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}
{
    scene_ = new QGraphicsScene(this);
    view_ = new QGraphicsView(scene_, this);
    view_->setLineWidth(1);
    view_->setFrameStyle(QFrame::Box | QFrame::Plain);
    layout_ = new QVBoxLayout(this);
    layout_->addWidget(view_);
    layout_->setContentsMargins(0,0,0,0);
    setLayout(layout_);
}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::setFrame(const QImage frame)
{
    //не отработана ситуация о ошибке конвертации
    if(!frame_.convertFromImage(frame))
    {
        qDebug() << "Error convert QImage to QPixmap";
    }
    else
    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(frame_);
        scene_->clear();
        scene_->setSceneRect(frame_.rect());
        scene_->addItem(item);
        view_->fitInView(item, Qt::KeepAspectRatio);
        view_->centerOn(item);
    }
}
