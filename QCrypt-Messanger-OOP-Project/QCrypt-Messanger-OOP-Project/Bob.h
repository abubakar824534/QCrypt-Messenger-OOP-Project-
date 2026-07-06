#ifndef BOB_H
#define BOB_H

#include "Party.h"
#include "RandomGen.h"

class Bob : public Party
{
private:
    MyVector<int> measuredBits;
    MyVector<int> randomBases;
    int photonsReceived;
    RandomGen* rng;

public:
    Bob(long long seed = 123) : photonsReceived(0)
    {
        partyName = MyString("Bob");
        role = MyString("Receiver");
        rng = new RandomGen(seed);
    }

    virtual ~Bob()
    {
        delete rng;
    }

    void prepare(int n) override
    {
        photonsReceived = 0;
        bits.clear();
        bases.clear();
        randomBases.clear();
        measuredBits.clear();
        for (int i = 0; i < n; ++i)
        {
            int b = rng->nextBit();
            randomBases.push_back(b);
            bases.push_back(b);
        }
    }

    int measure(int photon, int b) override
    {
        return photon & 1;
    }

    void receiveAndMeasure(int photon, int basisChoice)
    {
        int bit = measure(photon, 0);
        bits.push_back(bit);
        ++photonsReceived;
    }

    int getPhotonsReceived() const
    {
        return photonsReceived;
    }
};

#endif
