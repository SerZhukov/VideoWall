#ifndef WORKSREENS_H
#define WORKSREENS_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "cameralistwidget.h"
#include <QTextEdit>

class WorkSreens : public QWidget
{
    Q_OBJECT
public:
    explicit WorkSreens(QWidget *parent = nullptr);
public slots:
    void generateScr(int countScr);
    void toggleCameraListWidget();
private:
    QGridLayout* grdLayout_;
    QHBoxLayout* mainLayout_;
    CameraListWidget* cameraListWidget_;


signals:

};

#endif // WORKSREENS_H
