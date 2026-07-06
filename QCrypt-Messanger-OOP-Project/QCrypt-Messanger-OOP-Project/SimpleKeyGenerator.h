#ifndef SIMPLEKEYGENERATOR_H
#define SIMPLEKEYGENERATOR_H

#include "KeyGenerator.h"
#include "MyString.h"
#include <iostream>

class SimpleKeyGenerator : public KeyGenerator
{
private:
    int shiftValue;
    MyString keyword;
    unsigned char byteKey;
    MyString keyType;

public:
    SimpleKeyGenerator() : shiftValue(7), keyword("KEY"), byteKey(0xAB), keyType("SHIFT")
    {
        keyName = MyString("SimpleKey");
        keySize = 8;
        keyStrength = 8;
        isGenerated = true;
    }

    virtual ~SimpleKeyGenerator()
    {
    }

    void generate() override
    {
        shiftValue = 7;
        keyword = MyString("KEY");
        byteKey = 0xAB;
        isGenerated = true;
    }

    void show() override
    {
        std::cout << "  Simple Key -> Shift: " << shiftValue << "  Keyword: " << keyword << "  ByteKey: 0x" << std::hex << (int)(byteKey) << std::dec << std::endl;
    }

    int getShift() const
    {
        return shiftValue;
    }

    MyString getKeyword() const
    {
        return keyword;
    }

    unsigned char getByteKey() const
    {
        return byteKey;
    }
};

#endif
