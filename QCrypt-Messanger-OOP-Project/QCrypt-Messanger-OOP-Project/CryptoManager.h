#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include "Cipher.h"
#include "MyVector.h"
#include "MyString.h"

class CryptoManager
{
private:
    MyVector<Cipher*> ciphers;

public:
    CryptoManager();
    ~CryptoManager();

    void addCipher(Cipher* c);
    void runAll(const MyString& message);
    void showAllInfo();
    int getCipherCount() const;
    Cipher* getCipher(int index) const;
};

#endif