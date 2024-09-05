#ifndef SCREENADDSETTINGS_H
#define SCREENADDSETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include "rtspinputdisplay.h"

class ScreenAddSettings : public QDialog
{
    Q_OBJECT
public:
    ScreenAddSettings(QWidget* parent = nullptr);
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
    RtspInputDisplay* rtspInputDisplay_;
private slots:
    void createInputRtspDisplay();
};

#endif // SCREENADDSETTINGS_H
