#pragma once
#ifndef IDEALCHANNEL_H
#define IDEALCHANNEL_H

#include "QuantumChannel.h"

class IdealChannel : public QuantumChannel
{
private:
    double lossRate;
    int delay;
    int photonsLost;
    bool isIdeal;

public:
    IdealChannel() : lossRate(0.0), delay(0), photonsLost(0), isIdeal(true)
    {
        channelType = MyString("Ideal");
        noiseLevel = 0.0;
        isSecure = true;
    }

    virtual ~IdealChannel()
    {
    }

    int transmit(int photon) override
    {
        ++photonCount;
        return photon;
    }

    MyString getChannelType() const
    {
        return MyString("Ideal");
    }

    double getNoiseLevel() const
    {
        return 0.0;
    }

    bool isChannelSecure() const
    {
        return true;
    }
};

#endif
