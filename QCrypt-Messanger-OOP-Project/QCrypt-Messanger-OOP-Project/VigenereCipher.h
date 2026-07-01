#pragma once
#ifndef VIGENERECHIPHER_H
#define VIGENERECHIPHER_H

#include "PolyalphabeticCipher.h"
#include "SimpleKeyGenerator.h"

class VigenereCipher : public PolyalphabeticCipher
{
private:
    char tabula[26][26];
    SimpleKeyGenerator* keyGen;
    bool autoKey;

public:
    VigenereCipher(const char* kw = "KEY");
    virtual ~VigenereCipher();

    MyString encrypt(const MyString& text) override;
    MyString decrypt(const MyString& text) override;
    void showInfo() override;
    MyString getName() const override;

    void buildTabulaRecta();
    void setKeyword(const MyString& kw);
};

#endif
