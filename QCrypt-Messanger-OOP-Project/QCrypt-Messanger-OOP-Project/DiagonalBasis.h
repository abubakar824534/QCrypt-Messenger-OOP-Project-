#ifndef DIAGONALBASIS_H
#define DIAGONALBASIS_H

#include "Basis.h"

class DiagonalBasis : public Basis
{
private:
    double measureNoise;

public:
    DiagonalBasis();
    virtual ~DiagonalBasis();

    int measure(int photon) const override;
    int prepare(int bit) const override;
    MyString getBasisType() const;
    char getSymbol() const;
};

#endif
