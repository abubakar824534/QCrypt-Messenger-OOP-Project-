#ifndef CONTACT_H
#define CONTACT_H

#include "MyString.h"

class Contact
{
private:
    MyString name;
    MyString phone;
    MyString chatFile;

public:
    Contact();
    Contact(const char* n, const char* p, const char* file);
    Contact(const Contact& other);
    ~Contact();

    Contact& operator=(const Contact& other);

    MyString getName() const;
    MyString getPhone() const;
    MyString getChatFile() const;
    void display(int index) const;
};

#endif
