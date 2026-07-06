#pragma once
#ifndef XORCIPHER_H
#define XORCIPHER_H

#include "BitwiseCipher.h"
#include "SimpleKeyGenerator.h"
#include <iostream>

class XORCipher : public BitwiseCipher
{
private:
    SimpleKeyGenerator* keyGen;
    bool outputHex;
    bool blockMode;

public:
    XORCipher(unsigned char k = 0xAB) : outputHex(true), blockMode(false)
    {
        byteKey = k;
        name = MyString("XOR Cipher");
        description = MyString("Bitwise XOR of each byte with a fixed key byte");
        keySize = 8;
        isReady = true;
        keyGen = new SimpleKeyGenerator();
    }

    virtual ~XORCipher()
    {
        delete keyGen;
    }

    unsigned char xorByte(unsigned char b, unsigned char key) const
    {
        return b ^ key;
    }

    MyString encrypt(const MyString& text) override
    {
        MyString xord("");
        for (int i = 0; i < text.length(); ++i)
        {
            xord = xord + (char)(xorByte((unsigned char)(text[i]), byteKey));
        }
        return toHex(xord);
    }

    MyString decrypt(const MyString& hexText) override
    {
        MyString raw = fromHex(hexText);
        MyString result("");
        for (int i = 0; i < raw.length(); ++i)
        {
            result = result + (char)(xorByte((unsigned char)(raw[i]), byteKey));
        }
        return result;
    }

    void showInfo() override
    {
        std::cout << "  Cipher  : " << name << std::endl;
        std::cout << "  Desc    : " << description << std::endl;
        std::cout << "  ByteKey : 0x" << std::hex << (int)(byteKey) << std::dec << std::endl;
    }

    MyString getName() const override
    {
        return name;
    }
};

#endif
