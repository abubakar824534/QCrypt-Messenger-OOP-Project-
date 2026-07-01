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
    SubstitutionCipher();
    virtual ~SubstitutionCipher();

    char shiftChar(char c, int s) const;
    bool isAlpha(char c) const;
    int normalizeShift(int s) const;
    int getAlphabetSize() const;
};

#endif
