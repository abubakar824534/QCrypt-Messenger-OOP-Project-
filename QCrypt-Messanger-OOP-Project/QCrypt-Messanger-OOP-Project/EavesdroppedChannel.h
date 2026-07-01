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
    EavesdroppedChannel(long long eveSeed = 999, double errRate = 0.25);
    virtual ~EavesdroppedChannel();

    int transmit(int photon) override;
    MyString getChannelType() const;
    double getNoiseLevel() const;
    int getInterceptCount() const;
    bool isChannelSecure() const;
};

#endif
