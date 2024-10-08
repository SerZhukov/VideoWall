#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QVBoxLayout>


class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~ VideoPlayer();
public slots:
    void setFrame(const QImage frame);
private:
    QPixmap frame_;
    QGraphicsScene* scene_;
    QGraphicsView* view_;
    QGraphicsPixmapItem* item_;
    QVBoxLayout* layout_;
signals:

};

#endif // VIDEOPLAYER_H
