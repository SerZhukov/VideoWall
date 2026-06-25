#ifndef FULLSCREENWINDOW_H
#define FULLSCREENWINDOW_H

#include <QWidget>

class FullscreenWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FullscreenWindow(QWidget *parent = nullptr);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mouseDoubleClickEvent (QMouseEvent *event) override;

signals:
    void fullScreenRequested(bool enabled);

};

#endif // FULLSCREENWINDOW_H
