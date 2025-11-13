#ifndef ERRORWIDGET_H
#define ERRORWIDGET_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <qlabel.h>

class ErrorWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ErrorWidget(QWidget *parent = nullptr);
private:
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_btnLayout;
    QLabel* m_errorScreen;
    QPushButton* m_btnReconnect;
    QPushButton* m_btnClose;
signals:
    void closeErrorScreen();
    void reconnect();
};

#endif // ERRORWIDGET_H
