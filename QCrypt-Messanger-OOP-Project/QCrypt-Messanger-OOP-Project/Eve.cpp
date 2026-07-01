#include "Eve.h"

Eve::Eve(long long seed) :interceptCount(0)
{
    partyName = MyString("Eve");
    role = MyString("Eavesdropper");
    rng = new RandomGen(seed);
}

Eve::~Eve()
{
    delete rng;
}

void Eve::prepare(int n)
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

int Eve::measure(int photon, int b)
{
    return photon & 1;
}

int Eve::intercept(int photon)
{
    int eveBasis = rng->nextBit();
    int measured = measure(photon, eveBasis);
    int eveChoice = rng->nextBit();
    interceptedBits.push_back(measured);
    ++interceptCount;
    return eveChoice;
}

int Eve::getInterceptCount()const
{
    return interceptCount;
}
