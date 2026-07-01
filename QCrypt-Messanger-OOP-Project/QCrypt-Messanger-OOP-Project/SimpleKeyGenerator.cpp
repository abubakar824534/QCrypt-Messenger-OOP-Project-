#include "SimpleKeyGenerator.h"
#include <iostream>

using namespace std;

SimpleKeyGenerator::SimpleKeyGenerator() :shiftValue(7), keyword("KEY"), byteKey(0xAB), keyType("SHIFT")
{
    keyName = MyString("SimpleKey");
    keySize = 8;
    keyStrength = 8;
    isGenerated = true;
}

SimpleKeyGenerator::~SimpleKeyGenerator()
{

}

void SimpleKeyGenerator::generate()
{
    shiftValue = 7;
    keyword = MyString("KEY");
    byteKey = 0xAB;
    isGenerated = true;
}

void SimpleKeyGenerator::show()
{
    cout << "  Simple Key -> Shift: " << shiftValue << "  Keyword: " << keyword << "  ByteKey: 0x" << hex << (int)(byteKey) << dec << endl;
}

int SimpleKeyGenerator::getShift()const
{
    return shiftValue;
}
MyString SimpleKeyGenerator::getKeyword()const
{
    return keyword;
}
unsigned char SimpleKeyGenerator::getByteKey()const
{
    return byteKey;
}
