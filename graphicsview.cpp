#include "graphicsview.h"
#include "constants.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView{scene, parent}
{
    setAcceptDrops(true);
    setDragMode(QGraphicsView::NoDrag);
}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView{parent}
{

}

GraphicsView::~GraphicsView()
{

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
    stream.setVersion(QDataStream::Qt_6_5);
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
            }
            if(it.key() == Roles::Rtsp)
            {
                m_rtspLink = str;
            }
            if(it.key() == Roles::Display)
            {
                m_textOverlay = str;
            }
        }
    }
    if(m_pathCover.isEmpty())
    {
        emit rtspLinkDropped(m_rtspLink);
        emit textOverlayDropped(m_textOverlay);
        emit startRtspStream();
    }
    else
    {
        emit coverPathDropped(m_pathCover);
    }
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene()->itemsBoundingRect(), Qt::IgnoreAspectRatio);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_Delete)
    {
        emit clearScreen();
    }
     else
     {
         QWidget::keyPressEvent(event);
    }
}

void GraphicsView::clearDropInfo()
{
    m_rtspLink.clear();
    m_textOverlay.clear();
    m_pathCover.clear();
}






