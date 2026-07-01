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
    Party();
    virtual ~Party();

    virtual void prepare(int n) = 0;
    virtual int measure(int photon, int b) = 0;

    MyString getName() const;
    MyVector<int> getBits() const;
    MyVector<int> getBases() const;
};

#endif
