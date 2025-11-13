#include "singletontransmitter.h"

SingletonTransmitter::SingletonTransmitter()
{

}

SignalTransmitter *SingletonTransmitter::instance()
{
    static SignalTransmitter transmitter;
    return &transmitter;
}


