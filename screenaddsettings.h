#ifndef SCREENADDSETTINGS_H
#define SCREENADDSETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "rtspinputdisplay.h"
#include "streamconfig.h"
#include "signaltransmitter.h"
#include "covermanager.h"
#include "videosavemanager.h"

class ScreenAddSettings : public QDialog
{
    Q_OBJECT
public:
    ScreenAddSettings(QWidget* parent = nullptr);
    ~ScreenAddSettings();
private:
    QVBoxLayout* m_layout;
    QHBoxLayout* m_layoutHoriz;
    QLabel* m_nameObject;
    QLineEdit* m_inputNameObject;
    QPushButton* m_btnAddCover;
    QPushButton* m_btnAddVideo;
    QPushButton* m_btnAddRTSP;
    QPushButton* m_btnAdd;
    QPushButton* m_btnCancel;
    SignalTransmitter* m_transmitterChangeSettings;
    //объект для ввода rtsp ссылок
    RtspInputDisplay* m_rtspInputDisplay;
    //объект для хранения информации об объекте и его данных для подключения
    StreamConfig* m_currentStreamConfig;
    //object for select and copy a cover
    CoverManager* m_coverManager;
    //object for select and copy a cover
    VideoSaveManager* m_videoSaveManager;
    void writeSettings();
private slots:
    void createInputRtspDisplay();
};

#endif // SCREENADDSETTINGS_H
