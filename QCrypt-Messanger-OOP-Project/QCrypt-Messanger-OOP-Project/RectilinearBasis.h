#ifndef RECTILINEARBASIS_H
#define RECTILINEARBASIS_H

#include "Basis.h"

class RectilinearBasis : public Basis
{
private:
    double measureNoise;

public:
    RectilinearBasis();
    virtual ~RectilinearBasis();

    int measure(int photon) const override;
    int prepare(int bit) const override;
    MyString getBasisType() const;
    char getSymbol() const;
};

#endif
