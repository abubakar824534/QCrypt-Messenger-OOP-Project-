#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <cstdlib>

class RandomGen
{
private:
    long long seed;

public:
    RandomGen(long long s = 42) : seed(s)
    {
        srand((unsigned int)(seed));
    }

    void setSeed(long long s)
    {
        seed = s;
        srand((unsigned int)(seed));
    }

    long long next()
    {
        return rand();
    }

    int nextInt(int lo, int hi)
    {
        long long r = next();
        int range = hi - lo + 1;
        return (int)(r % range) + lo;
    }

    int nextBit()
    {
        return (int)(next() % 2);
    }
};

#endif
