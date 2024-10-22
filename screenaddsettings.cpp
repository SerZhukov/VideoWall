#include <QStringList>
#include <QSet>
#include "screenaddsettings.h"
#include "settings.h"

ScreenAddSettings::ScreenAddSettings(QWidget* parent) : QDialog(parent)
{   qDebug() << "ScreenAddSettings::ScreenAddSettings";
    //создание объекта Settings для сохранения настроек(паттерн Одиночка)
    settings_ = Settings::instance();
    //интерфейс настроек объекта
    layout_ = new QVBoxLayout;
    nameObject_ = new QLabel("Введите название объекта:");
    nameObject_->setFixedHeight(10);
    inputNameObject_ = new QLineEdit;
    checkAddCover_ = new QCheckBox("Включить обложку объекта в трансляцию");
    btnAddCover_ = new QPushButton("Настройки обложки");
    btnAddCover_->setEnabled(false);
    btnAddRTSP_ = new QPushButton("Настройки RTSP");
    btnAddRTSP_->setEnabled(false);
    btnAddIP_ = new QPushButton("Настройки IP");
    btnAddIP_->setEnabled(false);
    radRTSP_ = new QRadioButton("Подключение по RTSP");
    radIP_ = new QRadioButton("Подключение по IP");
    layout_->addWidget(nameObject_);
    layout_->addWidget(inputNameObject_);
    layout_->addWidget(checkAddCover_);
    layout_->addWidget(btnAddCover_);
    layout_->addWidget(radRTSP_);
    layout_->addWidget(btnAddRTSP_);
    layout_->addWidget(radIP_);
    layout_->addWidget(btnAddIP_);
    // интерфейс для сохранения или закрытия настроек
    btnAdd_ = new QPushButton("Добавить объект");
    btnCancel_ = new QPushButton("Закрыть");
    layoutHoriz_ = new QHBoxLayout;
    layoutHoriz_->addWidget(btnAdd_);
    layoutHoriz_->addWidget(btnCancel_);
    layout_->addLayout(layoutHoriz_);
    setLayout(layout_);
    //создание класса с информацией объекта
    currentStreamConfig_ = new StreamConfig(this);
    //настройки отображения диалогового окна
    setModal(true);
    setWindowTitle("Настройки подключения");
    resize(200, 400);

    connect(checkAddCover_, &QCheckBox::stateChanged, btnAddCover_, &QPushButton::setEnabled);
    connect(radRTSP_, &QRadioButton::toggled, btnAddRTSP_, &QPushButton::setEnabled);
    connect(radIP_, &QRadioButton::toggled, btnAddIP_, &QPushButton::setEnabled);
    connect(btnAdd_, &QPushButton::clicked, this, &ScreenAddSettings::accept);
    connect(btnCancel_, &QPushButton::clicked, this, &ScreenAddSettings::reject);
    //создаем виджет ввода rtsp ссылок
    connect(btnAddRTSP_, &QPushButton::clicked, this, &ScreenAddSettings::createInputRtspDisplay);
    //запись названия объекта в класс хранения данных StreamConfig
    connect(inputNameObject_, &QLineEdit::editingFinished, this, [this]() {
        currentStreamConfig_->setName(inputNameObject_->text());
    });
    //для тестирования
    connect(btnAdd_, &QPushButton::clicked, this, &ScreenAddSettings::test);
}

ScreenAddSettings::~ScreenAddSettings()
{
    writeSettings();
    emit settingsSaved();
    qDebug() << "ScreenAddSettings::~ScreenAddSettings()";
}

void ScreenAddSettings::writeSettings()
{
    qDebug() << "void ScreenAddSettings::writeSettings()";
    QString name = currentStreamConfig_->getName();
    qDebug() << name;
    settings_->beginGroup(name);
    QSet<QString> setRtsp = currentStreamConfig_->getRtspSet();
    int count = 1;
    for (const QString& rtsp : setRtsp) {
        QString cam = QString::number(count);
        settings_->setValue(cam, rtsp);
        qDebug() << cam << rtsp;
        ++count;
    }
    settings_->endGroup();
}

void ScreenAddSettings::createInputRtspDisplay()
{
    rtspInputDisplay_ = new RtspInputDisplay(this);
    //запись rtsp ссылки в класс хранения данных StreamConfig
    connect(rtspInputDisplay_, &RtspInputDisplay::rtspSent, currentStreamConfig_, &StreamConfig::addRtsp);
    rtspInputDisplay_->show();
}

void ScreenAddSettings::test()
{
    QString name = currentStreamConfig_->getName();
    qDebug() << "Test";
    qDebug() << name;
    QSet<QString> temp = currentStreamConfig_->getRtspSet();
    for (const QString& rtsp : temp) {
        qDebug() << rtsp;
    }
    settings_->beginGroup(name);
    QStringList groups = settings_->childKeys();
    qDebug() << groups.count();
    for (const QString& group : groups) {
        qDebug() << group;
    }
    settings_->endGroup();


}
