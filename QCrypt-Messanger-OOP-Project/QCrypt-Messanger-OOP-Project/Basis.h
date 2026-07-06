#ifndef BASIS_H
#define BASIS_H

#include "MyString.h"

class Basis
{
protected:
    MyString basisType;
    int angle0;
    int angle1;
    char symbol;

public:
    Basis() : basisType("Unknown"), angle0(0), angle1(90), symbol('?')
    {
    }

    virtual ~Basis()
    {
    }

    virtual int measure(int photon) const = 0;
    virtual int prepare(int bit) const = 0;

    MyString getBasisType() const
    {
        return basisType;
    }

    char getSymbol() const
    {
        return symbol;
    }

    int getAngle0() const
    {
        return angle0;
    }

    int getAngle1() const
    {
        return angle1;
    }
};

#endif
