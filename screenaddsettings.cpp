#include "screenaddsettings.h"

ScreenAddSettings::ScreenAddSettings(QWidget* parent) : QDialog(parent)
{
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
    //настройки отображения диалогового окна
    setModal(true);
    setWindowTitle("Настройки подключения");
    resize(200, 400);

    connect(checkAddCover_, &QCheckBox::stateChanged, btnAddCover_, &QPushButton::setEnabled);
    connect(radRTSP_, &QRadioButton::toggled, btnAddRTSP_, &QPushButton::setEnabled);
    connect(radIP_, &QRadioButton::toggled, btnAddIP_, &QPushButton::setEnabled);
    connect(btnAdd_, &QPushButton::clicked, this, &ScreenAddSettings::accept);
    connect(btnCancel_, &QPushButton::clicked, this, &ScreenAddSettings::reject);
    connect(btnAddRTSP_, &QPushButton::clicked, this, &ScreenAddSettings::createInputRtspDisplay);
}

void ScreenAddSettings::createInputRtspDisplay()
{
    rtspInputDisplay_ = new RtspInputDisplay(this);
    rtspInputDisplay_->show();
}
