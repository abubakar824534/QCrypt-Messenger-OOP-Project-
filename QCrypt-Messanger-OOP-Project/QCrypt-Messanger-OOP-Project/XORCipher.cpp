#include "XORCipher.h"
#include <iostream>

using namespace std;

XORCipher::XORCipher(unsigned char k) :outputHex(true), blockMode(false)
{
    byteKey = k;
    name = MyString("XOR Cipher");
    description = MyString("Bitwise XOR of each byte with a fixed key byte");
    keySize = 8;
    isReady = true;
    keyGen = new SimpleKeyGenerator();
}

XORCipher::~XORCipher()
{
    delete keyGen;
}

unsigned char XORCipher::xorByte(unsigned char b, unsigned char key)const
{
    return b ^ key;
}

MyString XORCipher::encrypt(const MyString& text)
{
    MyString xord("");
    for (int i = 0; i < text.length(); ++i)
    {
        xord = xord + (char)(xorByte((unsigned char)(text[i]), byteKey));
    }
    return toHex(xord);
}

MyString XORCipher::decrypt(const MyString& hexText)
{
    MyString raw = fromHex(hexText);
    MyString result("");
    for (int i = 0; i < raw.length(); ++i)
    {
        result = result + (char)(xorByte((unsigned char)(raw[i]), byteKey));
    }
    return result;
}

void XORCipher::showInfo()
{
    cout << "  Cipher  : " << name << endl;
    cout << "  Desc    : " << description << endl;
    cout << "  ByteKey : 0x" << hex << (int)(byteKey) << dec << endl;
}

MyString XORCipher::getName()const
{
    return name;
}
