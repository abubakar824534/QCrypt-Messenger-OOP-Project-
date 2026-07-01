#ifndef CIPHER_H
#define CIPHER_H

#include "MyString.h"

class Cipher
{
protected:
    MyString name;
    MyString description;
    int keySize;
    bool isReady;

public:
    Cipher();
    virtual ~Cipher();

    virtual MyString encrypt(const MyString& text) = 0;
    virtual MyString decrypt(const MyString& text) = 0;
    virtual void showInfo() = 0;
    virtual MyString getName() const = 0;
};

#endif
