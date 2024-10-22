#ifndef RTSPINPUTDISPLAY_H
#define RTSPINPUTDISPLAY_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSet>

class RtspInputDisplay : public QDialog
{
    Q_OBJECT
public:
    RtspInputDisplay(QWidget* parent = nullptr);
public slots:
    //отправка rtsp ссылки
    void sendRtspSignal();  
private:
    //set для хранения rtsp ссылок
    QSet<QString> rtspSet_;
    //основной макет
    QVBoxLayout* mainLayout_;
    //макет для размещения кнопок подтверждения и отмены
    QHBoxLayout* confirmCancelLayout_;
    QPushButton* confirmAddRtsp_;
    QPushButton* cancelAddRtsp_;
    void addSection();
    //удаление секции
    void deleteSection(QLayout *layout);
    //для тестирования
    void test();
signals:
    void rtspSent(const QSet<QString>&);
};

#endif // RTSPINPUTDISPLAY_H
