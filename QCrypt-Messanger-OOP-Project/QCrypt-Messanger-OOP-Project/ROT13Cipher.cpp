#include "ROT13Cipher.h"
#include <iostream>

using namespace std;

ROT13Cipher::ROT13Cipher() :fixedShift(13), isSelfInverse(true), alphaOnly(true)
{
    name = MyString("ROT13 Cipher");
    description = MyString("Substitutes each letter with the one 13 positions later. Self inverse.");
    keySize = 0;
    isReady = true;
}

ROT13Cipher::~ROT13Cipher()
{

}

MyString ROT13Cipher::applyROT13(const MyString& text)
{
    MyString upper = text.toUpper();
    MyString result("");
    for (int i = 0; i < upper.length(); ++i)
    {
        char c = upper[i];
        if (c >= 'A' && c <= 'Z')
        {
            result = result + (char)('A' + (c - 'A' + 13) % 26);
        }
        else
        {
            result = result + c;
        }
    }
    lastResult = result;
    return result;
}

MyString ROT13Cipher::encrypt(const MyString& text)
{
    return applyROT13(text);
}

MyString ROT13Cipher::decrypt(const MyString& text)
{
    return applyROT13(text);
}

void ROT13Cipher::showInfo()
{
    cout << "  Cipher : " << name << endl;
    cout << "  Desc   : " << description << endl;
    cout << "  Shift  : " << fixedShift << " (self inverse)" << endl;
}

MyString ROT13Cipher::getName()const
{
    return name;
}
