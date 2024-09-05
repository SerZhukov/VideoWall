#ifndef RTSPINPUTDISPLAY_H
#define RTSPINPUTDISPLAY_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class RtspInputDisplay : public QDialog
{
    Q_OBJECT
public:
    RtspInputDisplay(QWidget* parent = nullptr);
private:
    static int counterSectLayout_;
    QVBoxLayout* mainLayout_;
    QPushButton* deleteRtsp_;
    QPushButton* ok_;
    QPushButton* cancel_;
    void addSection();
};

#endif // RTSPINPUTDISPLAY_H
