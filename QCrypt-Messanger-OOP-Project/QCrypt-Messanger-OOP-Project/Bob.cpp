#include "Bob.h"

Bob::Bob(long long seed) :photonsReceived(0)
{
    partyName = MyString("Bob");
    role = MyString("Receiver");
    rng = new RandomGen(seed);
}

Bob::~Bob()
{
    delete rng;
}

void Bob::prepare(int n)
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

int Bob::measure(int photon, int b)
{
    return photon & 1;
}

void Bob::receiveAndMeasure(int photon, int basisChoice)
{
    int bit = measure(photon, 0);
    bits.push_back(bit);
    ++photonsReceived;
}

int Bob::getPhotonsReceived()const
{
    return photonsReceived;
}
