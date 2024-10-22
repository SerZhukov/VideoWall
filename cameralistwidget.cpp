#include <QStandardItem>
#include "cameralistwidget.h"


CameraListWidget::CameraListWidget(QWidget *parent)
    : QWidget{parent}
{
    view_ = new QTreeView(this);
    model_ = new QStandardItemModel(1, 1, this);
    model_->setHeaderData(0, Qt::Horizontal, "List objects", Qt::DisplayRole);
    view_->setModel(model_);
    mainLayout_ = new QVBoxLayout;
    mainLayout_->addWidget(view_);
    setLayout(mainLayout_);
}

void CameraListWidget::setData(const QMap<QString, QVector<QString> > &data)
{
    auto it = data.begin();
    for(;it != data.end(); ++it)
    {
        QStandardItem* object = new QStandardItem(it.key());
        model_->appendRow(object);
        QVector<QString> rtspLinks = it.value();
        for (const QString& link : rtspLinks)
        {
            QStandardItem* item = new QStandardItem(link);
            object->appendRow(item);
        }
    }
}
