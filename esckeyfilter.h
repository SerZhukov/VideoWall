#ifndef ESCKEYFILTER_H
#define ESCKEYFILTER_H

#include <QObject>
#include "mainwindow.h"

class EscKeyFilter : public QObject
{
    Q_OBJECT
public:
    explicit EscKeyFilter(MainWindow* mainWindow, QObject *parent = nullptr);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    MainWindow* m_mainWindow;



};

#endif // ESCKEYFILTER_H
