#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include "MyString.h"

class KeyGenerator
{
protected:
    MyString keyName;
    int keySize;
    bool isGenerated;
    int keyStrength;

public:
    KeyGenerator();
    virtual ~KeyGenerator();

    virtual void generate() = 0;
    virtual void show() = 0;

    MyString getKeyName() const;
    bool isKeyReady() const;
    int getKeyStrength() const;
};

#endif
