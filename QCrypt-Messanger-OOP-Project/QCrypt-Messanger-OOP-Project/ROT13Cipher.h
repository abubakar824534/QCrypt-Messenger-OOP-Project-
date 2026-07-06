#ifndef ROT13CIPHER_H
#define ROT13CIPHER_H

#include "SubstitutionCipher.h"
#include "MyString.h"
#include <iostream>

class ROT13Cipher : public SubstitutionCipher
{
private:
    int fixedShift;
    bool isSelfInverse;
    bool alphaOnly;
    MyString lastResult;

public:
    ROT13Cipher() : fixedShift(13), isSelfInverse(true), alphaOnly(true)
    {
        name = MyString("ROT13 Cipher");
        description = MyString("Substitutes each letter with the one 13 positions later. Self inverse.");
        keySize = 0;
        isReady = true;
    }

    virtual ~ROT13Cipher()
    {
    }

    MyString applyROT13(const MyString& text)
    {
        MyString upper = text.toUpper();
        MyString result("");
        for (int i = 0; i < upper.length(); ++i)
        {
            char c = upper[i];
            if (c >= 'A' && c <= 'Z')
            {
                result = result + (char)('A' + (c - 'A' + 13) % 26);
            }
            else
            {
                result = result + c;
            }
        }
        lastResult = result;
        return result;
    }

    MyString encrypt(const MyString& text) override
    {
        return applyROT13(text);
    }

    MyString decrypt(const MyString& text) override
    {
        return applyROT13(text);
    }

    void showInfo() override
    {
        std::cout << "  Cipher : " << name << std::endl;
        std::cout << "  Desc   : " << description << std::endl;
        std::cout << "  Shift  : " << fixedShift << " (self inverse)" << std::endl;
    }

    MyString getName() const override
    {
        return name;
    }
};

#endif
