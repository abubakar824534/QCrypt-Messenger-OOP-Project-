#ifndef MODULARARITHMETIC_H
#define MODULARARITHMETIC_H

#include "MathEngine.h"

class ModularArithmetic : public MathEngine
{
private:
    long long base;
    long long exponent;
    long long mod;
    long long inverse;

public:
    ModularArithmetic();
    virtual ~ModularArithmetic();

    long long compute(long long a, long long b, long long m) override;
    long long modPow(long long b, long long exp, long long m);
    long long gcd(long long a, long long b);
    long long modInverse(long long a, long long m);
    long long extendedEuclidean(long long a, long long b, long long& x, long long& y);
};

#endif 
