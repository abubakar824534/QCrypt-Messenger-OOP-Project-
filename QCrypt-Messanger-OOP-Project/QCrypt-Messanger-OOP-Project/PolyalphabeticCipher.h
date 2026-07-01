#ifndef POLYALPHABETICCIPER_H
#define POLYALPHABETICCIPER_H

#include "Cipher.h"

class PolyalphabeticCipher : public Cipher
{
protected:
    MyString keyword;
    int keyIndex;
    int keyLength;
    bool repeatKey;

public:
    PolyalphabeticCipher();
    virtual ~PolyalphabeticCipher();

    void setKeyword(const MyString& kw);
    char getKeyChar(int pos) const;
    MyString extendKey(int len) const;
    bool validateKeyword() const;
};

#endif
