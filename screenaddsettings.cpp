#include <QStringList>
#include <QSet>
#include "screenaddsettings.h"
#include "settingsmanager.h"
#include "signaltransmitter.h"
#include "singletontransmitter.h"

ScreenAddSettings::ScreenAddSettings(QWidget* parent) : QDialog(parent)
{
    //интерфейс настроек объекта
    m_layout = new QVBoxLayout;
    m_nameObject = new QLabel("Введите название объекта:");
    m_nameObject->setFixedHeight(10);
    m_inputNameObject = new QLineEdit;
    m_btnAddCover = new QPushButton("Добавить обложку");
    m_btnAddVideo = new QPushButton("Добавить видео");
    m_btnAddRTSP = new QPushButton("Настройки RTSP");
    m_layout->addWidget(m_nameObject);
    m_layout->addWidget(m_inputNameObject);
    m_layout->addWidget(m_btnAddCover);
    m_layout->addWidget(m_btnAddVideo);
    m_layout->addWidget(m_btnAddRTSP);
    // интерфейс для сохранения или закрытия настроек
    m_btnAdd = new QPushButton("Добавить объект");
    m_btnCancel = new QPushButton("Закрыть");
    m_layoutHoriz = new QHBoxLayout;
    m_layoutHoriz->addWidget(m_btnAdd);
    m_layoutHoriz->addWidget(m_btnCancel);
    m_layout->addLayout(m_layoutHoriz);
    setLayout(m_layout);

    m_currentStreamConfig = new StreamConfig(this);
    m_coverManager = new CoverManager(this);
    m_videoSaveManager = new VideoSaveManager(this);

    //настройки отображения диалогового окна
    setModal(true);
    setWindowTitle("Настройки подключения");
    resize(400, 400);
    connect(m_btnAdd, &QPushButton::clicked, this, &ScreenAddSettings::accept);
    connect(m_btnCancel, &QPushButton::clicked, this, &ScreenAddSettings::reject);
    //создаем виджет ввода rtsp ссылок
    connect(m_btnAddRTSP, &QPushButton::clicked, this, &ScreenAddSettings::createInputRtspDisplay);
    //writes name of object to StreamConfig
    connect(m_inputNameObject, &QLineEdit::editingFinished, this, [this]() {
        m_currentStreamConfig->setName(m_inputNameObject->text());
    });
    //writes name of object to CoverManager
    connect(m_inputNameObject, &QLineEdit::editingFinished, this, [this]() {
        m_coverManager->setNameCover(m_inputNameObject->text());
    });
    //save settings
    connect(m_btnAdd, &QPushButton::clicked, this, &ScreenAddSettings::writeSettings);
    //object singleton transmitting signal about changing settings
     m_transmitterChangeSettings = SingletonTransmitter::instance();
    //open select window a cover
     connect(m_btnAddCover, &QPushButton::clicked, m_coverManager, &CoverManager::importCover);
     //open select window a video
     connect(m_btnAddVideo, &QPushButton::clicked, m_videoSaveManager, &VideoSaveManager::addVideo);
}

ScreenAddSettings::~ScreenAddSettings()
{
}

void ScreenAddSettings::writeSettings()
{
    SettingsManager manager;
    QString nameObject = m_currentStreamConfig->getName();
    QMultiMap<QString, QString> rtspLinks = m_currentStreamConfig->getRtspLinkMap();
    manager.saveData(nameObject, rtspLinks);
    QMultiMap<QString, QString> videoPaths = m_videoSaveManager->getVideoLinkMap();
    manager.saveData(nameObject, videoPaths);
    QString pathCover = m_coverManager->getNewPathCover();
    //pathCover will be empty if user does not choose the cover
    if(!pathCover.isEmpty())
    {
        manager.saveCover(nameObject, pathCover);
    }
    m_transmitterChangeSettings->notifySettingsModified();
}

void ScreenAddSettings::createInputRtspDisplay()
{
    m_rtspInputDisplay = new RtspInputDisplay(this);
    //запись rtsp ссылки в класс хранения данных StreamConfig
    connect(m_rtspInputDisplay, &RtspInputDisplay::rtspMap, m_currentStreamConfig, &StreamConfig::addRtspLink);
    m_rtspInputDisplay->show();
}

