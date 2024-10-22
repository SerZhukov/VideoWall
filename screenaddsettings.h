#ifndef SCREENADDSETTINGS_H
#define SCREENADDSETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QSettings>
#include "rtspinputdisplay.h"
#include "streamconfig.h"

class ScreenAddSettings : public QDialog
{
    Q_OBJECT
public:
    ScreenAddSettings(QWidget* parent = nullptr);
    ~ScreenAddSettings();
private:
    QVBoxLayout* layout_;
    QHBoxLayout* layoutHoriz_;
    QLabel* nameObject_;
    QLineEdit* inputNameObject_;
    QCheckBox* checkAddCover_;
    QPushButton* btnAddCover_;
    QRadioButton* radRTSP_;
    QRadioButton* radIP_;
    QPushButton* btnAddRTSP_;
    QPushButton* btnAddIP_;
    QPushButton* btnAdd_;
    QPushButton* btnCancel_;
    QSettings* settings_;
    //объект для ввода rtsp ссылок
    RtspInputDisplay* rtspInputDisplay_;
    //объект для хранения информации об объекте и его данных для подключения
    StreamConfig* currentStreamConfig_;
    void writeSettings();
private slots:
    void createInputRtspDisplay();
    void test();
signals:
    void settingsSaved();



};

#endif // SCREENADDSETTINGS_H
