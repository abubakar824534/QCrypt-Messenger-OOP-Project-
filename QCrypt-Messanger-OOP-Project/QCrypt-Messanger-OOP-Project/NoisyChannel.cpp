#include "NoisyChannel.h"

NoisyChannel::NoisyChannel(double rate, long long seed) :noiseRate(rate), flipProb(rate), rng(seed), disturbCount(0)
{
    channelType = MyString("Noisy");
    noiseLevel = rate;
    isSecure = true;
}

NoisyChannel::~NoisyChannel()
{

}

int NoisyChannel::transmit(int photon)
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

double NoisyChannel::getNoiseLevel()const
{
    return noiseRate;
}
MyString NoisyChannel::getChannelType()const
{
    return MyString("Noisy");
}

void NoisyChannel::setNoiseRate(double r)
{
    noiseRate = r;
    flipProb = r;
    noiseLevel = r;
}
