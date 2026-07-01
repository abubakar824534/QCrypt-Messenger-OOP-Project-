#ifndef SIMPLEKEYGENERATOR_H
#define SIMPLEKEYGENERATOR_H

#include "KeyGenerator.h"
#include "MyString.h"

class SimpleKeyGenerator : public KeyGenerator
{
private:
    int shiftValue;
    MyString keyword;
    unsigned char byteKey;
    MyString keyType;

public:
    SimpleKeyGenerator();
    virtual ~SimpleKeyGenerator();

    void generate() override;
    void show() override;

    int getShift() const;
    MyString getKeyword() const;
    unsigned char getByteKey() const;
};

#endif
