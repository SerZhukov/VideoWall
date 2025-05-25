#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    GraphicsView(QWidget *parent = nullptr);
    ~GraphicsView();
protected:
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
        QString m_rtspLink;
        QString m_textOverlay;
        QString m_pathCover;
        void clearDropInfo();
signals:
    void rtspLinkDropped(const QString& rtspLink);
    void coverPathDropped(const QString& coverPath);
    void textOverlayDropped(const QString& rtspLink);
    void startRtspStream();
    void clearScreen();
};

#endif // GRAPHICSVIEW_H
