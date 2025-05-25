#ifndef SINGLETONTRANSMITTER_H
#define SINGLETONTRANSMITTER_H

#include "signaltransmitter.h"


class SingletonTransmitter
{

 SingletonTransmitter();
 SingletonTransmitter(const SingletonTransmitter&) = delete;
 SingletonTransmitter& operator=(const SingletonTransmitter&) = delete;
 //static SignalTransmitter transmitter;
 public:
 static SignalTransmitter* instance();

};

#endif // SINGLETONTRANSMITTER_H
