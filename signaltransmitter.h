#ifndef SIGNALTRANSMITTER_H
#define SIGNALTRANSMITTER_H

#include <QObject>

class SignalTransmitter : public QObject
{
    Q_OBJECT
public:
    explicit SignalTransmitter(QObject *parent = nullptr);
public slots:
    void notifySettingsModified();

signals:
    void settingsModified();

};

#endif // SIGNALTRANSMITTER_H
