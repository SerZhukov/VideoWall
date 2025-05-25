#include "mainwindow.h"
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, m_workSreens(new WorkSreens(this)), m_scrPartitionBtn(new ScreenPartitionButtons(this))
{
    resize(900, 700);
    addToolBar(createToolBar());
    m_workSreens->generateScr(4);
    setCentralWidget(m_workSreens);
    connect(m_scrPartitionBtn, &ScreenPartitionButtons::oneScreens, m_workSreens, &WorkSreens::generateScr);
    connect(m_scrPartitionBtn, &ScreenPartitionButtons::fourScreens, m_workSreens, &WorkSreens::generateScr);
    connect(m_scrPartitionBtn, &ScreenPartitionButtons::nineScreens, m_workSreens, &WorkSreens::generateScr);
    connect(m_scrPartitionBtn, &ScreenPartitionButtons::sixteenScreens, m_workSreens, &WorkSreens::generateScr);
}

void MainWindow::openScreenPartitionButtons()
{
    m_scrPartitionBtn->show();
}

void MainWindow::openScreenAddSettings()
{
    m_scrAddSettings = new ScreenAddSettings(this);
    if(m_scrAddSettings->exec() == QDialog::Accepted)
    {
        qDebug() << "Successful";
    }
    else
    {
        //m_scrAddSettings->close();
    }
    delete m_scrAddSettings;
}

void MainWindow::enableFullScreen()
{
    m_ptb->hide();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    this->show();
    m_fullScreen = true;
}

void MainWindow::disableFullScreen()
{
    m_ptb->show();
    this->setWindowFlags(Qt::Window);
    this->showNormal();
    this->show();
    m_fullScreen = false;
}

bool MainWindow::isInFullScreenMode()
{
    return m_fullScreen;
}

QToolBar *MainWindow::createToolBar()
{

    m_ptb = new QToolBar(this);
    m_ptb->addAction(QPixmap("://resources//icon_add.jpg"), "add object", this, &MainWindow::openScreenAddSettings);
    m_ptb->addAction(QPixmap("://resources//icon_screens.jpg"), "split screen", this, &MainWindow::openScreenPartitionButtons);
    m_ptb->addAction(QPixmap("://resources//icon_full_screen.jpg"), "full screen", this, &MainWindow::enableFullScreen);
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_ptb->addWidget(spacer);
    m_ptb->addAction(QPixmap("://resources//icon_cam.jpg"), "cam list", m_workSreens, &WorkSreens::toggleCameraListWidget);
    QPalette pal = m_ptb->palette();
    pal.setColor(QPalette::Button, QColor(176, 224, 230));
    m_ptb->setPalette(pal);
    m_ptb->setAutoFillBackground(true);
    m_ptb->setIconSize(QSize(32, 32));
    return m_ptb;
}

