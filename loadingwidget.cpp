#include "loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent)
    : QFrame{parent}
{
    m_mainLayout = new QVBoxLayout;
    m_areaAnimation = new QLabel;

    m_areaLoadInfo = new QLabel;
    m_mainLayout->addWidget(m_areaAnimation, 0, Qt::AlignHCenter);
    m_mainLayout->addWidget(m_areaLoadInfo);
    setLayout(m_mainLayout);
    m_loadAnimation = new QMovie(":/resources/load_animation_connect.gif");
    m_areaAnimation->setMovie(m_loadAnimation);
    m_areaAnimation->setScaledContents(true);
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setFocusPolicy(Qt::StrongFocus);

}

void LoadingWidget::startAnimation()
{
    m_loadAnimation->start();
}

void LoadingWidget::stopAnimation()
{
    m_loadAnimation->stop();
}

void LoadingWidget::setLoadInfo(const QString &text)
{
    m_areaLoadInfo->setText(text);
}

void LoadingWidget::clearLoadInfo()
{
    m_areaLoadInfo->clear();
}

void LoadingWidget::setTypeAnimation()
{
    m_areaAnimation->setMovie(m_loadAnimation);
}

void LoadingWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "void LoadingWidget::keyPressEvent(QKeyEvent *event)";
    if(event->key() == Qt::Key_Delete)
    {
        emit interruptLoad();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void LoadingWidget::resizeEvent(QResizeEvent *event)
{
    m_loadAnimation->setScaledSize((event->size())/3);
    QFrame::resizeEvent(event);

    // qDebug() << "QLabel: H - " << m_areaAnimation->size().height() << " W - " << m_areaAnimation->size().width();
    // qDebug() << "QMovie: H - " << m_loadAnimation->currentImage().size().height() << " W - " << m_loadAnimation->currentImage().size().width();
    // qDebug() << "Event: H - " << event->size().height() << " W - " << event->size().width();
}
