#pragma once
#ifndef XORCIPHER_H
#define XORCIPHER_H

#include "BitwiseCipher.h"
#include "SimpleKeyGenerator.h"

class XORCipher : public BitwiseCipher
{
private:
    SimpleKeyGenerator* keyGen;
    bool outputHex;
    bool blockMode;

public:
    XORCipher(unsigned char k = 0xAB);
    virtual ~XORCipher();

    MyString encrypt(const MyString& text) override;
    MyString decrypt(const MyString& text) override;
    void showInfo() override;
    MyString getName() const override;

    unsigned char xorByte(unsigned char b, unsigned char key) const;
};

#endif
