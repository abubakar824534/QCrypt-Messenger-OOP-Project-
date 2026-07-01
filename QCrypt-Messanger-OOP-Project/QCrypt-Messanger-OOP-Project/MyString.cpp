#include "MyString.h"

using namespace std;

void MyString::copyFrom(const char* src)
{
    if (!src)
    {
        len = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }
    len = 0;
    while (src[len] != '\0') ++len;
    data = new char[len + 1];
    for (int i = 0; i <= len; ++i)
    {
        data[i] = src[i];
    }
}

MyString::MyString()
{
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* str)
{
    copyFrom(str);
}

MyString::MyString(const MyString& other)
{
    copyFrom(other.data);
}

MyString::~MyString()
{
    delete[] data;
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        delete[] data;
        copyFrom(other.data);
    }
    return *this;
}

MyString& MyString::operator=(const char* str)
{
    delete[] data;
    copyFrom(str);
    return *this;
}

MyString MyString::operator+(const MyString& other)const
{
    int newLen = len + other.len;
    char* buf = new char[newLen + 1];
    for (int i = 0; i < len; ++i)
    {
        buf[i] = data[i];
    }
    for (int i = 0; i < other.len; ++i)
    {
        buf[len + i] = other.data[i];
    }
    buf[newLen] = '\0';
    MyString result(buf);
    delete[] buf;
    return result;
}

MyString MyString::operator+(const char* other)const
{
    MyString tmp(other);
    return (*this) + tmp;
}

MyString MyString::operator+(char c)const
{
    int newLen = len + 1;
    char* buf = new char[newLen + 1];
    for (int i = 0; i < len; ++i)
    {
        buf[i] = data[i];
    }
    buf[len] = c;
    buf[newLen] = '\0';
    MyString result(buf);
    delete[] buf;
    return result;
}

char& MyString::operator[](int index)
{
    return data[index];
}

char MyString::operator[](int index)const
{
    return data[index];
}

bool MyString::operator==(const MyString& other)const
{
    if (len != other.len)
    {
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        if (data[i] != other.data[i])
        {
            return false;
        }
    }
    return true;
}

bool MyString::operator!=(const MyString& other)const
{
    return !(*this == other);
}

int MyString::length()const
{
    return len;
}

const char* MyString::c_str()const
{
    return data;
}

MyString MyString::fromInt(int val)
{
    if (val == 0)
    {
        return MyString("0");
    }
    bool neg = val < 0;
    if (neg)
    {
        val = -val;
    }
    char buf[32];
    int pos = 0;
    while (val > 0)
    {
        buf[pos++] = '0' + (val % 10);
        val /= 10;
    }
    if (neg)
    {
        buf[pos++] = '-';
    }
    for (int i = 0; i < pos / 2; ++i)
    {
        char t = buf[i];
        buf[i] = buf[pos - 1 - i];
        buf[pos - 1 - i] = t;
    }
    buf[pos] = '\0';
    return MyString(buf);
}

MyString MyString::toUpper()const
{
    MyString result(*this);
    for (int i = 0; i < result.len; ++i)
    {
        if (result.data[i] >= 'a' && result.data[i] <= 'z')
        {
            result.data[i] = result.data[i] - 'a' + 'A';
        }
    }
    return result;
}

MyString MyString::toLower()const
{
    MyString result(*this);
    for (int i = 0; i < result.len; ++i)
    {
        if (result.data[i] >= 'A' && result.data[i] <= 'Z')
        {
            result.data[i] = result.data[i] - 'A' + 'a';
        }
    }
    return result;
}

ostream& operator<<(ostream& os, const MyString& s)
{
    os << s.data;
    return os;
}
