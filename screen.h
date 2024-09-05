#ifndef SCREEN_H
#define SCREEN_H

#include <QFrame>

class Screen : public QFrame
{
    Q_OBJECT
public:
    Screen(QWidget *parent = nullptr);
};

#endif // SCREEN_H
