#ifndef NOISYCHANNEL_H
#define NOISYCHANNEL_H

#include "QuantumChannel.h"
#include "RandomGen.h"

class NoisyChannel : public QuantumChannel
{
private:
    double noiseRate;
    double flipProb;
    RandomGen rng;
    int disturbCount;

public:
    NoisyChannel(double rate = 0.1, long long seed = 42);
    virtual ~NoisyChannel();

    int transmit(int photon) override;
    double getNoiseLevel() const;
    void setNoiseRate(double r);
    MyString getChannelType() const;
};

#endif
