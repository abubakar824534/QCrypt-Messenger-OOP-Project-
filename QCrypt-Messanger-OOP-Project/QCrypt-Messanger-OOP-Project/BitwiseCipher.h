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
    BitwiseCipher() : byteKey(0xAB), blockSize(8), operation("XOR"), padded(false)
    {
    }

    virtual ~BitwiseCipher()
    {
    }

    unsigned char applyBitOp(unsigned char byte, unsigned char key) const
    {
        return byte ^ key;
    }

    MyString toHex(const MyString& data) const
    {
        const char hexChars[] = "0123456789ABCDEF";
        MyString result("");
        for (int i = 0; i < data.length(); ++i)
        {
            unsigned char b = (unsigned char)(data[i]);
            if (i > 0)
            {
                result = result + ' ';
            }
            result = result + hexChars[(b >> 4) & 0x0F];
            result = result + hexChars[b & 0x0F];
        }
        return result;
    }

    MyString fromHex(const MyString& hex) const
    {
        MyString result("");
        int i = 0;
        while (i < hex.length())
        {
            while (i < hex.length() && hex[i] == ' ')
            {
                ++i;
            }
            if (i + 1 >= hex.length())
            {
                break;
            }
            char h = hex[i];
            char l = hex[i + 1];
            i += 2;
            int hv = 0;
            if (h >= '0' && h <= '9')
            {
                hv = h - '0';
            }
            else if (h >= 'A' && h <= 'F')
            {
                hv = h - 'A' + 10;
            }
            else if (h >= 'a' && h <= 'f')
            {
                hv = h - 'a' + 10;
            }

            int lv = 0;
            if (l >= '0' && l <= '9')
            {
                lv = l - '0';
            }
            else if (l >= 'A' && l <= 'F')
            {
                lv = l - 'A' + 10;
            }
            else if (l >= 'a' && l <= 'f')
            {
                lv = l - 'a' + 10;
            }
            unsigned char byte = (unsigned char)((hv << 4) | lv);
            result = result + (char)(byte);
        }
        return result;
    }

    unsigned char getByteKey() const
    {
        return byteKey;
    }
};

#endif
