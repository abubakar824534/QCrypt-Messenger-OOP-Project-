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
    IdealChannel();
    virtual ~IdealChannel();

    int transmit(int photon) override;
    MyString getChannelType() const;
    double getNoiseLevel() const;
    bool isChannelSecure() const;
};

#endif
