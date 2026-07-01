#include "AsymmetricCipher.h"

AsymmetricCipher::AsymmetricCipher() :pubE(17), pubN(3233), privD(2753), privN(3233), keySize2(12), isPadded(false)
{

}

AsymmetricCipher::~AsymmetricCipher()
{

}

void AsymmetricCipher::setPublicKey(long long e, long long n)
{
    pubE = e;
    pubN = n;
}

void AsymmetricCipher::setPrivateKey(long long d, long long n)
{
    privD = d;
    privN = n;
}

long long AsymmetricCipher::getPublicE()const
{
    return pubE;
}

long long AsymmetricCipher::getPublicN()const
{
    return pubN;
}

long long AsymmetricCipher::getPrivateD()const
{
    return privD;
}
