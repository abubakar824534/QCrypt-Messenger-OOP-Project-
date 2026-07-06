#ifndef SUBSTITUTIONCIPER_H
#define SUBSTITUTIONCIPER_H

#include "Cipher.h"

class SubstitutionCipher : public Cipher
{
protected:
    int shift;
    int alphabetSize;
    bool preserveCase;
    bool skipNonAlpha;

public:
    SubstitutionCipher() : shift(0), alphabetSize(26), preserveCase(true), skipNonAlpha(true)
    {
    }

    virtual ~SubstitutionCipher()
    {
    }

    char shiftChar(char c, int s) const
    {
        s = normalizeShift(s);
        if (c >= 'A' && c <= 'Z')
        {
            return (char)('A' + (c - 'A' + s) % 26);
        }
        if (c >= 'a' && c <= 'z')
        {
            return (char)('a' + (c - 'a' + s) % 26);
        }
        return c;
    }

    bool isAlpha(char c) const
    {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }

    int normalizeShift(int s) const
    {
        int n = s % 26;
        if (n < 0)
        {
            n += 26;
        }
        return n;
    }

    int getAlphabetSize() const
    {
        return alphabetSize;
    }
};

#endif
