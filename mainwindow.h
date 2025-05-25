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
public slots:
    void enableFullScreen();
    void disableFullScreen();
    bool isInFullScreenMode();
private:
    WorkSreens* m_workSreens;
    ScreenPartitionButtons* m_scrPartitionBtn;
    ScreenAddSettings* m_scrAddSettings;
    QToolBar* m_ptb;
    QToolBar* createToolBar();
    bool m_fullScreen = false;
signals:

};

#endif // MAINWINDOW_H
