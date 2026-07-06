#ifndef MATHENGINE_H
#define MATHENGINE_H

class MathEngine
{
protected:
    long long result;
    long long operandA;
    long long operandB;
    long long modulus;

public:
    MathEngine() : result(0), operandA(0), operandB(0), modulus(1)
    {
    }

    virtual ~MathEngine()
    {
    }

    virtual long long compute(long long a, long long b, long long mod) = 0;

    long long getResult() const
    {
        return result;
    }

    void setOperands(long long a, long long b, long long mod)
    {
        operandA = a;
        operandB = b;
        modulus = mod;
    }

    void reset()
    {
        result = 0;
        operandA = 0;
        operandB = 0;
        modulus = 1;
    }

    bool validate(long long n) const
    {
        return n > 0;
    }
};

#endif
