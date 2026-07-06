#ifndef EVE_H
#define EVE_H

#include "Party.h"
#include "RandomGen.h"

class Eve : public Party
{
private:
    MyVector<int> interceptedBits;
    MyVector<int> interceptedBases;
    int interceptCount;
    RandomGen* rng;

public:
    Eve(long long seed = 999) : interceptCount(0)
    {
        partyName = MyString("Eve");
        role = MyString("Eavesdropper");
        rng = new RandomGen(seed);
    }

    virtual ~Eve()
    {
        delete rng;
    }

    void prepare(int n) override
    {
        bits.clear();
        bases.clear();
        interceptedBits.clear();
        interceptedBases.clear();
        for (int i = 0; i < n; ++i)
        {
            interceptedBases.push_back(rng->nextBit());
        }
    }

    int measure(int photon, int b) override
    {
        return photon & 1;
    }

    int intercept(int photon)
    {
        int eveBasis = rng->nextBit();
        int measured = measure(photon, eveBasis);
        int eveChoice = rng->nextBit();
        interceptedBits.push_back(measured);
        ++interceptCount;
        return eveChoice;
    }

    int getInterceptCount() const
    {
        return interceptCount;
    }
};

#endif
