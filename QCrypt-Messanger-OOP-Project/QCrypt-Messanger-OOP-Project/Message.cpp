#include "Message.h"
#include <iostream>

using namespace std;

Message::Message() :plainText(""), encryptedText(""), cipherName(""), cipherInfo("")
{

}

Message::Message(const MyString& plain, const MyString& encrypted, const MyString& cipher) :plainText(plain), encryptedText(encrypted), cipherName(cipher), cipherInfo("")
{

}

Message::Message(const MyString& plain, const MyString& encrypted, const MyString& cipher, const MyString& info) :plainText(plain), encryptedText(encrypted), cipherName(cipher), cipherInfo(info)
{

}

Message::Message(const Message& other) :plainText(other.plainText), encryptedText(other.encryptedText), cipherName(other.cipherName), cipherInfo(other.cipherInfo)
{

}

Message::~Message()
{

}

Message& Message::operator=(const Message& other)
{
    if (this != &other)
    {
        plainText = other.plainText;
        encryptedText = other.encryptedText;
        cipherName = other.cipherName;
        cipherInfo = other.cipherInfo;
    }
    return *this;
}

MyString Message::getPlainText()const
{
    return plainText;
}

MyString Message::getEncryptedText()const
{
    return encryptedText;
}

MyString Message::getCipherName()const
{
    return cipherName;
}

MyString Message::getCipherInfo()const
{
    return cipherInfo;
}

bool Message::hasCipherInfo()const
{
    return cipherInfo.length() > 0;
}

void Message::display()const
{
    cout << "Cipher: " << cipherName << endl;
    if (hasCipherInfo())
    {
        cout << "Info  : " << cipherInfo << endl;
    }
    cout << "      > " << encryptedText << endl;
    cout << "        " << plainText << endl;
}
