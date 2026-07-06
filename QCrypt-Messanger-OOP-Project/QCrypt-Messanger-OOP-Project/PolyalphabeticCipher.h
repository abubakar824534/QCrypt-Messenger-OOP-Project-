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
    PolyalphabeticCipher() : keyword("KEY"), keyIndex(0), keyLength(3), repeatKey(true)
    {
    }

    virtual ~PolyalphabeticCipher()
    {
    }

    void setKeyword(const MyString& kw)
    {
        keyword = kw.toUpper();
        keyLength = kw.length();
        keyIndex = 0;
    }

    char getKeyChar(int pos) const
    {
        if (keyLength == 0)
        {
            return 'A';
        }
        return keyword[pos % keyLength];
    }

    MyString extendKey(int len) const
    {
        MyString ext("");
        for (int i = 0; i < len; ++i)
        {
            ext = ext + getKeyChar(i);
        }
        return ext;
    }

    bool validateKeyword() const
    {
        return keyLength > 0;
    }
};

#endif
