#include "screenpartitionbuttons.h"

ScreenPartitionButtons::ScreenPartitionButtons(QWidget *parent)
    : QDialog{parent}
{
    resize(100,100);
    layout_ = new QGridLayout;
    btnOnePart_ = new QPushButton("1");
    btnFourPart_ = new QPushButton("4");
    btnNinePart_ = new QPushButton("9");
    btnSixteenPart_ = new QPushButton("16");
    layout_->addWidget(btnOnePart_, 0, 0);
    layout_->addWidget(btnFourPart_, 0, 1);
    layout_->addWidget(btnNinePart_, 1, 0);
    layout_->addWidget(btnSixteenPart_, 1, 1);
    setLayout(layout_);
    setModal(true);
    setWindowTitle("Настройки экрана");
    connect(btnOnePart_, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionOneScreens);
    connect(btnFourPart_, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionFourScreens);
    connect(btnNinePart_, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionNineScreens);
    connect(btnSixteenPart_, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionSixteenScreens);
}

void ScreenPartitionButtons::partitionOneScreens()
{
    emit oneScreens(1);
}

void ScreenPartitionButtons::partitionFourScreens()
{
    emit fourScreens(4);
}

void ScreenPartitionButtons::partitionNineScreens()
{
    emit nineScreens(9);
}

void ScreenPartitionButtons::partitionSixteenScreens()
{
    emit sixteenScreens(16);
}
