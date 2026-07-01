#include "SubstitutionCipher.h"

SubstitutionCipher::SubstitutionCipher() :shift(0), alphabetSize(26), preserveCase(true), skipNonAlpha(true)
{

}

SubstitutionCipher::~SubstitutionCipher()
{

}

bool SubstitutionCipher::isAlpha(char c)const
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int SubstitutionCipher::normalizeShift(int s)const
{
    int n = s % 26;
    if (n < 0)
    {
        n += 26;
    }
    return n;
}

int SubstitutionCipher::getAlphabetSize()const
{
    return alphabetSize;
}

char SubstitutionCipher::shiftChar(char c, int s)const
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
