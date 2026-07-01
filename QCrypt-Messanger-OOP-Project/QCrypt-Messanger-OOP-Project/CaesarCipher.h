#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "SubstitutionCipher.h"
#include "SimpleKeyGenerator.h"

class CaesarCipher : public SubstitutionCipher
{
private:
    int key;
    bool wrapAround;
    bool caseSensitive;
    SimpleKeyGenerator* keyGen;

public:
    CaesarCipher(int k = 7);
    virtual ~CaesarCipher();

    MyString encrypt(const MyString& text) override;
    MyString decrypt(const MyString& text) override;
    void showInfo() override;
    MyString getName() const override;

    void setKey(int k);
};

#endif
