#ifndef RECTILINEARBASIS_H
#define RECTILINEARBASIS_H

#include "Basis.h"

class RectilinearBasis : public Basis
{
private:
    double measureNoise;

public:
    RectilinearBasis() : measureNoise(0.0)
    {
        basisType = MyString("Rectilinear");
        angle0 = 0;
        angle1 = 90;
        symbol = '+';
    }

    virtual ~RectilinearBasis()
    {
    }

    int measure(int photon) const override
    {
        return photon & 1;
    }

    int prepare(int bit) const override
    {
        return bit & 1;
    }

    MyString getBasisType() const
    {
        return basisType;
    }

    char getSymbol() const
    {
        return symbol;
    }
};

#endif
