#ifndef SCREENPARTITIONBUTTONS_H
#define SCREENPARTITIONBUTTONS_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>

class ScreenPartitionButtons : public QDialog
{
    Q_OBJECT
public:
    explicit ScreenPartitionButtons(QWidget *parent = nullptr);
private:
    QGridLayout* layout_;
    QPushButton* btnOnePart_;
    QPushButton* btnFourPart_;
    QPushButton* btnNinePart_;
    QPushButton* btnSixteenPart_;
private slots:
    void partitionOneScreens();
    void partitionFourScreens();
    void partitionNineScreens();
    void partitionSixteenScreens();
signals:
    void oneScreens(int);
    void fourScreens(int);
    void nineScreens(int);
    void sixteenScreens(int);


};

#endif // SCREENPARTITIONBUTTONS_H
