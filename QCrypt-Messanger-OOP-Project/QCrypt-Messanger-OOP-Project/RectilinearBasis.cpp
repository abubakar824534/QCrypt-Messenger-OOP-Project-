#include "RectilinearBasis.h"

RectilinearBasis::RectilinearBasis() :measureNoise(0.0)
{
    basisType = MyString("Rectilinear");
    angle0 = 0;
    angle1 = 90;
    symbol = '+';
}

RectilinearBasis::~RectilinearBasis()
{

}

int RectilinearBasis::measure(int photon)const
{
    return photon & 1;
}

int RectilinearBasis::prepare(int bit)const
{
    return bit & 1;
}

MyString RectilinearBasis::getBasisType()const
{
    return basisType;
}
char RectilinearBasis::getSymbol()const
{
    return symbol;
}
