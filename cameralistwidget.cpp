#include <QStandardItem>
#include "cameralistwidget.h"
#include "singletontransmitter.h"
#include "constants.h"


CameraListWidget::CameraListWidget(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "CameraListWidget::CameraListWidget(QWidget *parent)";
    m_view = new QTreeView(this);
    m_model = new QStandardItemModel(1, 1, this);
    m_model->setHeaderData(0, Qt::Horizontal, "Список объектов", Qt::DisplayRole);
    QFont font("Arial", 14, QFont::Bold, false);
    m_model->setHeaderData(0, Qt::Horizontal, font, Qt::FontRole);
    m_view->setModel(m_model);
    m_view->setDragEnabled(true);
    m_view->setAcceptDrops(true);
    m_view->setDropIndicatorShown(true);
    m_view->setIconSize(QSize(24, 24));
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_view);
    setLayout(m_mainLayout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    //объект одиночка передающий сигнал при изменении настроек
    m_transmitterChangeSettings = SingletonTransmitter::instance();
    //object for load the settings
    m_settingsManager = new SettingsManager(this);
    connect(m_transmitterChangeSettings, &SignalTransmitter::settingsModified, this,
            [this]()
            {
                m_data = m_settingsManager->load();
                setData(m_data);
            });
    //for load on the first launch of the program
    m_data = m_settingsManager->load();
    setData(m_data);
}

void CameraListWidget::setData(const QMap<QString, StreamGroupData> &data)
{
    clearData();
    for(auto it = data.cbegin();it != data.end(); ++it)
    {        
        QStandardItem* object = new QStandardItem(it.key());
        object->setFont(QFont("Arial", 14, QFont::Bold, false));
        m_model->appendRow(object);
        QPixmap covPic(":/resources/icon_cover.png");
        QIcon iconCov(covPic);
        const StreamGroupData groupData = it.value();
        const QMultiMap<QString, QString> coverPath = groupData.coverPath;
        for (auto it = coverPath.cbegin(); it !=coverPath.end(); ++it)
        {
            QStandardItem* item = new QStandardItem(it.key());
            item->setData(it.value(), Roles::Cover);
            item->setFont(QFont("Arial", 14, QFont::Normal, false));
            item->setIcon(iconCov);
            item->setDropEnabled(true);
            object->appendRow(item);
        }       
        QPixmap camPic(":/resources/icon_video_green.png");
        QIcon iconCam(camPic);
        const QMultiMap<QString, QString> rtspLinks = groupData.rtspLinks;
        for (auto it = rtspLinks.cbegin(); it !=rtspLinks.end(); ++it)
        {
            QStandardItem* item = new QStandardItem(it.key());
            item->setData(it.value(), Roles::Rtsp);
            item->setFont(QFont("Arial", 14, QFont::Normal, false));
            item->setIcon(iconCam);
            item->setDropEnabled(true);
            object->appendRow(item);
        }
    }
}

void CameraListWidget::clearData()
{
    m_model->removeRows(0, m_model->rowCount());
}
