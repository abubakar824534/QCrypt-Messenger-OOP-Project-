#ifndef RSACIPHER_H
#define RSACIPHER_H

#include "AsymmetricCipher.h"
#include "PrimeKeyGenerator.h"
#include "ModularArithmetic.h"

class RSACipher : public AsymmetricCipher
{
private:
    long long e;
    long long d;
    long long n;
    PrimeKeyGenerator* keyGen;
    ModularArithmetic* mathEngine;

public:
    RSACipher();
    virtual ~RSACipher();

    MyString encrypt(const MyString& text) override;
    MyString decrypt(const MyString& text) override;
    void showInfo() override;
    MyString getName() const override;
    MyString getRSAStats() const;

    void generateKeys();
    long long modPow(long long base, long long exp, long long m) const;
};

#endif
