#include "MathEngine.h"

MathEngine::MathEngine() :result(0), operandA(0), operandB(0), modulus(1)
{

}

MathEngine::~MathEngine()
{

}

long long MathEngine::getResult()const
{
    return result;
}

void MathEngine::setOperands(long long a, long long b, long long mod)
{
    operandA = a;
    operandB = b;
    modulus = mod;
}

void MathEngine::reset()
{
    result = 0;
    operandA = 0;
    operandB = 0;
    modulus = 1;
}

bool MathEngine::validate(long long n)const
{
    return n > 0;
}
