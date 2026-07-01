#ifndef EVE_H
#define EVE_H

#include "Party.h"
#include "RandomGen.h"

class Eve : public Party
{
private:
    MyVector<int> interceptedBits;
    MyVector<int> interceptedBases;
    int interceptCount;
    RandomGen* rng;

public:
    Eve(long long seed = 999);
    virtual ~Eve();

    void prepare(int n) override;
    int measure(int photon, int b) override;
    int intercept(int photon);
    int getInterceptCount() const;
};

#endif
