#include "RandomGen.h"
#include <cstdlib>

using namespace std;

RandomGen::RandomGen(long long s) :seed(s)
{
    srand((unsigned int)(seed));
}

void RandomGen::setSeed(long long s)
{
    seed = s;
    srand((unsigned int)(seed));
}

long long RandomGen::next()
{
    return rand();
}

int RandomGen::nextInt(int lo, int hi)
{
    long long r = next();
    int range = hi - lo + 1;
    return (int)(r % range) + lo;
}

int RandomGen::nextBit()
{
    return (int)(next() % 2);
}
