#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QDialog>
#include "screenpartitionbuttons.h"
#include "worksreens.h"
#include "screenaddsettings.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private slots:
    void openScreenPartitionButtons();
    void openScreenAddSettings();
private:
    WorkSreens* workSreens_;
    ScreenPartitionButtons* scrPartitionBtn_;
    ScreenAddSettings* scrAddSettings_;
    QToolBar* createToolBar();
signals:

};

#endif // MAINWINDOW_H
