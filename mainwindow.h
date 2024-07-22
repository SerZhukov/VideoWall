#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QImage frame_;
public slots:
    void setFrame(const QImage& frame);


};
#endif // MAINWINDOW_H
