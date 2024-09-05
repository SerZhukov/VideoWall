#ifndef WORKSREENS_H
#define WORKSREENS_H

#include <QWidget>
#include <QGridLayout>

class WorkSreens : public QWidget
{
    Q_OBJECT
public:
    explicit WorkSreens(QWidget *parent = nullptr);
public slots:
    void generateScr(int countScr);
private:
    QGridLayout* grdLayout_;


signals:

};

#endif // WORKSREENS_H
