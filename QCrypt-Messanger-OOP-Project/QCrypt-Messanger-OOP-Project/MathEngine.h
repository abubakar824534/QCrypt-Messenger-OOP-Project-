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
    MathEngine();
    virtual ~MathEngine();

    virtual long long compute(long long a, long long b, long long mod) = 0;

    long long getResult() const;
    void setOperands(long long a, long long b, long long mod);
    void reset();
    bool validate(long long n) const;
};

#endif
