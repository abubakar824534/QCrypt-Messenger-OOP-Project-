#include "Party.h"

Party::Party() :partyName("Unknown"), role("none")
{

}

Party::~Party()
{

}

MyString Party::getName()const
{
    return partyName;
}
MyVector<int> Party::getBits()const
{
    return bits;
}
MyVector<int> Party::getBases()const
{
    return bases;
}
