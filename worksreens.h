#ifndef WORKSREENS_H
#define WORKSREENS_H

#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QVector>
#include "cameralistwidget.h"


class WorkSreens : public QWidget
{
    Q_OBJECT
public:
    explicit WorkSreens(QWidget *parent = nullptr);
public slots:
    void generateScr(int countScr);
    void toggleCameraListWidget();
private:
    QGridLayout* m_grdLayout;
    QHBoxLayout* m_mainLayout;
    CameraListWidget* m_cameraListWidget;
signals:

};

#endif // WORKSREENS_H
