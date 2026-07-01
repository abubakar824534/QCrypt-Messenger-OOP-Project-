#include "Contact.h"
#include <iostream>

using namespace std;

Contact::Contact() :name("Unknown"), phone("000"), chatFile("chat.txt")
{

}

Contact::Contact(const char* n, const char* p, const char* file) :name(n), phone(p), chatFile(file)
{

}

Contact::Contact(const Contact& other) :name(other.name), phone(other.phone), chatFile(other.chatFile)
{

}

Contact::~Contact()
{

}

Contact& Contact::operator=(const Contact& other)
{
    if (this != &other)
    {
        name = other.name;
        phone = other.phone;
        chatFile = other.chatFile;
    }
    return *this;
}

MyString Contact::getName()const
{
    return name;
}

MyString Contact::getPhone()const
{
    return phone;
}

MyString Contact::getChatFile()const
{
    return chatFile;
}

void Contact::display(int index)const
{
    cout << "    [" << index << "] " << name << "\t" << phone << endl;
}
