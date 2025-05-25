#include "esckeyfilter.h"
#include <QKeyEvent>


EscKeyFilter::EscKeyFilter(MainWindow* mainWindow, QObject *parent)
    : QObject{parent}, m_mainWindow{mainWindow}
{

}

bool EscKeyFilter::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Escape)
        {
            if(m_mainWindow->isInFullScreenMode())
            {
                m_mainWindow->disableFullScreen();
                return true;
            }
            else
            {
                return QObject::eventFilter(obj, event);
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
