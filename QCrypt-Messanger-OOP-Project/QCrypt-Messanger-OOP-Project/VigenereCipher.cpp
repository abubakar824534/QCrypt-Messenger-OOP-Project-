#include "VigenereCipher.h"
#include <iostream>

using namespace std;

VigenereCipher::VigenereCipher(const char* kw) :autoKey(false)
{
    name = MyString("Vigenere Cipher");
    description = MyString("Polyalphabetic substitution using a keyword and tabula recta");
    keySize = 3;
    isReady = true;
    keyGen = new SimpleKeyGenerator();
    keyword = MyString(kw);
    keyLength = keyword.length();
    buildTabulaRecta();
}

VigenereCipher::~VigenereCipher()
{
    delete keyGen;
}

void VigenereCipher::buildTabulaRecta()
{
    for (int r = 0; r < 26; ++r)
    {
        for (int c = 0; c < 26; ++c)
        {
            tabula[r][c] = (char)('A' + (r + c) % 26);
        }
    }
}

void VigenereCipher::setKeyword(const MyString& kw)
{
    PolyalphabeticCipher::setKeyword(kw);
}

MyString VigenereCipher::encrypt(const MyString& text)
{
    MyString upper = text.toUpper();
    MyString result("");
    int ki = 0;
    for (int i = 0; i < upper.length(); ++i)
    {
        char c = upper[i];
        if (c >= 'A' && c <= 'Z')
        {
            char k = getKeyChar(ki++);
            result = result + tabula[k - 'A'][c - 'A'];
        }
        else
        {
            result = result + c;
        }
    }
    return result;
}

MyString VigenereCipher::decrypt(const MyString& text)
{
    MyString upper = text.toUpper();
    MyString result("");
    int ki = 0;
    for (int i = 0; i < upper.length(); ++i)
    {
        char c = upper[i];
        if (c >= 'A' && c <= 'Z')
        {
            char k = getKeyChar(ki++);
            int row = k - 'A';
            for (int col = 0; col < 26; ++col)
            {
                if (tabula[row][col] == c)
                {
                    result = result + (char)('A' + col);
                    break;
                }
            }
        }
        else
        {
            result = result + c;
        }
    }
    return result;
}

void VigenereCipher::showInfo()
{
    cout << "  Cipher  : " << name << endl;
    cout << "  Desc    : " << description << endl;
    cout << "  Keyword : " << keyword << endl;
}

MyString VigenereCipher::getName()const
{
    return name;
}
