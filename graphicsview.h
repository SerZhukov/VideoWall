
#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include "streamcontext.h"
#include "constants.h"
#include <gst/gst.h>
#include <gst/video/video.h>
#include <glib.h>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(StreamContext* streamContext, QGraphicsScene *scene, QWidget *parent = nullptr);
    GraphicsView(QWidget *parent = nullptr);
    ~GraphicsView();
public slots:
    void setIsFullScreen(bool isFullScreen);
protected:
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mouseDoubleClickEvent (QMouseEvent *event) override;
    //virtual void contextMenuEvent(QContextMenuEvent *event) override;
private:
        StreamContext* m_streamContex;
        QString m_rtspLink;
        QString m_textOverlay;
        QString m_pathCover;
        QString m_pathVideo;
        void clearDropInfo();
        Roles::Roles m_role;
        bool m_isFullScreen = false;
        QWidget* m_parent = nullptr;
        QLayout*  m_layout = nullptr;
signals:
    void rtspLinkDropped(const QString& rtspLink);
    void videoPathDropped(const QString& videoPath);
    void coverPathDropped(const QString& coverPath);
    void textOverlayDropped(const QString& rtspLink);
    void startRtspStream();
    void startVideoStream();
    void clearScreen();
    void fullScreenRequested(bool);
    void snapshotRequested();
};

#endif // GRAPHICSVIEW_H
