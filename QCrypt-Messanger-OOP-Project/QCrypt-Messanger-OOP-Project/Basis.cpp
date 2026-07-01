#include "Basis.h"

Basis::Basis() :basisType("Unknown"), angle0(0), angle1(90), symbol('?')
{

}

Basis::~Basis()
{

}

MyString Basis::getBasisType()const
{
    return basisType;
}
char Basis::getSymbol()const
{
    return symbol;
}
int Basis::getAngle0()const
{
    return angle0;
}
int Basis::getAngle1()const
{
    return angle1;
}
