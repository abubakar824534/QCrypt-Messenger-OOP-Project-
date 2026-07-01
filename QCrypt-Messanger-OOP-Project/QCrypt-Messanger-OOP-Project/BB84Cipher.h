#ifndef BB84CIPHER_H
#define BB84CIPHER_H

#include "QuantumCipher.h"
#include "Alice.h"
#include "Bob.h"
#include "QuantumChannel.h"
#include "IdealChannel.h"
#include "Eve.h"

class BB84Cipher : public QuantumCipher
{
private:
    Alice* alice;
    Bob* bob;
    Eve* eve;
    QuantumChannel* channel;
    MyVector<int> sharedKey;
    double errorThreshold;
    int numQubits;
    bool eveActive;

public:
    BB84Cipher(int nQubits = 64, long long seed = 42);
    virtual ~BB84Cipher();

    MyString encrypt(const MyString& text) override;
    MyString decrypt(const MyString& text) override;
    void showInfo() override;
    MyString getName() const override;

    void simulateChannel() override;
    bool detectEavesdropper() override;
    void setEveActive(bool active);
    bool runBB84Protocol();
    MyVector<int> reconcileBases();
    MyString xorWithKey(const MyString& text);
    MyString getBB84Stats() const;
};

#endif
