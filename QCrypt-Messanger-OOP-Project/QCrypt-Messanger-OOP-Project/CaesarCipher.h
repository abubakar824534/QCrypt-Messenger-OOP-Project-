#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "SubstitutionCipher.h"
#include "SimpleKeyGenerator.h"
#include <iostream>

class CaesarCipher : public SubstitutionCipher
{
private:
    int key;
    bool wrapAround;
    bool caseSensitive;
    SimpleKeyGenerator* keyGen;

public:
    CaesarCipher(int k = 7) : key(k), wrapAround(true), caseSensitive(false)
    {
        name = MyString("Caesar Cipher");
        description = MyString("Shifts each letter by a fixed key value.");
        keySize = 5;
        isReady = true;
        keyGen = new SimpleKeyGenerator();
    }

    virtual ~CaesarCipher()
    {
        delete keyGen;
    }

    MyString encrypt(const MyString& text) override
    {
        MyString upper = text.toUpper();
        MyString result("");
        for (int i = 0; i < upper.length(); ++i)
        {
            char c = upper[i];
            if (c >= 'A' && c <= 'Z')
            {
                result = result + (char)('A' + (c - 'A' + key) % 26);
            }
            else
            {
                result = result + c;
            }
        }
        return result;
    }

    MyString decrypt(const MyString& text) override
    {
        MyString upper = text.toUpper();
        MyString result("");
        for (int i = 0; i < upper.length(); ++i)
        {
            char c = upper[i];
            if (c >= 'A' && c <= 'Z')
            {
                result = result + (char)('A' + (c - 'A' - key % 26 + 26) % 26);
            }
            else
            {
                result = result + c;
            }
        }
        return result;
    }

    void showInfo() override
    {
        std::cout << "  Cipher : " << name << std::endl;
        std::cout << "  Desc   : " << description << std::endl;
        std::cout << "  Key    : " << key << std::endl;
    }

    MyString getName() const override
    {
        return name;
    }

    void setKey(int k)
    {
        key = k;
    }
};

#endif
