#include "CryptoManager.h"
#include <iostream>

using namespace std;

CryptoManager::CryptoManager()
{

}

CryptoManager::~CryptoManager()
{
    for (int i = 0; i < (int)(ciphers.size()); ++i)
    {
        delete ciphers[i];
    }
}

void CryptoManager::addCipher(Cipher* c)
{
    ciphers.push_back(c);
}

void CryptoManager::runAll(const MyString& message)
{
    for (int i = 0; i < (int)(ciphers.size()); ++i)
    {
        cout << endl << "[" << (i + 1) << "] " << ciphers[i]->getName() << endl;

        MyString enc = ciphers[i]->encrypt(message);
        cout << "Encrypted: " << enc << endl;

        MyString dec = ciphers[i]->decrypt(enc);
        cout << "Decrypted: " << dec;

        MyString origUp = message.toUpper();
        MyString decUp = dec.toUpper();
        if (origUp == decUp)
        {
            cout << " [OK]";
        }
        else
        {
            cout << " [MISMATCH]";
        }
        cout << endl;
    }
}

void CryptoManager::showAllInfo()
{
    cout << endl << "Cipher Info" << endl;
    for (int i = 0; i < (int)(ciphers.size()); ++i)
    {
        cout << "[" << (i + 1) << "] ";
        ciphers[i]->showInfo();
    }
}

int CryptoManager::getCipherCount()const
{
    return (int)(ciphers.size());
}

Cipher* CryptoManager::getCipher(int index)const
{
    if (index < 0 || index >= (int)(ciphers.size()))
    {
        return nullptr;
    }
    return ciphers[index];
}
