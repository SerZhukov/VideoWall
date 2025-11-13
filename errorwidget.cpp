#include "errorwidget.h"

ErrorWidget::ErrorWidget(QWidget *parent)
    : QFrame{parent}
{
    m_mainLayout = new QVBoxLayout;
    m_errorScreen = new QLabel;
    QPixmap errorScreenPic(":/resources/screen_error.png");
    m_errorScreen->setPixmap(errorScreenPic);
    m_errorScreen->setScaledContents(true);
    m_errorScreen->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_mainLayout->addWidget(m_errorScreen);
    m_btnLayout = new QHBoxLayout;
    m_mainLayout->addLayout(m_btnLayout);
    m_btnReconnect = new QPushButton("    Reconnect");
    QPixmap imgBtnReconnect(":/resources/reconnect.png");
    QIcon iconBtnReconnect(imgBtnReconnect);
    m_btnReconnect->setIcon(iconBtnReconnect);
    m_btnReconnect->setIconSize(QSize(25, 25));
    m_btnClose = new QPushButton("    Close");
    QPixmap imgBtnClose(":/resources/close.png");
    QIcon iconBtnClose(imgBtnClose);
    m_btnClose->setIcon(iconBtnClose);
    m_btnClose->setIconSize(QSize(25, 25));
    m_btnLayout->addWidget(m_btnReconnect);
    m_btnLayout->addWidget(m_btnClose);
    setLayout(m_mainLayout);

    connect(m_btnClose, &QPushButton::clicked, this, &ErrorWidget::closeErrorScreen);
    connect(m_btnReconnect, &QPushButton::clicked, this, &ErrorWidget::reconnect);
}



