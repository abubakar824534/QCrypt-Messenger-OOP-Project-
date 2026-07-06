#ifndef PARTY_H
#define PARTY_H

#include "MyString.h"
#include "MyVector.h"

class Party
{
protected:
    MyString partyName;
    MyVector<int> bits;
    MyVector<int> bases;
    MyString role;

public:
    Party() : partyName("Unknown"), role("none")
    {
    }

    virtual ~Party()
    {
    }

    virtual void prepare(int n) = 0;
    virtual int measure(int photon, int b) = 0;

    MyString getName() const
    {
        return partyName;
    }

    MyVector<int> getBits() const
    {
        return bits;
    }

    MyVector<int> getBases() const
    {
        return bases;
    }
};

#endif
