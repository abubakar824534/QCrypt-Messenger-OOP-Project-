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
    Basis();
    virtual ~Basis();

    virtual int measure(int photon) const = 0;
    virtual int prepare(int bit) const = 0;

    MyString getBasisType() const;
    char getSymbol() const;
    int getAngle0() const;
    int getAngle1() const;
};

#endif
