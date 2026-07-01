#include "CaesarCipher.h"
#include <iostream>

using namespace std;

CaesarCipher::CaesarCipher(int k) :key(k), wrapAround(true), caseSensitive(false)
{
    name = MyString("Caesar Cipher");
    description = MyString("Shifts each letter by a fixed key value.");
    keySize = 5;
    isReady = true;
    keyGen = new SimpleKeyGenerator();
}

CaesarCipher::~CaesarCipher()
{
    delete keyGen;
}

MyString CaesarCipher::encrypt(const MyString& text)
{
    MyString upper = text.toUpper();
    MyString result("");
    for (int i = 0; i < upper.length(); ++i)
    {
        char c = upper[i];
        if (c >= 'A' && c <= 'Z')
        {
            result = result + (char)('A' + (c - 'A' + key) % 26);
        }
        else
        {
            result = result + c;
        }
    }
    return result;
}

MyString CaesarCipher::decrypt(const MyString& text)
{
    MyString upper = text.toUpper();
    MyString result("");
    for (int i = 0; i < upper.length(); ++i)
    {
        char c = upper[i];
        if (c >= 'A' && c <= 'Z')
        {
            result = result + (char)('A' + (c - 'A' - key % 26 + 26) % 26);
        }
        else
        {
            result = result + c;
        }
    }
    return result;
}

void CaesarCipher::showInfo()
{
    cout << "  Cipher : " << name << endl;
    cout << "  Desc   : " << description << endl;
    cout << "  Key    : " << key << endl;
}

MyString CaesarCipher::getName()const
{
    return name;
}

void CaesarCipher::setKey(int k)
{
    key = k;
}
