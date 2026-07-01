#include "DiagonalBasis.h"

DiagonalBasis::DiagonalBasis() :measureNoise(0.0)
{
    basisType = MyString("Diagonal");
    angle0 = 45;
    angle1 = 135;
    symbol = 'x';
}

DiagonalBasis::~DiagonalBasis()
{

}

int DiagonalBasis::measure(int photon)const
{
    return photon & 1;
}

int DiagonalBasis::prepare(int bit)const
{
    return bit & 1;
}

MyString DiagonalBasis::getBasisType()const
{
    return basisType;
}
char DiagonalBasis::getSymbol()const
{
    return symbol;
}
