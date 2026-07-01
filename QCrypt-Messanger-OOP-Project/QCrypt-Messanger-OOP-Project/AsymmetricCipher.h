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
    AsymmetricCipher();
    virtual ~AsymmetricCipher();

    void setPublicKey(long long e, long long n);
    void setPrivateKey(long long d, long long n);
    long long getPublicE() const;
    long long getPublicN() const;
    long long getPrivateD() const;
};

#endif
