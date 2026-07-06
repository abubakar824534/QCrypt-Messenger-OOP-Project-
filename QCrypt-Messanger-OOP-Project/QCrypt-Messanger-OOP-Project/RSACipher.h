#ifndef RSACIPHER_H
#define RSACIPHER_H

#include "AsymmetricCipher.h"
#include "PrimeKeyGenerator.h"
#include "ModularArithmetic.h"
#include <iostream>
#include <cstdlib>

class RSACipher : public AsymmetricCipher
{
private:
    long long e;
    long long d;
    long long n;
    PrimeKeyGenerator* keyGen;
    ModularArithmetic* mathEngine;

public:
    RSACipher()
    {
        name = MyString("RSA-style Cipher");
        description = MyString("Public-key encryption using modular exponentiation (n=3233, e=17, d=2753)");
        isReady = true;
        keyGen = new PrimeKeyGenerator();
        mathEngine = new ModularArithmetic();
        keyGen->generate();
        e = keyGen->getPublicE();
        n = keyGen->getPublicN();
        d = keyGen->getPrivateD();
        pubE = e;
        pubN = n;
        privD = d;
        privN = n;
    }

    virtual ~RSACipher()
    {
        delete keyGen;
        delete mathEngine;
    }

    long long modPow(long long base, long long exp, long long m) const
    {
        if (m == 1)
        {
            return 0;
        }
        long long res = 1;
        base = base % m;
        while (exp > 0)
        {
            if (exp % 2 == 1)
            {
                res = (res * base) % m;
            }
            exp = exp / 2;
            base = (base * base) % m;
        }
        return res;
    }

    void generateKeys()
    {
        keyGen->generate();
        e = keyGen->getPublicE();
        n = keyGen->getPublicN();
        d = keyGen->getPrivateD();
    }

    MyString encrypt(const MyString& text) override
    {
        MyString upper = text.toUpper();
        MyString result("");
        const char digits[] = "0123456789";
        for (int i = 0; i < upper.length(); ++i)
        {
            long long m_val = (long long)((unsigned char)(upper[i]));

            int maxR = (n - 256) / 256;
            int R = (rand() % maxR) + 1;
            long long padded_m = m_val + (R * 256);

            long long c = modPow(padded_m, e, n);
            result = result + '[';
            if (c == 0)
            {
                result = result + '0';
            }
            else
            {
                char buf[20];
                int blen = 0;
                long long tmp = c;
                while (tmp > 0)
                {
                    buf[blen++] = digits[tmp % 10];
                    tmp /= 10;
                }
                for (int j = blen - 1; j >= 0; --j)
                {
                    result = result + buf[j];
                }
            }
            result = result + ']';
        }
        return result;
    }

    MyString decrypt(const MyString& text) override
    {
        MyString result("");
        int i = 0;
        while (i < text.length())
        {
            if (text[i] == '[')
            {
                ++i;
                long long c = 0;
                while (i < text.length() && text[i] != ']')
                {
                    c = c * 10 + (text[i] - '0');
                    ++i;
                }
                if (i < text.length()) ++i;
                long long padded_m = modPow(c, d, n);

                long long m_val = padded_m % 256;

                result = result + (char)(m_val);
            }
            else
            {
                ++i;
            }
        }
        return result;
    }

    void showInfo() override
    {
        std::cout << "  Cipher : " << name << std::endl;
        std::cout << "  Desc   : " << description << std::endl;
        std::cout << "  Public  key (e,n) = (" << e << "," << n << ")" << std::endl;
        std::cout << "  Private key (d,n) = (" << d << "," << n << ")" << std::endl;
    }

    MyString getName() const override
    {
        return name;
    }

    MyString getRSAStats() const
    {
        return MyString::fromInt(e) + "|" + MyString::fromInt(n) + "|" + MyString::fromInt(d);
    }
};

#endif
