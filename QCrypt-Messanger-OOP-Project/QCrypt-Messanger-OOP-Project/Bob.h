#ifndef BOB_H
#define BOB_H

#include "Party.h"
#include "RandomGen.h"

class Bob : public Party
{
private:
    MyVector<int> measuredBits;
    MyVector<int> randomBases;
    int photonsReceived;
    RandomGen* rng;

public:
    Bob(long long seed = 123);
    virtual ~Bob();

    void prepare(int n) override;
    int measure(int photon, int b) override;
    void receiveAndMeasure(int photon, int basisChoice);
    int getPhotonsReceived() const;
};

#endif
