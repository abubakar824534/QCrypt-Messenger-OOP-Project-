#include "ModularArithmetic.h"

ModularArithmetic::ModularArithmetic() : base(0), exponent(0), mod(1), inverse(0)
{

}

ModularArithmetic::~ModularArithmetic()
{

}

long long ModularArithmetic::compute(long long a, long long b, long long m)
{
    if (m == 0)
    {
        return 0;
    }
    result = ((a % m) * (b % m)) % m;
    return result;
}


long long ModularArithmetic::modPow(long long b, long long exp, long long m)
{
    if (m == 1)
    {
        return 0;
    }
    long long res = 1;
    b = b % m;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            res = (res * b) % m;
        }
        exp = exp / 2;
        b = (b * b) % m;
    }
    return res;
}


long long ModularArithmetic::gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long ModularArithmetic::extendedEuclidean(long long a, long long b, long long& x, long long& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long x1 = 0, y1 = 1;
    x = 1;
    y = 0;
    while (b != 0)
    {
        long long q = a / b;
        long long tmp = b;
        b = a - q * b;
        a = tmp;
        tmp = x1;
        x1 = x - q * x1;
        x = tmp;
        tmp = y1;
        y1 = y - q * y1;
        y = tmp;
    }
    return a;
}

long long ModularArithmetic::modInverse(long long a, long long m)
{
    long long x = 0, y = 0;
    long long g = extendedEuclidean(a, m, x, y);
    if (g != 1)
    {
        return -1;
    }
    inverse = (x % m + m) % m;
    return inverse;
}
