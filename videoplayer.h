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
public slots:
    void setFrame(const QImage frame);
private:
    QPixmap frame_;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* item;
    QVBoxLayout* layout;


signals:

};

#endif // VIDEOPLAYER_H