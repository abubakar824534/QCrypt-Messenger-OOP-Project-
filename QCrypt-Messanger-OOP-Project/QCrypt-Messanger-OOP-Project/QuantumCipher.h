#ifndef QUANTUMCIPHER_H
#define QUANTUMCIPHER_H

#include "Cipher.h"
#include "MyVector.h"

class QuantumCipher : public Cipher
{
protected:
    int qubits;
    double errorRate;
    MyVector<int> keyBits;
    MyString protocol;

public:
    QuantumCipher();
    virtual ~QuantumCipher();

    virtual void simulateChannel() = 0;
    virtual bool detectEavesdropper() = 0;

    double getErrorRate() const;
    MyString getProtocol() const;
};

#endif
