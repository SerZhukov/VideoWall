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
    WorkSreens* m_workSreens = nullptr;
    ScreenPartitionButtons* m_scrPartitionBtn = nullptr;
    ScreenAddSettings* m_scrAddSettings = nullptr;
    QToolBar* m_ptb = nullptr;
    QLabel* m_titleLabel = nullptr;
    QToolBar* createToolBar();
    bool m_fullScreen = false;
signals:

};

#endif // MAINWINDOW_H
