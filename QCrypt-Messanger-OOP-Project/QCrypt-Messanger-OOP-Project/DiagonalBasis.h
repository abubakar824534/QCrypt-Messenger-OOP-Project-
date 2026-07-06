#ifndef DIAGONALBASIS_H
#define DIAGONALBASIS_H

#include "Basis.h"

class DiagonalBasis : public Basis
{
private:
    double measureNoise;

public:
    DiagonalBasis() : measureNoise(0.0)
    {
        basisType = MyString("Diagonal");
        angle0 = 45;
        angle1 = 135;
        symbol = 'x';
    }

    virtual ~DiagonalBasis()
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
