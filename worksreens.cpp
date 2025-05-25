#include "worksreens.h"
#include "player.h"
#include <cmath>


WorkSreens::WorkSreens(QWidget *parent)
    : QWidget{parent}
{
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setSpacing(0);
    //компоновка для размещения изображений с камер
    m_grdLayout = new QGridLayout;
    m_grdLayout->setContentsMargins(0,0,0,0);
    m_grdLayout->setSpacing(0);
    m_mainLayout->addLayout(m_grdLayout);
    //класс для размещения списка объектов с камерами
    m_cameraListWidget = new CameraListWidget;
    m_mainLayout->addWidget(m_cameraListWidget);
    setLayout(m_mainLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
}

void WorkSreens::generateScr(int countScr)
{
    QLayoutItem *current;
    while ((current = m_grdLayout->takeAt(0)) != nullptr) {
        delete current->widget();
    }
    int count = sqrt(countScr);
    for (int row = 0; row < count; ++row) {
        for (int column = 0; column < count; ++column) {
            Player* scr = new Player(this);
            m_grdLayout->addWidget(scr, row, column);
        }
    }
}

void WorkSreens::toggleCameraListWidget()
{
    if(m_cameraListWidget->isHidden())
    {
        m_cameraListWidget->show();
        return;
    }
    else
    {
        m_cameraListWidget->hide();
    }
}



