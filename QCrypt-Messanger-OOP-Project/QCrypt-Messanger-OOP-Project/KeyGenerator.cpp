#include "KeyGenerator.h"

KeyGenerator::KeyGenerator() :keyName("Unnamed"), keySize(0), isGenerated(false), keyStrength(0)
{

}

KeyGenerator::~KeyGenerator()
{

}

MyString KeyGenerator::getKeyName()const
{
    return keyName;
}
bool KeyGenerator::isKeyReady()const
{
    return isGenerated;
}
int KeyGenerator::getKeyStrength()const
{
    return keyStrength;
}
