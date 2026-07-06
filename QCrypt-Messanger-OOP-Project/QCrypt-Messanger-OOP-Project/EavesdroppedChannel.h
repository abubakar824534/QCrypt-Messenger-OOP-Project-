#ifndef EAVESDROPPEDCHANNEL_H
#define EAVESDROPPEDCHANNEL_H

#include "QuantumChannel.h"
#include "Eve.h"

class EavesdroppedChannel : public QuantumChannel
{
private:
    Eve* eve;
    double errorRate;
    double detectionRisk;
    int interceptCount;

public:
    EavesdroppedChannel(long long eveSeed = 999, double errRate = 0.25) : errorRate(errRate), detectionRisk(errRate), interceptCount(0)
    {
        channelType = MyString("Eavesdropped");
        noiseLevel = errRate;
        isSecure = false;
        eve = new Eve(eveSeed);
    }

    virtual ~EavesdroppedChannel()
    {
        delete eve;
    }

    int transmit(int photon) override
    {
        ++photonCount;
        ++interceptCount;
        return eve->intercept(photon);
    }

    MyString getChannelType() const
    {
        return MyString("Eavesdropped");
    }

    double getNoiseLevel() const
    {
        return errorRate;
    }

    int getInterceptCount() const
    {
        return interceptCount;
    }

    bool isChannelSecure() const
    {
        return false;
    }
};

#endif
