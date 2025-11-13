#include "screenpartitionbuttons.h"

ScreenPartitionButtons::ScreenPartitionButtons(QWidget *parent)
    : QDialog{parent}
{
    resize(100,100);
    m_layout = new QGridLayout;
    m_btnOnePart = new QPushButton("1");
    m_btnFourPart = new QPushButton("4");
    m_btnNinePart = new QPushButton("9");
    m_btnSixteenPart = new QPushButton("16");
    m_layout->addWidget(m_btnOnePart, 0, 0);
    m_layout->addWidget(m_btnFourPart, 0, 1);
    m_layout->addWidget(m_btnNinePart, 1, 0);
    m_layout->addWidget(m_btnSixteenPart, 1, 1);
    setLayout(m_layout);
    setModal(true);
    setWindowTitle("Настройки экрана");
    connect(m_btnOnePart, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionOneScreens);
    connect(m_btnFourPart, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionFourScreens);
    connect(m_btnNinePart, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionNineScreens);
    connect(m_btnSixteenPart, &QPushButton::clicked, this, &ScreenPartitionButtons::partitionSixteenScreens);
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
