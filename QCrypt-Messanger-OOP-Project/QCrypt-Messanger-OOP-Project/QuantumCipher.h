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
    QuantumCipher() : qubits(64), errorRate(0.0), protocol("BB84")
    {
    }

    virtual ~QuantumCipher()
    {
    }

    virtual void simulateChannel() = 0;
    virtual bool detectEavesdropper() = 0;

    double getErrorRate() const
    {
        return errorRate;
    }

    MyString getProtocol() const
    {
        return protocol;
    }
};

#endif
