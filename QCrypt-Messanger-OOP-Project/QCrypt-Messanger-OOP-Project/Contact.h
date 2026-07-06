#ifndef CONTACT_H
#define CONTACT_H

#include "MyString.h"
#include <iostream>

class Contact
{
private:
    MyString name;
    MyString phone;
    MyString chatFile;

public:
    Contact() : name("Unknown"), phone("000"), chatFile("chat.txt")
    {
    }

    Contact(const char* n, const char* p, const char* file) : name(n), phone(p), chatFile(file)
    {
    }

    Contact(const Contact& other) : name(other.name), phone(other.phone), chatFile(other.chatFile)
    {
    }

    ~Contact()
    {
    }

    Contact& operator=(const Contact& other)
    {
        if (this != &other)
        {
            name = other.name;
            phone = other.phone;
            chatFile = other.chatFile;
        }
        return *this;
    }

    MyString getName() const
    {
        return name;
    }

    MyString getPhone() const
    {
        return phone;
    }

    MyString getChatFile() const
    {
        return chatFile;
    }

    void display(int index) const
    {
        std::cout << "    [" << index << "] " << name << "\t" << phone << std::endl;
    }
};

#endif
