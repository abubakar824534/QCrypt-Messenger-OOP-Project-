#ifndef QUANTUMCHANNEL_H
#define QUANTUMCHANNEL_H

#include "MyString.h"

class QuantumChannel
{
protected:
    MyString channelType;
    double noiseLevel;
    int photonCount;
    bool isSecure;

public:
    QuantumChannel();
    virtual ~QuantumChannel();

    virtual int transmit(int photon) = 0;

    MyString getChannelType() const;
    double getNoiseLevel() const;
    bool isChannelSecure() const;
    void resetChannel();
};

#endif
