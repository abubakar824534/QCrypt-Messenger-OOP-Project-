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
    NoisyChannel(double rate = 0.1, long long seed = 42) : noiseRate(rate), flipProb(rate), rng(seed), disturbCount(0)
    {
        channelType = MyString("Noisy");
        noiseLevel = rate;
        isSecure = true;
    }

    virtual ~NoisyChannel()
    {
    }

    int transmit(int photon) override
    {
        ++photonCount;
        int threshold = (int)(noiseRate * 100.0);
        int roll = rng.nextInt(0, 99);
        if (roll < threshold)
        {
            ++disturbCount;
            return (photon ^ 1);
        }
        return photon;
    }

    double getNoiseLevel() const
    {
        return noiseRate;
    }

    MyString getChannelType() const
    {
        return MyString("Noisy");
    }

    void setNoiseRate(double r)
    {
        noiseRate = r;
        flipProb = r;
        noiseLevel = r;
    }
};

#endif
