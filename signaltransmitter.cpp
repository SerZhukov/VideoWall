#include "signaltransmitter.h"

SignalTransmitter::SignalTransmitter(QObject *parent)
    : QObject{parent}
{

}

void SignalTransmitter::notifySettingsModified()
{
    emit settingsModified();
}
