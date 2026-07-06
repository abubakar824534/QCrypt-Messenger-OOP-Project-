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
    QuantumChannel() : channelType("Unknown"), noiseLevel(0.0), photonCount(0), isSecure(true)
    {
    }

    virtual ~QuantumChannel()
    {
    }

    virtual int transmit(int photon) = 0;

    MyString getChannelType() const
    {
        return channelType;
    }

    double getNoiseLevel() const
    {
        return noiseLevel;
    }

    bool isChannelSecure() const
    {
        return isSecure;
    }

    void resetChannel()
    {
        photonCount = 0;
        isSecure = true;
    }
};

#endif
