#ifndef ASYMMETRICCIPHER_H
#define ASYMMETRICCIPHER_H

#include "Cipher.h"

class AsymmetricCipher : public Cipher
{
protected:
    long long pubE;
    long long pubN;
    long long privD;
    long long privN;
    int keySize2;
    bool isPadded;

public:
    AsymmetricCipher() : pubE(17), pubN(3233), privD(2753), privN(3233), keySize2(12), isPadded(false)
    {
    }

    virtual ~AsymmetricCipher()
    {
    }

    void setPublicKey(long long e, long long n)
    {
        pubE = e;
        pubN = n;
    }

    void setPrivateKey(long long d, long long n)
    {
        privD = d;
        privN = n;
    }

    long long getPublicE() const
    {
        return pubE;
    }

    long long getPublicN() const
    {
        return pubN;
    }

    long long getPrivateD() const
    {
        return privD;
    }
};

#endif
