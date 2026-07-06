#pragma once
#ifndef VIGENERECHIPHER_H
#define VIGENERECHIPHER_H

#include "PolyalphabeticCipher.h"
#include "SimpleKeyGenerator.h"
#include <iostream>

class VigenereCipher : public PolyalphabeticCipher
{
private:
    char tabula[26][26];
    SimpleKeyGenerator* keyGen;
    bool autoKey;

public:
    VigenereCipher(const char* kw = "KEY") : autoKey(false)
    {
        name = MyString("Vigenere Cipher");
        description = MyString("Polyalphabetic substitution using a keyword and tabula recta");
        keySize = 3;
        isReady = true;
        keyGen = new SimpleKeyGenerator();
        keyword = MyString(kw);
        keyLength = keyword.length();
        buildTabulaRecta();
    }

    virtual ~VigenereCipher()
    {
        delete keyGen;
    }

    void buildTabulaRecta()
    {
        for (int r = 0; r < 26; ++r)
        {
            for (int c = 0; c < 26; ++c)
            {
                tabula[r][c] = (char)('A' + (r + c) % 26);
            }
        }
    }

    void setKeyword(const MyString& kw)
    {
        PolyalphabeticCipher::setKeyword(kw);
    }

    MyString encrypt(const MyString& text) override
    {
        MyString upper = text.toUpper();
        MyString result("");
        int ki = 0;
        for (int i = 0; i < upper.length(); ++i)
        {
            char c = upper[i];
            if (c >= 'A' && c <= 'Z')
            {
                char k = getKeyChar(ki++);
                result = result + tabula[k - 'A'][c - 'A'];
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
        int ki = 0;
        for (int i = 0; i < upper.length(); ++i)
        {
            char c = upper[i];
            if (c >= 'A' && c <= 'Z')
            {
                char k = getKeyChar(ki++);
                int row = k - 'A';
                for (int col = 0; col < 26; ++col)
                {
                    if (tabula[row][col] == c)
                    {
                        result = result + (char)('A' + col);
                        break;
                    }
                }
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
        std::cout << "  Cipher  : " << name << std::endl;
        std::cout << "  Desc    : " << description << std::endl;
        std::cout << "  Keyword : " << keyword << std::endl;
    }

    MyString getName() const override
    {
        return name;
    }
};

#endif
