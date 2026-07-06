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
    KeyGenerator() : keyName("Unnamed"), keySize(0), isGenerated(false), keyStrength(0)
    {
    }

    virtual ~KeyGenerator()
    {
    }

    virtual void generate() = 0;
    virtual void show() = 0;

    MyString getKeyName() const
    {
        return keyName;
    }

    bool isKeyReady() const
    {
        return isGenerated;
    }

    int getKeyStrength() const
    {
        return keyStrength;
    }
};

#endif
