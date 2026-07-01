#include "PolyalphabeticCipher.h"

PolyalphabeticCipher::PolyalphabeticCipher() : keyword("KEY"), keyIndex(0), keyLength(3), repeatKey(true)
{

}

PolyalphabeticCipher::~PolyalphabeticCipher()
{

}

void PolyalphabeticCipher::setKeyword(const MyString& kw)
{
    keyword = kw.toUpper();
    keyLength = kw.length();
    keyIndex = 0;
}

char PolyalphabeticCipher::getKeyChar(int pos) const
{
    if (keyLength == 0)
    {
        return 'A';
    }
    return keyword[pos % keyLength];
}

MyString PolyalphabeticCipher::extendKey(int len) const
{
    MyString ext("");
    for (int i = 0; i < len; ++i)
    {
        ext = ext + getKeyChar(i);
    }
    return ext;
}

bool PolyalphabeticCipher::validateKeyword() const
{
    return keyLength > 0;
}
