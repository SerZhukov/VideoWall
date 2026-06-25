#include "graphicsview.h"
#include "constants.h"
#include <QGuiApplication>
#include <QStackedLayout>
#include <QMenu>

GraphicsView::GraphicsView(StreamContext* streamContext, QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView{scene, parent}, m_streamContex{streamContext}
{

    setAcceptDrops(true);
    setDragMode(QGraphicsView::NoDrag);


}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView{parent}
{
    setAcceptDrops(true);
    setDragMode(QGraphicsView::NoDrag);

}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::setIsFullScreen(bool isFullScreen)
{
    m_isFullScreen = isFullScreen;
}

void GraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        event->acceptProposedAction();
    }
    else
    {
        qDebug() << "event is not application/x-qabstractitemmodeldatalist";
    }
}

void GraphicsView::dropEvent(QDropEvent *event)
{

    clearDropInfo();
    const QMimeData* mimeData = event->mimeData();
    QByteArray encoded = mimeData->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_6_9);
    while (!stream.atEnd()) {
        int row, col;
        QMap<int,  QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;
        auto it = roleDataMap.begin();
        for(;it != roleDataMap.end(); ++it)
        {
            QVariant dataRole = it.value();
            QString str = dataRole.toString();
            if (it.key() == Roles::Cover)
            {
                m_pathCover = str;
                m_role = Roles::Cover;
            }
            if(it.key() == Roles::Rtsp)
            {
                m_rtspLink = str;
                m_role = Roles::Rtsp;
            }
            if(it.key() == Roles::Display)
            {
                m_textOverlay = str;
            }
            if(it.key() == Roles::Video)
            {
                m_pathVideo = str;
                m_role = Roles::Video;
            }
        }
    }
    if(m_role == Roles::Rtsp)
    {
        emit rtspLinkDropped(m_rtspLink);
        emit textOverlayDropped(m_textOverlay);
        emit startRtspStream();
    }
    if(m_role == Roles::Cover)
    {
        emit coverPathDropped(m_pathCover);
    }
    if(m_role == Roles::Video)
    {
        emit videoPathDropped(m_pathVideo);
        emit startVideoStream();
    }
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(scene()->sceneRect(), Qt::IgnoreAspectRatio);
    QGraphicsView::resizeEvent(event);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_Delete)
    {
        emit clearScreen();
    }
     if(event->key() == Qt::Key_Escape)
    {
         if(m_isFullScreen)
         {
             emit fullScreenRequested(false);
             m_isFullScreen = false;
         }
         else
         {
             emit fullScreenRequested(false);
         }
    }
     else
     {
         QWidget::keyPressEvent(event);
    }
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)";
    if(event->button() == Qt::LeftButton)
    {
        if(!m_isFullScreen)
        {
            emit fullScreenRequested(true);
            m_isFullScreen = true;
        }
        else
        {
            emit fullScreenRequested(false);
            m_isFullScreen = false;
        }
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

// void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
// {
//     QMenu* contextMenu = new QMenu(this);
//     QAction* snapshot = contextMenu->addAction("snapshot");
//     connect(snapshot, &QAction::triggered, this, [this] ()
//             {
//                 emit snapshotRequested();
//                 qDebug() << "emit snapshotRequested();";
//             });
//     contextMenu->popup(event->globalPos());
// }

void GraphicsView::clearDropInfo()
{
    m_rtspLink.clear();
    m_textOverlay.clear();
    m_pathCover.clear();
}








