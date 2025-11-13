#include <QStandardItem>
#include <QModelIndex>
#include "cameralistwidget.h"
#include "singletontransmitter.h"
#include "constants.h"


CameraListWidget::CameraListWidget(QWidget *parent)
    : QWidget{parent}
{
    m_view = new QTreeView(this);
    m_model = new QStandardItemModel(1, 1, this);
    m_model->setHeaderData(0, Qt::Horizontal, "List objects", Qt::DisplayRole);
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
    //delete object from camera list
    m_view->addAction("Delete", this, [this]() {
        //clearCameraList();
        //m_settingsManager->clearData();
        deleteItem();
    });
    m_view->setContextMenuPolicy(Qt::ActionsContextMenu);
    //объект одиночка передающий сигнал при изменении настроек
    m_transmitterChangeSettings = SingletonTransmitter::instance();
    //object for load the settings
    m_settingsManager = new SettingsManager(this);
    connect(m_transmitterChangeSettings, &SignalTransmitter::settingsModified, this,
            [this]()
            {
                m_data = m_settingsManager->loadAlt();
                setData(m_data);
            });
    //for load on the first launch of the program
    m_data = m_settingsManager->loadAlt();
    setData(m_data);
}

void CameraListWidget::setData(const QMap<QString, StreamGroupData> &data)
{
    clearCameraList();
    for(auto it = data.cbegin();it != data.cend(); ++it)
    {        
        QStandardItem* object = new QStandardItem(it.key());
        QString nameObject = it.key();
        object->setData(nameObject, Roles::ItemName);
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
            QString itemName = nameObject + "/Cover/" + it.key();
            item->setData(itemName, Roles::ItemName);
            item->setFont(QFont("Arial", 14, QFont::Normal, false));
            item->setIcon(iconCov);
            item->setDropEnabled(true);
            object->appendRow(item);
        }       
        QPixmap camPic(":/resources/icon_video_green.png");
        QIcon iconCam(camPic);
        const QMultiMap<QString, QString> rtspLinks = groupData.rtspLinks;
        for (auto it = rtspLinks.cbegin(); it !=rtspLinks.cend(); ++it)
        {
            QStandardItem* item = new QStandardItem(it.key());
            item->setData(it.value(), Roles::Rtsp);
            QString itemName = nameObject + "/Rtsp/" + it.key();
            item->setData(itemName, Roles::ItemName);
            item->setFont(QFont("Arial", 14, QFont::Normal, false));
            item->setIcon(iconCam);
            item->setDropEnabled(true);
            object->appendRow(item);
        }
        const QMultiMap<QString, QString> videoPath = groupData.videoPath;
        for (auto it = videoPath.cbegin(); it !=videoPath.cend(); ++it)
        {
            QStandardItem* item = new QStandardItem(it.key());
            item->setData(it.value(), Roles::Video);
            QString itemName = nameObject + "/Video/" + it.key();
            item->setData(itemName, Roles::ItemName);
            item->setFont(QFont("Arial", 14, QFont::Normal, false));
            item->setIcon(iconCam);
            item->setDropEnabled(true);
            object->appendRow(item);
        }
    }
}

void CameraListWidget::clearCameraList()
{
    m_model->removeRows(0, m_model->rowCount());
}

void CameraListWidget::deleteItem()
{
    QModelIndex currrentIndex = m_view->currentIndex();
    QVariant nameData = currrentIndex.data(Roles::ItemName);
    QString nameObject = nameData.toString();
    m_settingsManager->remove(nameObject);
    int row = currrentIndex.row();
    QModelIndex parent = currrentIndex.parent();

    m_model->removeRow(row, parent);
    if (!m_model->hasChildren(parent))
    {
        QVariant nameDataParent = parent.data(Roles::ItemName);
        QString nameObjectParent = nameDataParent.toString();
        m_settingsManager->remove(nameObjectParent);
        m_model->removeRow(parent.row(), parent.parent());
    }
}
