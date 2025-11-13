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
    QGridLayout* m_layout;
    QPushButton* m_btnOnePart;
    QPushButton* m_btnFourPart;
    QPushButton* m_btnNinePart;
    QPushButton* m_btnSixteenPart;
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
