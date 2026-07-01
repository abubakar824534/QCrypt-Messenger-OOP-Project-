#include "Alice.h"

Alice::Alice(long long seed) :photonsSent(0)
{
    partyName = MyString("Alice");
    role = MyString("Sender");
    rng = new RandomGen(seed);
}

Alice::~Alice()
{
    delete rng;
}

void Alice::generateRandomBits(int n)
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

void Alice::prepare(int n)
{
    photonsSent = 0;
    generateRandomBits(n);
}

int Alice::measure(int photon, int b)
{
    return -1;
}

int Alice::sendPhoton(int i, QuantumChannel* ch)
{
    if (i < 0 || i >= (int)bits.size())
    {
        return 0;
    }
    int photon = bits[i];
    ++photonsSent;
    return ch->transmit(photon);
}

int Alice::getPhotonsSent()const
{
    return photonsSent;
}
