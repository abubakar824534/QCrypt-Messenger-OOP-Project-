#include "IdealChannel.h"

IdealChannel::IdealChannel() :lossRate(0.0), delay(0), photonsLost(0), isIdeal(true)
{
    channelType = MyString("Ideal");
    noiseLevel = 0.0;
    isSecure = true;
}

IdealChannel::~IdealChannel()
{

}

int IdealChannel::transmit(int photon)
{
    ++photonCount;
    return photon;
}

MyString IdealChannel::getChannelType()const
{
    return MyString("Ideal");
}
double IdealChannel::getNoiseLevel()const
{
    return 0.0;
}
bool IdealChannel::isChannelSecure()const
{
    return true;
}
