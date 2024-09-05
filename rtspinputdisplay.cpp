#include "rtspinputdisplay.h"

RtspInputDisplay::RtspInputDisplay(QWidget* parent) : QDialog(parent)
{
    mainLayout_ = new QVBoxLayout;
    setLayout(mainLayout_);
    addSection();
    addSection();
    addSection();
    addSection();
    addSection();
}

void RtspInputDisplay::addSection()
{
    QVBoxLayout* sectLayout_ = new QVBoxLayout;
    QLabel* title_ = new QLabel("Добавьте RTSP ссылку");
    sectLayout_->addWidget(title_);
    QLineEdit* inputRtsp_ = new QLineEdit;
    sectLayout_->addWidget(inputRtsp_);
    QHBoxLayout* addNextLayout_ = new QHBoxLayout;
    QPushButton* nextRtsp_ = new QPushButton("След. ссылка");
    QPushButton* addRtsp_ = new QPushButton("Добавить");
    addNextLayout_->addWidget(nextRtsp_);
    addNextLayout_->addWidget(addRtsp_);
    sectLayout_->addLayout(addNextLayout_);
    mainLayout_->addLayout(sectLayout_);
}
