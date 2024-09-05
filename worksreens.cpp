#include "worksreens.h"
#include <cmath>
#include "screen.h"

WorkSreens::WorkSreens(QWidget *parent)
    : QWidget{parent}
{
    grdLayout_ = new QGridLayout(this);
    setLayout(grdLayout_);


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
            Screen* scr = new Screen(this);
            grdLayout_->addWidget(scr, row, column);

        }
    }
}
