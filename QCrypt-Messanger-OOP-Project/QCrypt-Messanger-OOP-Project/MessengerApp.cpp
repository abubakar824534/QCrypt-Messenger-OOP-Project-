#include "MessengerApp.h"
#include "CaesarCipher.h"
#include "ROT13Cipher.h"
#include "VigenereCipher.h"
#include "XORCipher.h"
#include "RSACipher.h"
#include "BB84Cipher.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

MessengerApp::MessengerApp() :activeContact(-1), eveMode(false)
{
    contacts[0] = Contact("Hafiz Abdullah", "+92-300-1234567", "chat_hafiz.txt");
    contacts[1] = Contact("Omer Abdullah", "+92-321-9876543", "chat_omer.txt");
    contacts[2] = Contact("Tayyab Ahmed", "+92-333-5556789", "chat_tayyab.txt");

    manager = new CryptoManager();
    manager->addCipher(new CaesarCipher(7));
    manager->addCipher(new ROT13Cipher());
    manager->addCipher(new VigenereCipher("KEY"));
    manager->addCipher(new XORCipher(0xAB));
    manager->addCipher(new RSACipher());
    manager->addCipher(new BB84Cipher(128, 42));

    for (int i = 0; i < 3; ++i)
    {
        loadChat(i);
    }
}

MessengerApp::~MessengerApp()
{
    delete manager;
}

int MessengerApp::readChoice()
{
    char buf[16];
    cin.getline(buf, 16);
    if (buf[0] >= '0' && buf[0] <= '9')
    {
        return buf[0] - '0';
    }
    return -1;
}

void MessengerApp::waitForEnter()
{
    cout << endl << "    Press Enter to continue";
    char dummy[4];
    cin.getline(dummy, 4);
}

void MessengerApp::clearScreen()
{
    system("cls");
}

void MessengerApp::printBanner()
{
    cout << endl;

    cout << " QCrypt Messenger " << endl;
    cout << " Secure Encrypted Chat " << endl;

}

void MessengerApp::showContacts()
{
    cout << endl << "    Contacts:" << endl << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "    [" << (i + 1) << "]  " << contacts[i].getName() << "\t" << contacts[i].getPhone();
        int count = (int)(chats[i].size());
        if (count > 0)
        {
            cout << "   (" << count << " msgs)";
        }
        cout << endl;
    }
    cout << endl << "    [4]  Toggle Eve Mode (Currently: " << (eveMode ? "ACTIVE" : "OFF") << ")" << endl;
    cout << endl << "    [0]  Exit" << endl;
}

void MessengerApp::showChat(int idx)
{

    cout << " Chat with " << contacts[idx].getName() << "  " << contacts[idx].getPhone() << endl;


    int total = (int)(chats[idx].size());
    if (total == 0)
    {
        cout << " (No messages yet. Send the first one!)" << endl;
    }
    else
    {
        int start;
        if (total > 20)
        {
            start = total - 20;
        }
        else
        {
            start = 0;
        }
        for (int i = start; i < total; ++i)
        {
            chats[idx][i].display();
            cout << endl;
        }
    }

}

void MessengerApp::showCipherMenu()
{
    cout << " Select Encryption:" << endl << endl;
    for (int i = 0; i < (int)(manager->getCipherCount()); ++i)
    {
        cout << "    [" << (i + 1) << "]  " << manager->getCipher(i)->getName() << endl;
    }
    cout << endl;
}

