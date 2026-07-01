#ifndef BITWISECIPHER_H
#define BITWISECIPHER_H

#include "Cipher.h"

class BitwiseCipher : public Cipher
{
protected:
    unsigned char byteKey;
    int blockSize;
    MyString operation;
    bool padded;

public:
    BitwiseCipher();
    virtual ~BitwiseCipher();

    unsigned char applyBitOp(unsigned char byte, unsigned char key) const;
    MyString toHex(const MyString& data) const;
    MyString fromHex(const MyString& hex) const;
    unsigned char getByteKey() const;
};

#endif
