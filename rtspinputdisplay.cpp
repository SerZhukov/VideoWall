#include "rtspinputdisplay.h"

RtspInputDisplay::RtspInputDisplay(QWidget* parent) : QDialog(parent)
{
    mainLayout_ = new QVBoxLayout;
    setLayout(mainLayout_);
    confirmAddRtsp_ = new QPushButton("Добавить RTSP");
    cancelAddRtsp_ = new QPushButton("Отмена");
    confirmCancelLayout_ = new QHBoxLayout;
    confirmCancelLayout_->addWidget(confirmAddRtsp_);
    confirmCancelLayout_->addWidget(cancelAddRtsp_);
    mainLayout_->addSpacing(20);
    mainLayout_->addLayout(confirmCancelLayout_, 20);
    //добавится в начало макета
    addSection();
    //настройки окна
    setModal(true);
    setWindowTitle("Настройки подключения");
    //отправка rtspSet_
    connect(confirmAddRtsp_, &QPushButton::clicked, this, &RtspInputDisplay::sendRtspSignal);
    //для тестирования
    connect(confirmAddRtsp_, &QPushButton::clicked, this, &RtspInputDisplay::test);
}

void RtspInputDisplay::sendRtspSignal()
{
    emit rtspSent(rtspSet_);
}

void RtspInputDisplay::addSection()
{
    QVBoxLayout* sectLayout_ = new QVBoxLayout;
    QLabel* title_ = new QLabel("Добавьте RTSP ссылку:");
    sectLayout_->addWidget(title_);
    QLineEdit* inputRtsp_ = new QLineEdit;
    sectLayout_->addWidget(inputRtsp_);
    QHBoxLayout* addNextLayout_ = new QHBoxLayout;
    QPushButton* nextRtsp_ = new QPushButton("След. ссылка");
    QPushButton* addRtsp_ = new QPushButton("Добавить");
    QPushButton* deleteRtsp_ = new QPushButton("Удалить");
    addNextLayout_->addWidget(nextRtsp_);
    addNextLayout_->addWidget(addRtsp_);
    addNextLayout_->addWidget(deleteRtsp_);
    sectLayout_->addLayout(addNextLayout_);
    //блок подтверждения(добавить и отмена) + блок разрыва
    int lastTwoLayout = 2;
    //определяем индекс вставки(перед кнопками подтверждения и отмены)
    int indexInsert = mainLayout_->count() - lastTwoLayout;
    mainLayout_->insertLayout(indexInsert, sectLayout_);
    //добавление секции ввода
    connect(nextRtsp_, &QPushButton::clicked, this, &RtspInputDisplay::addSection);
    //добавление ссылки в rtspSet_
    connect(addRtsp_, &QPushButton::clicked, this, [this, inputRtsp_] ()
            {
        rtspSet_.insert(inputRtsp_->text());
    });
    //удаление секции
    connect(deleteRtsp_, &QPushButton::clicked, this, [this, sectLayout_]()
            {
        deleteSection(sectLayout_);
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

void RtspInputDisplay::test()
{
    qDebug() << "Test";


}
