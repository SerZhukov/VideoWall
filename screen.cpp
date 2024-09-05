#include "screen.h"

Screen::Screen(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setLineWidth(2);
    resize(200, 200);
    show();
}
