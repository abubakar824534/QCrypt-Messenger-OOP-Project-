#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include "Cipher.h"
#include "MyVector.h"
#include "MyString.h"
#include <iostream>

class CryptoManager
{
private:
    MyVector<Cipher*> ciphers;

public:
    CryptoManager()
    {
    }

    ~CryptoManager()
    {
        for (int i = 0; i < (int)(ciphers.size()); ++i)
        {
            delete ciphers[i];
        }
    }

    void addCipher(Cipher* c)
    {
        ciphers.push_back(c);
    }

    void runAll(const MyString& message)
    {
        for (int i = 0; i < (int)(ciphers.size()); ++i)
        {
            std::cout << std::endl << "[" << (i + 1) << "] " << ciphers[i]->getName() << std::endl;

            MyString enc = ciphers[i]->encrypt(message);
            std::cout << "Encrypted: " << enc << std::endl;

            MyString dec = ciphers[i]->decrypt(enc);
            std::cout << "Decrypted: " << dec;

            MyString origUp = message.toUpper();
            MyString decUp = dec.toUpper();
            if (origUp == decUp)
            {
                std::cout << " [OK]";
            }
            else
            {
                std::cout << " [MISMATCH]";
            }
            std::cout << std::endl;
        }
    }

    void showAllInfo()
    {
        std::cout << std::endl << "Cipher Info" << std::endl;
        for (int i = 0; i < (int)(ciphers.size()); ++i)
        {
            std::cout << "[" << (i + 1) << "] ";
            ciphers[i]->showInfo();
        }
    }

    int getCipherCount() const
    {
        return (int)(ciphers.size());
    }

    Cipher* getCipher(int index) const
    {
        if (index < 0 || index >= (int)(ciphers.size()))
        {
            return nullptr;
        }
        return ciphers[index];
    }
};

#endif