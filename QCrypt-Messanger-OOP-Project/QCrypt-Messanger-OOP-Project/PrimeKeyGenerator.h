#ifndef PRIMEKEYGENERATOR_H
#define PRIMEKEYGENERATOR_H

#include "KeyGenerator.h"

class PrimeKeyGenerator : public KeyGenerator
{
private:
    long long p;
    long long q;
    long long n;
    long long phi;
    long long e;
    long long d;

    long long modPow(long long base, long long exp, long long m);
    long long gcd(long long a, long long b);
    long long modInverse(long long a, long long m);
    bool isPrime(int num);
    int generatePrime(int min, int max);

public:
    PrimeKeyGenerator();
    virtual ~PrimeKeyGenerator();

    void generate() override;
    void show() override;

    long long getPublicE() const;
    long long getPublicN() const;
    long long getPrivateD() const;
    long long computePhi();
};

#endif