void MessengerApp::sendMessage(int idx)
{
    clearScreen();

    cout << " Send to: " << contacts[idx].getName() << endl;


    showCipherMenu();
    cout << "    Select cipher (1-" << manager->getCipherCount() << "): ";
    int cipherIdx = readChoice();

    if (cipherIdx < 1 || cipherIdx > manager->getCipherCount())
    {
        cout << endl << " Invalid cipher choice!" << endl;
        waitForEnter();
        return;
    }

    cout << endl << " Type message: ";
    char buf[256];
    cin.getline(buf, 256);
    MyString message(buf);

    if (message.length() == 0)
    {
        cout << endl << " Empty message! Cancelled." << endl;
        waitForEnter();
        return;
    }

    Cipher* cipher = manager->getCipher(cipherIdx - 1);
    if (cipher->getName() == "BB84 Quantum")
    {
        BB84Cipher* bb84 = (BB84Cipher*)cipher;
        bb84->setEveActive(eveMode);
    }

    cout << endl << " Encrypting" << endl;

    MyString encrypted = cipher->encrypt(message);
    MyString cipherName = cipher->getName();

    MyString extraInfo("");
    if (cipher->getName() == "BB84 Quantum")
    {
        BB84Cipher* bb84 = (BB84Cipher*)cipher;
        extraInfo = bb84->getBB84Stats();
    }
    else if (cipher->getName() == "RSA-style Cipher")
    {
        RSACipher* rsa = (RSACipher*)cipher;
        extraInfo = rsa->getRSAStats();
    }

    MyString decrypted = cipher->decrypt(encrypted);

    MyString upperMsg = message.toUpper();
    Message msg(upperMsg, encrypted, cipherName, extraInfo);
    chats[idx].push_back(msg);
    saveMessage(idx, msg);

    cout << " Message Sent!" << endl;
    cout << " Cipher   :    " << cipherName << endl;
    cout << " Encrypted: " << encrypted << endl;
    cout << " Decrypted: " << decrypted << endl;

    MyString decUp = decrypted.toUpper();
    if (upperMsg == decUp)
    {
        cout << " Status:    [OK] Decryption verified" << endl;
    }
    else
    {
        cout << " Status:    [!] Mismatch" << endl;
    }

    waitForEnter();
}

void MessengerApp::loadChat(int idx)
{
    MyString chatFile = contacts[idx].getChatFile();
    ifstream infile(chatFile.c_str());
    if (!infile.is_open())
    {
        return;
    }

    char line[1024];
    while (infile.getline(line, 1024))
    {
        int len = 0;
        while (line[len] != '\0')
        {
            ++len;
        }
        if (len != 0)
        {
            int pipe1 = -1, pipe2 = -1;
            for (int i = 0; i < len; ++i)
            {
                if (line[i] == '|')
                {
                    if (pipe1 == -1)
                    {
                        pipe1 = i;
                    }
                    else if (pipe2 == -1)
                    {
                        pipe2 = i;
                        break;
                    }
                }
            }
            if (pipe1 != -1 && pipe2 != -1)
            {
                char cipherBuf[256];
                int j = 0;
                for (int i = 0; i < pipe1 && j < 255; ++i)
                {
                    cipherBuf[j++] = line[i];
                }
                cipherBuf[j] = '\0';

                char encBuf[512];
                j = 0;
                for (int i = pipe1 + 1; i < pipe2 && j < 511; ++i)
                {
                    encBuf[j++] = line[i];
                }
                encBuf[j] = '\0';

                char plainBuf[256];
                j = 0;
                for (int i = pipe2 + 1; i < len && j < 255; ++i)
                {
                    plainBuf[j++] = line[i];
                }
                plainBuf[j] = '\0';

                MyString plainStr(plainBuf);
                MyString encStr(encBuf);
                MyString cipherStr(cipherBuf);
                Message msg(plainStr, encStr, cipherStr);
                chats[idx].push_back(msg);
            }
        }
    }
    infile.close();
}

void MessengerApp::saveMessage(int idx, const Message& msg)
{
    MyString chatFile = contacts[idx].getChatFile();
    ofstream outfile(chatFile.c_str(), ios::app);
    if (!outfile.is_open())
    {
        return;
    }

    outfile << msg.getCipherName() << "|" << msg.getEncryptedText() << "|" << msg.getPlainText() << endl;
    outfile.close();
}

void MessengerApp::run()
{
    bool running = true;

    while (running)
    {
        clearScreen();
        printBanner();
        showContacts();

        cout << endl << " Select contact: ";
        int choice = readChoice();

        if (choice == 0)
        {
            running = false;
        }
        else if (choice == 4)
        {
            eveMode = !eveMode;
        }
        else if (choice >= 1 && choice <= 3)
        {
            activeContact = choice - 1;

            bool inChat = true;
            while (inChat)
            {
                clearScreen();
                showChat(activeContact);

                cout << endl << "    [1]  Send Message" << endl;
                cout << "    [2]  Back to Contacts" << endl;
                cout << endl << "    Choice: ";
                int chatChoice = readChoice();

                if (chatChoice == 1)
                {
                    sendMessage(activeContact);
                }
                else
                {
                    inChat = false;
                }
            }
        }
    }

    clearScreen();
    cout << " QCrypt Messenger Goodbye!" << endl;
    cout << " Your chats are saved and will be here next time." << endl;
}
