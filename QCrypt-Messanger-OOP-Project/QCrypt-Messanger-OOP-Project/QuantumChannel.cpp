#include "QuantumChannel.h"

QuantumChannel::QuantumChannel() :channelType("Unknown"), noiseLevel(0.0), photonCount(0), isSecure(true)
{

}

QuantumChannel::~QuantumChannel()
{

}

MyString QuantumChannel::getChannelType()const
{
    return channelType;
}
double QuantumChannel::getNoiseLevel()const
{
    return noiseLevel;
}
bool QuantumChannel::isChannelSecure() const
{
    return isSecure;
}

void QuantumChannel::resetChannel()
{
    photonCount = 0;
    isSecure = true;
}
