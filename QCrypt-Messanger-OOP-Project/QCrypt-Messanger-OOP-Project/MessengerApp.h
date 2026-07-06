#ifndef MESSENGERAPP_H
#define MESSENGERAPP_H

#include "Contact.h"
#include "Message.h"
#include "MyVector.h"
#include "CryptoManager.h"
#include "CaesarCipher.h"
#include "ROT13Cipher.h"
#include "VigenereCipher.h"
#include "XORCipher.h"
#include "RSACipher.h"
#include "BB84Cipher.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

class MessengerApp
{
private:
    Contact contacts[3];
    MyVector<Message> chats[3];
    CryptoManager* manager;
    int activeContact;
    bool eveMode;

    int readChoice()
    {
        char buf[16];
        std::cin.getline(buf, 16);
        if (buf[0] >= '0' && buf[0] <= '9')
        {
            return buf[0] - '0';
        }
        return -1;
    }

    void waitForEnter()
    {
        std::cout << std::endl << "    Press Enter to continue";
        char dummy[4];
        std::cin.getline(dummy, 4);
    }

    void clearScreen()
    {
        system("cls");
    }

    void printBanner()
    {
        std::cout << std::endl;
        std::cout << " QCrypt Messenger " << std::endl;
        std::cout << " Secure Encrypted Chat " << std::endl;
    }

    void showContacts()
    {
        std::cout << std::endl << "    Contacts:" << std::endl << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "    [" << (i + 1) << "]  " << contacts[i].getName() << "\t" << contacts[i].getPhone();
            int count = (int)(chats[i].size());
            if (count > 0)
            {
                std::cout << "   (" << count << " msgs)";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "    [4]  Toggle Eve Mode (Currently: " << (eveMode ? "ACTIVE" : "OFF") << ")" << std::endl;
        std::cout << std::endl << "    [0]  Exit" << std::endl;
    }

    void showChat(int idx)
    {
        std::cout << " Chat with " << contacts[idx].getName() << "  " << contacts[idx].getPhone() << std::endl;

        int total = (int)(chats[idx].size());
        if (total == 0)
        {
            std::cout << " (No messages yet. Send the first one!)" << std::endl;
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
                std::cout << std::endl;
            }
        }
    }

    void showCipherMenu()
    {
        std::cout << " Select Encryption:" << std::endl << std::endl;
        for (int i = 0; i < (int)(manager->getCipherCount()); ++i)
        {
            std::cout << "    [" << (i + 1) << "]  " << manager->getCipher(i)->getName() << std::endl;
        }
        std::cout << std::endl;
    }

    void sendMessage(int idx)
    {
        clearScreen();

        std::cout << " Send to: " << contacts[idx].getName() << std::endl;

        showCipherMenu();
        std::cout << "    Select cipher (1-" << manager->getCipherCount() << "): ";
        int cipherIdx = readChoice();

        if (cipherIdx < 1 || cipherIdx > manager->getCipherCount())
        {
            std::cout << std::endl << " Invalid cipher choice!" << std::endl;
            waitForEnter();
            return;
        }

        std::cout << std::endl << " Type message: ";
        char buf[256];
        std::cin.getline(buf, 256);
        MyString message(buf);

        if (message.length() == 0)
        {
            std::cout << std::endl << " Empty message! Cancelled." << std::endl;
            waitForEnter();
            return;
        }

        Cipher* cipher = manager->getCipher(cipherIdx - 1);
        if (cipher->getName() == "BB84 Quantum")
        {
            BB84Cipher* bb84 = (BB84Cipher*)cipher;
            bb84->setEveActive(eveMode);
        }

        std::cout << std::endl << " Encrypting" << std::endl;

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

        std::cout << " Message Sent!" << std::endl;
        std::cout << " Cipher   :    " << cipherName << std::endl;
        std::cout << " Encrypted: " << encrypted << std::endl;
        std::cout << " Decrypted: " << decrypted << std::endl;

        MyString decUp = decrypted.toUpper();
        if (upperMsg == decUp)
        {
            std::cout << " Status:    [OK] Decryption verified" << std::endl;
        }
        else
        {
            std::cout << " Status:    [!] Mismatch" << std::endl;
        }

        waitForEnter();
    }

    void loadChat(int idx)
    {
        MyString chatFile = contacts[idx].getChatFile();
        std::ifstream infile(chatFile.c_str());
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

    void saveMessage(int idx, const Message& msg)
    {
        MyString chatFile = contacts[idx].getChatFile();
        std::ofstream outfile(chatFile.c_str(), std::ios::app);
        if (!outfile.is_open())
        {
            return;
        }

        outfile << msg.getCipherName() << "|" << msg.getEncryptedText() << "|" << msg.getPlainText() << std::endl;
        outfile.close();
    }

public:
    MessengerApp() : activeContact(-1), eveMode(false)
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

    ~MessengerApp()
    {
        delete manager;
    }

    void run()
    {
        bool running = true;

        while (running)
        {
            clearScreen();
            printBanner();
            showContacts();

            std::cout << std::endl << " Select contact: ";
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

                    std::cout << std::endl << "    [1]  Send Message" << std::endl;
                    std::cout << "    [2]  Back to Contacts" << std::endl;
                    std::cout << std::endl << "    Choice: ";
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
        std::cout << " QCrypt Messenger Goodbye!" << std::endl;
        std::cout << " Your chats are saved and will be here next time." << std::endl;
    }
};

#endif 
