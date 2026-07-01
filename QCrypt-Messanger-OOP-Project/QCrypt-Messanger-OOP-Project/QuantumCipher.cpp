#include "QuantumCipher.h"

QuantumCipher::QuantumCipher() :qubits(64), errorRate(0.0), protocol("BB84")
{

}

QuantumCipher::~QuantumCipher()
{

}

double QuantumCipher::getErrorRate()const
{
    return errorRate;
}
MyString QuantumCipher::getProtocol()const
{
    return protocol;
}
