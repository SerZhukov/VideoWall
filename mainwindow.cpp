#include "mainwindow.h"
#include <QPalette>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, workSreens_(new WorkSreens(this)), scrPartitionBtn_(new ScreenPartitionButtons(this))
{
    resize(900, 700);
    addToolBar(createToolBar());
    workSreens_->generateScr(4);
    setCentralWidget(workSreens_);
    connect(scrPartitionBtn_, &ScreenPartitionButtons::oneScreens, workSreens_, &WorkSreens::generateScr);
    connect(scrPartitionBtn_, &ScreenPartitionButtons::fourScreens, workSreens_, &WorkSreens::generateScr);
    connect(scrPartitionBtn_, &ScreenPartitionButtons::nineScreens, workSreens_, &WorkSreens::generateScr);
    connect(scrPartitionBtn_, &ScreenPartitionButtons::sixteenScreens, workSreens_, &WorkSreens::generateScr);
}

void MainWindow::openScreenPartitionButtons()
{
    scrPartitionBtn_->show();
}

void MainWindow::openScreenAddSettings()
{
    scrAddSettings_ = new ScreenAddSettings(this);
    if(scrAddSettings_->exec() == QDialog::Accepted)
    {
        qDebug() << "Successful";
    }
    else
    {
        //scrAddSettings_->close();
    }
    delete scrAddSettings_;
}

QToolBar *MainWindow::createToolBar()
{

    QToolBar* ptb = new QToolBar(this);
    ptb->addAction(QPixmap("://resources//icon_add.jpg"), "add object", this, &MainWindow::openScreenAddSettings);
    ptb->addAction(QPixmap("://resources//icon_screens.jpg"), "split screen", this, &MainWindow::openScreenPartitionButtons);
    //создаем объект разделитель
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ptb->addWidget(spacer);
    ptb->addAction(QPixmap("://resources//icon_cam.jpg"), "cam list", workSreens_, &WorkSreens::toggleCameraListWidget);
    QPalette pal = ptb->palette();
    pal.setColor(QPalette::Button, QColor(176, 224, 230));
    ptb->setPalette(pal);
    ptb->setAutoFillBackground(true);
    return ptb;
}

