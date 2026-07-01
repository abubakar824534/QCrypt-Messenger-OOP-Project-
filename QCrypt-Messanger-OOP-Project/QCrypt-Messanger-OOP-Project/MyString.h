#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString
{
private:
    char* data;
    int len;

    void copyFrom(const char* src);

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString& operator=(const char* str);
    MyString operator+(const MyString& other) const;
    MyString operator+(const char* other) const;
    MyString operator+(char c) const;
    char& operator[](int index);
    char operator[](int index) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;

    int length() const;
    const char* c_str() const;

    static MyString fromInt(int val);

    MyString toUpper() const;
    MyString toLower() const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
};

#endif
