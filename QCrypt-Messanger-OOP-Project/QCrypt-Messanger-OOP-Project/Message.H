#ifndef MESSAGE_H
#define MESSAGE_H

#include "MyString.h"

class Message
{
private:
    MyString plainText;
    MyString encryptedText;
    MyString cipherName;
    MyString cipherInfo;

public:
    Message();
    Message(const MyString& plain, const MyString& encrypted, const MyString& cipher);
    Message(const MyString& plain, const MyString& encrypted, const MyString& cipher, const MyString& info);
    Message(const Message& other);
    ~Message();

    Message& operator=(const Message& other);

    MyString getPlainText() const;
    MyString getEncryptedText() const;
    MyString getCipherName() const;
    MyString getCipherInfo() const;
    bool hasCipherInfo() const;
    void display() const;
};

#endif
