#include "rtspinputdisplay.h"

RtspInputDisplay::RtspInputDisplay(QWidget* parent) : QDialog(parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_confirmAddRtsp = new QPushButton("Добавить RTSP");
    m_cancelAddRtsp = new QPushButton("Отмена");
    m_confirmCancelLayout = new QHBoxLayout;
    m_confirmCancelLayout->addStretch(1);
    m_confirmCancelLayout->addWidget(m_confirmAddRtsp);
    m_confirmCancelLayout->addWidget(m_cancelAddRtsp);
    m_mainLayout->addSpacing(20);
    m_mainLayout->addLayout(m_confirmCancelLayout, 20);
    //добавится в начало макета
    addSection();
    //настройки окна
    setModal(true);
    setWindowTitle("Настройки подключения");
    //send m_rtspMap
    connect(m_confirmAddRtsp, &QPushButton::clicked, this, &RtspInputDisplay::sendRtspSignal);

}

void RtspInputDisplay::sendRtspSignal()
{
    emit rtspMap(m_rtspMap);
}

void RtspInputDisplay::addSection()
{
    QVBoxLayout* sectLayout = new QVBoxLayout;
    QHBoxLayout* sectRtspInput = new QHBoxLayout;
    QLabel* overlayText = new QLabel("Добавьте название камеры:");
    sectRtspInput->addWidget(overlayText);
    QLineEdit* inputOverlayText = new QLineEdit;
    inputOverlayText->setFixedWidth(100);
    sectRtspInput->addWidget(inputOverlayText);
    QLabel* title = new QLabel("Добавьте RTSP ссылку:");
    sectRtspInput->addWidget(title);
    QLineEdit* inputRtsp = new QLineEdit;
    inputRtsp->setFixedWidth(200);
    sectRtspInput->addWidget(inputRtsp);
    sectLayout->addLayout(sectRtspInput);
    QHBoxLayout* addNextLayout = new QHBoxLayout;
    addNextLayout->addStretch(5);
    QPushButton* nextRtsp = new QPushButton("Далее");
    QPushButton* addRtsp = new QPushButton("Добавить");
    QPushButton* deleteRtsp = new QPushButton("Удалить");
    addNextLayout->addWidget(nextRtsp);
    addNextLayout->addWidget(addRtsp);
    addNextLayout->addWidget(deleteRtsp);
    sectLayout->addLayout(addNextLayout);
    //блок подтверждения(добавить и отмена) + блок разрыва
    int lastTwoLayout = 2;
    //определяем индекс вставки(перед кнопками подтверждения и отмены)
    int indexInsert = m_mainLayout->count() - lastTwoLayout;
    m_mainLayout->insertLayout(indexInsert, sectLayout);
    //добавление секции ввода
    connect(nextRtsp, &QPushButton::clicked, this, &RtspInputDisplay::addSection);
    //добавление ссылки в m_rtspMap
    connect(addRtsp, &QPushButton::clicked, this, [this, inputRtsp, inputOverlayText] ()
            {
        QString overlayText = inputOverlayText->text();
        QString rtspLink = inputRtsp->text();
        m_rtspMap.insert(overlayText, rtspLink);
    });
    //удаление секции
    connect(deleteRtsp, &QPushButton::clicked, this, [this, sectLayout]()
            {
        deleteSection(sectLayout);
    });
}

void RtspInputDisplay::deleteSection(QLayout *layout)
{
    qDebug() << "void RtspInputDisplay::deleteSection(QLayout *layout)";
    if(layout == nullptr)
    {
        return;
    }
    QLayoutItem* item;
    while(layout->count() > 0)
    {
        item = layout->takeAt(0);
        if(QWidget* w = item->widget())
        {
            layout->removeWidget(w);
            w->hide();
            //delete w;
        }
        if(QLayout* l = item->layout())
        {
            deleteSection(l);
        }
        delete item;
    }
}

