#ifndef ALICE_H
#define ALICE_H

#include "Party.h"
#include "RandomGen.h"
#include "QuantumChannel.h"

class Alice : public Party
{
private:
    MyVector<int> randomBits;
    MyVector<int> randomBases;
    int photonsSent;
    RandomGen* rng;

public:
    Alice(long long seed = 42);
    virtual ~Alice();

    void prepare(int n) override;
    int measure(int photon, int b) override;
    int sendPhoton(int i, QuantumChannel* ch);
    void generateRandomBits(int n);
    int getPhotonsSent() const;
};

#endif
