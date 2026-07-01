#include "EavesdroppedChannel.h"

EavesdroppedChannel::EavesdroppedChannel(long long eveSeed, double errRate) :errorRate(errRate), detectionRisk(errRate), interceptCount(0)
{
    channelType = MyString("Eavesdropped");
    noiseLevel = errRate;
    isSecure = false;
    eve = new Eve(eveSeed);
}

EavesdroppedChannel::~EavesdroppedChannel()
{
    delete eve;
}

int EavesdroppedChannel::transmit(int photon)
{
    ++photonCount;
    ++interceptCount;
    return eve->intercept(photon);
}

MyString EavesdroppedChannel::getChannelType()const
{
    return MyString("Eavesdropped");
}
double EavesdroppedChannel::getNoiseLevel()const
{
    return errorRate;
}
int EavesdroppedChannel::getInterceptCount()const
{
    return interceptCount;
}
bool EavesdroppedChannel::isChannelSecure()const
{
    return false;
}
