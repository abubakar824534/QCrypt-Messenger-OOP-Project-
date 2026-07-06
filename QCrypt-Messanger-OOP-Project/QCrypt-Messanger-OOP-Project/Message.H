#ifndef MESSAGE_H
#define MESSAGE_H

#include "MyString.h"
#include <iostream>

class Message
{
private:
    MyString plainText;
    MyString encryptedText;
    MyString cipherName;
    MyString cipherInfo;

public:
    Message() : plainText(""), encryptedText(""), cipherName(""), cipherInfo("")
    {
    }

    Message(const MyString& plain, const MyString& encrypted, const MyString& cipher) : plainText(plain), encryptedText(encrypted), cipherName(cipher), cipherInfo("")
    {
    }

    Message(const MyString& plain, const MyString& encrypted, const MyString& cipher, const MyString& info) : plainText(plain), encryptedText(encrypted), cipherName(cipher), cipherInfo(info)
    {
    }

    Message(const Message& other) : plainText(other.plainText), encryptedText(other.encryptedText), cipherName(other.cipherName), cipherInfo(other.cipherInfo)
    {
    }

    ~Message()
    {
    }

    Message& operator=(const Message& other)
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

    MyString getPlainText() const
    {
        return plainText;
    }

    MyString getEncryptedText() const
    {
        return encryptedText;
    }

    MyString getCipherName() const
    {
        return cipherName;
    }

    MyString getCipherInfo() const
    {
        return cipherInfo;
    }

    bool hasCipherInfo() const
    {
        return cipherInfo.length() > 0;
    }

    void display() const
    {
        std::cout << "Cipher: " << cipherName << std::endl;
        if (hasCipherInfo())
        {
            std::cout << "Info  : " << cipherInfo << std::endl;
        }
        std::cout << "      > " << encryptedText << std::endl;
        std::cout << "        " << plainText << std::endl;
    }
};

#endif
