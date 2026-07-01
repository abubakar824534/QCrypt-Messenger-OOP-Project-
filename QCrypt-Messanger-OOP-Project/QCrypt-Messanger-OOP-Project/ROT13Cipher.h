#ifndef ROT13CIPHER_H
#define ROT13CIPHER_H

#include "SubstitutionCipher.h"
#include "MyString.h"

class ROT13Cipher : public SubstitutionCipher
{
private:
    int fixedShift;
    bool isSelfInverse;
    bool alphaOnly;
    MyString lastResult;

public:
    ROT13Cipher();
    virtual ~ROT13Cipher();

    MyString encrypt(const MyString& text) override;
    MyString decrypt(const MyString& text) override;
    void showInfo() override;
    MyString getName() const override;

    MyString applyROT13(const MyString& text);
};

#endif
