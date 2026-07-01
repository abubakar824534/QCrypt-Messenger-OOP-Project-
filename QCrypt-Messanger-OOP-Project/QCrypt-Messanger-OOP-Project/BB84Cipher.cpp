#include "BB84Cipher.h"
#include <iostream>

using namespace std;

BB84Cipher::BB84Cipher(int nQubits, long long seed) :errorThreshold(0.20), numQubits(nQubits)
{
    name = MyString("BB84 Quantum");
    description = MyString("Quantum Key Distribution using BB84 protocol");
    keySize = nQubits;
    isReady = false;
    protocol = MyString("BB84");
    qubits = nQubits;

    alice = new Alice(seed);
    bob = new Bob(seed + 1);
    eve = new Eve(seed + 2);
    channel = new IdealChannel();
    eveActive = false;
}

BB84Cipher::~BB84Cipher()
{
    delete alice;
    delete bob;
    delete eve;
    delete channel;
}

void BB84Cipher::setEveActive(bool active)
{
    eveActive = active;
}

bool BB84Cipher::runBB84Protocol()
{
    int maxRetries = 10;
    for (int attempt = 0; attempt < maxRetries; ++attempt)
    {
        sharedKey.clear();

        alice->prepare(numQubits);
        bob->prepare(numQubits);

        if (eveActive)
        {
            eve->prepare(numQubits);
        }

        MyVector<int> aliceBits = alice->getBits();
        MyVector<int> aliceBases = alice->getBases();
        MyVector<int> bobBases = bob->getBases();

        for (int i = 0; i < numQubits; ++i)
        {
            int photon = alice->sendPhoton(i, channel);
            if (eveActive)
            {
                photon = eve->intercept(photon);
            }
            int bobBasis = bobBases[i];
            bob->receiveAndMeasure(photon, bobBasis);
        }

        MyVector<int> siftedKey;
        MyVector<int> bobFinal = bob->getBits();

        for (int i = 0; i < numQubits; ++i)
        {
            if (aliceBases[i] == bobBases[i])
            {
                siftedKey.push_back(aliceBits[i]);
            }
        }

        if (siftedKey.size() != 0)
        {
            int sampleSize = (int)(siftedKey.size()) / 4;
            if (sampleSize < 1)
            {
                sampleSize = 1;
            }
            int errors = 0;
            for (int i = 0; i < sampleSize; ++i)
            {
                int ai = -1, bi = -1, cnt = 0;
                for (int j = 0; j < numQubits; ++j)
                {
                    if (aliceBases[j] == bobBases[j])
                    {
                        if (cnt == i)
                        {
                            ai = aliceBits[j];
                            bi = bobFinal[j];
                            break;
                        }
                        ++cnt;
                    }
                }
                if (ai != -1 && ai != bi)
                {
                    ++errors;
                }
            }

            if (sampleSize > 0)
            {
                errorRate = ((double)(errors) / sampleSize);
            }
            else
            {
                errorRate = 0.0;
            }

            if (errorRate > errorThreshold)
            {
                cout << "  [BB84] High error rate (" << (int)(errorRate * 100) << "%), regenerating key" << endl;
                if (eveActive)
                {
                    sharedKey.clear();
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < (int)(siftedKey.size()); ++i)
                {
                    sharedKey.push_back(siftedKey[i]);
                }

                keyBits = sharedKey;
                isReady = true;
                return true;
            }
        }

    }
    return false;
}

MyVector<int> BB84Cipher::reconcileBases()
{
    return sharedKey;
}

void BB84Cipher::simulateChannel()
{
    runBB84Protocol();
}

bool BB84Cipher::detectEavesdropper()
{
    return errorRate > errorThreshold;
}

MyString BB84Cipher::xorWithKey(const MyString& text)
{
    if (sharedKey.size() == 0)
    {
        return text;
    }
    int keySz = (int)(sharedKey.size());
    MyString result("");
    for (int i = 0; i < text.length(); ++i)
    {
        int k = sharedKey[i % keySz];
        char out = (char)((unsigned char)(text[i]) ^ (unsigned char)(k));
        result = result + out;
    }
    return result;
}

MyString BB84Cipher::encrypt(const MyString& text)
{
    runBB84Protocol();
    cout << "Key: ";
    int dispLen;
    if ((int)(sharedKey.size()) < 16)
    {
        dispLen = (int)(sharedKey.size());
    }
    else
    {
        dispLen = 16;
    }
    for (int i = 0; i < dispLen; ++i)
    {
        cout << sharedKey[i];
    }
    if ((int)(sharedKey.size()) > 16)
    {
        cout << "...";
    }
    cout << endl;
    MyString upper = text.toUpper();
    return xorWithKey(upper);
}

MyString BB84Cipher::decrypt(const MyString& cipher)
{
    MyString result = xorWithKey(cipher);
    return result;
}

void BB84Cipher::showInfo()
{
    cout << "  Cipher   : " << name << endl;
    cout << "  Protocol : " << protocol << endl;
    cout << "  Qubits   : " << qubits << endl;
    cout << "  KeyBits  : " << sharedKey.size() << endl;
    cout << "  ErrorRate: " << (int)(errorRate * 100) << "%" << endl;
}

MyString BB84Cipher::getName()const
{
    return name;
}

MyString BB84Cipher::getBB84Stats()const
{
    int keyLen = (int)(sharedKey.size());
    int photonsSent;
    if (alice)
    {
        photonsSent = alice->getPhotonsSent();
    }
    else
    {
        photonsSent = 0;
    }

    int photonsRcvd;
    if (bob)
    {
        photonsRcvd = bob->getPhotonsReceived();
    }
    else
    {
        photonsRcvd = 0;
    }

    int errPct = (int)(errorRate * 100);
    int eveDetected;
    if (errorRate > errorThreshold && eveActive)
    {
        eveDetected = 1;
    }
    else
    {
        eveDetected = 0;
    }

    char keyPreview[512];
    int dispLen;
    if (keyLen < 511)
    {
        dispLen = keyLen;
    }
    else
    {
        dispLen = 511;
    }

    for (int i = 0; i < dispLen; ++i)
    {
        if (sharedKey[i] == 1)
        {
            keyPreview[i] = '1';
        }
        else
        {
            keyPreview[i] = '0';
        }
    }
    keyPreview[dispLen] = '\0';
    if (dispLen == 0)
    {
        keyPreview[0] = '-';
        keyPreview[1] = '\0';
    }

    MyString result = MyString::fromInt(keyLen) + "|" + MyString::fromInt(errPct) + "|" + MyString::fromInt(photonsSent) + "|" + MyString::fromInt(photonsRcvd) + "|" + MyString::fromInt(eveDetected) + "|" + keyPreview;

    return result;
}
