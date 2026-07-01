#ifndef RANDOMGEN_H
#define RANDOMGEN_H

class RandomGen
{
private:
    long long seed;

public:
    RandomGen(long long s = 42);
    void setSeed(long long s);
    long long next();
    int nextInt(int lo, int hi);
    int nextBit();
};

#endif
