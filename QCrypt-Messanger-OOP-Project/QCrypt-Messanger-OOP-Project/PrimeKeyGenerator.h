#ifndef PRIMEKEYGENERATOR_H
#define PRIMEKEYGENERATOR_H

#include "KeyGenerator.h"
#include <iostream>
#include <cstdlib>

class PrimeKeyGenerator : public KeyGenerator
{
private:
    long long p;
    long long q;
    long long n;
    long long phi;
    long long e;
    long long d;

    long long modPow(long long base, long long exp, long long m)
    {
        if (m == 1)
        {
            return 0;
        }
        long long res = 1;
        base = base % m;
        while (exp > 0)
        {
            if (exp % 2 == 1)
            {
                res = (res * base) % m;
            }
            exp = exp / 2;
            base = (base * base) % m;
        }
        return res;
    }

    long long gcd(long long a, long long b)
    {
        while (b != 0)
        {
            long long t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    long long modInverse(long long a, long long m)
    {
        long long m0 = m, x0 = 0, x1 = 1;
        if (m == 1)
        {
            return 0;
        }
        while (a > 1)
        {
            long long q = a / m;
            long long t = m;
            m = a % m;
            a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0)
        {
            x1 += m0;
        }
        return x1;
    }

    bool isPrime(int num)
    {
        if (num < 2)
        {
            return false;
        }
        if (num == 2)
        {
            return true;
        }
        if (num % 2 == 0)
        {
            return false;
        }
        for (int i = 3; i * i <= num; i += 2)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    int generatePrime(int min, int max)
    {
        int num;
        int range = max - min + 1;
        do
        {
            num = (rand() % range) + min;
        } while (!isPrime(num));
        return num;
    }

public:
    PrimeKeyGenerator() : p(61), q(53), n(3233), phi(3120), e(17), d(2753)
    {
        keyName = MyString("RSA-PrimeKey");
        keySize = 12;
        keyStrength = 12;
        isGenerated = true;
    }

    virtual ~PrimeKeyGenerator()
    {
    }

    void generate() override
    {
        p = generatePrime(60, 200);
        q = generatePrime(60, 200);
        while (p == q)
        {
            q = generatePrime(60, 200);
        }

        n = p * q;
        phi = computePhi();

        e = 3;
        while (gcd(e, phi) != 1)
        {
            e += 2;
        }

        d = modInverse(e, phi);
        isGenerated = true;
    }

    void show() override
    {
        std::cout << "  RSA Key Parameters:" << std::endl;
        std::cout << "  p=" << p << ", q=" << q << ", n=" << n << std::endl;
        std::cout << "  phi(n)=" << phi << std::endl;
        std::cout << "  Public  key (e, n) = (" << e << ", " << n << ")" << std::endl;
        std::cout << "  Private key (d, n) = (" << d << ", " << n << ")" << std::endl;
    }

    long long getPublicE() const
    {
        return e;
    }

    long long getPublicN() const
    {
        return n;
    }

    long long getPrivateD() const
    {
        return d;
    }

    long long computePhi()
    {
        phi = (p - 1) * (q - 1);
        return phi;
    }
};

#endif
