#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QKeyEvent>

class LoadingWidget : public QFrame
{
    Q_OBJECT
public:
    explicit LoadingWidget(QWidget *parent = nullptr);
public slots:
    void startAnimation();
    void stopAnimation();
    void setLoadInfo(const QString& text);
    void clearLoadInfo();
    void setTypeAnimation();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    QVBoxLayout* m_mainLayout;
    QLabel* m_areaAnimation;
    QLabel* m_areaLoadInfo;
    QMovie* m_loadAnimation;
signals:
    void interruptLoad();
};

#endif // LOADINGWIDGET_H
