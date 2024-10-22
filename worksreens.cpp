#include "worksreens.h"
#include <cmath>
#include "videoplayer.h"


WorkSreens::WorkSreens(QWidget *parent)
    : QWidget{parent}
{
    mainLayout_ = new QHBoxLayout;
    mainLayout_->setSpacing(0);
    //компоновка для размещения изображений с камер
    grdLayout_ = new QGridLayout;
    grdLayout_->setContentsMargins(0,0,0,0);
    grdLayout_->setSpacing(0);
    mainLayout_->addLayout(grdLayout_);
    //класс для размещения списка объектов с камерами
    cameraListWidget_ = new CameraListWidget;
    mainLayout_->addWidget(cameraListWidget_);
    setLayout(mainLayout_);
}

void WorkSreens::generateScr(int countScr)
{
    QLayoutItem *current;
    while ((current = grdLayout_->takeAt(0)) != nullptr) {
        delete current->widget();
        delete current;
    }
    int count = sqrt(countScr);
    for (int row = 0; row < count; ++row) {
        for (int column = 0; column < count; ++column) {
            VideoPlayer* scr = new VideoPlayer(this);
            grdLayout_->addWidget(scr, row, column);
        }
    }
}

void WorkSreens::toggleCameraListWidget()
{
    if(cameraListWidget_->isHidden())
    {
        cameraListWidget_->show();
        return;
    }
    else
    {
        cameraListWidget_->hide();
    }
}
