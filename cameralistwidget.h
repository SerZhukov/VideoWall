#ifndef CAMERALISTWIDGET_H
#define CAMERALISTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTreeView>
#include <QMap>
#include "signaltransmitter.h"
#include "settingsmanager.h"


class CameraListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraListWidget(QWidget *parent = nullptr);
private:
    QVBoxLayout* m_mainLayout;
    QStandardItemModel* m_model;
    QTreeView* m_view;
    SignalTransmitter* m_transmitterChangeSettings;
    SettingsManager* m_settingsManager;
    QMap<QString, StreamGroupData> m_data;
    void clearCameraList();
public slots:
    void setData(const QMap<QString, StreamGroupData>& data);


};

#endif // CAMERALISTWIDGET_H
