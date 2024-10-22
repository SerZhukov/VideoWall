#ifndef CAMERALISTWIDGET_H
#define CAMERALISTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTreeView>
#include <QModelIndex>
#include <QMap>

class CameraListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraListWidget(QWidget *parent = nullptr);
private:    
    QVBoxLayout* mainLayout_;
    QStandardItemModel* model_;
    QTreeView* view_;
    QMap<QString, QVector<QString>> data_;
    void setupDataModel(const QMap<QString, QVector<QString>>& data);
public slots:
    void setData(const QMap<QString, QVector<QString>>& data);
};

#endif // CAMERALISTWIDGET_H
