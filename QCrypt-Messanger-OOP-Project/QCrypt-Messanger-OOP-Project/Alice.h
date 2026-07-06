#ifndef ALICE_H
#define ALICE_H

#include "Party.h"
#include "RandomGen.h"
#include "QuantumChannel.h"

class Alice : public Party
{
private:
    MyVector<int> randomBits;
    MyVector<int> randomBases;
    int photonsSent;
    RandomGen* rng;

public:
    Alice(long long seed = 42) : photonsSent(0)
    {
        partyName = MyString("Alice");
        role = MyString("Sender");
        rng = new RandomGen(seed);
    }

    virtual ~Alice()
    {
        delete rng;
    }

    void generateRandomBits(int n)
    {
        randomBits.clear();
        randomBases.clear();
        bits.clear();
        bases.clear();
        for (int i = 0; i < n; ++i)
        {
            int b = rng->nextBit();
            int s = rng->nextBit();
            randomBits.push_back(b);
            randomBases.push_back(s);
            bits.push_back(b);
            bases.push_back(s);
        }
    }

    void prepare(int n) override
    {
        photonsSent = 0;
        generateRandomBits(n);
    }

    int measure(int photon, int b) override
    {
        return -1;
    }

    int sendPhoton(int i, QuantumChannel* ch)
    {
        if (i < 0 || i >= (int)bits.size())
        {
            return 0;
        }
        int photon = bits[i];
        ++photonsSent;
        return ch->transmit(photon);
    }

    int getPhotonsSent() const
    {
        return photonsSent;
    }
};

#endif
