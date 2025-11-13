#ifndef WORKSREENS_H
#define WORKSREENS_H

#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QVector>
#include "cameralistwidget.h"



class WorkSreens : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs the WorkSreens widget.
     * @param parent Parent widget (can be nullptr).
     */
    explicit WorkSreens(QWidget *parent = nullptr);
public slots:
    /**
     * @brief Splits the screen into the specified number of parts.
     *
     * Creates a grid of Player widgets based on the number of parts requested.
     *
     * @param countScr Number of screen partitions (must be a perfect square — e.g., 1, 4, 9, 16).
     * @callgraph
     */
    void generateScr(int countScr);
    void toggleCameraListWidget();
private:
    QGridLayout* m_grdLayout;
    QHBoxLayout* m_mainLayout;
    CameraListWidget* m_cameraListWidget;
signals:

};

#endif // WORKSREENS_H
