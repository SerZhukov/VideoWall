#ifndef RTSPINPUTDISPLAY_H
#define RTSPINPUTDISPLAY_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMultiMap>


class RtspInputDisplay : public QDialog
{
    Q_OBJECT
public:
    RtspInputDisplay(QWidget* parent = nullptr);
public slots:
    //отправка rtsp ссылки
    void sendRtspSignal();  
private:
    //multimap для хранения rtsp ссылок
    QMultiMap<QString, QString> m_rtspMap;
    //основной макет
    QVBoxLayout* m_mainLayout;
    //макет для размещения кнопок подтверждения и отмены
    QHBoxLayout* m_confirmCancelLayout;
    QPushButton* m_confirmAddRtsp;
    QPushButton* m_cancelAddRtsp;
    void addSection();
    //удаление секции
    void deleteSection(QLayout *layout);
signals:
    void rtspMap(const QMultiMap<QString, QString>&);

};

#endif // RTSPINPUTDISPLAY_H
