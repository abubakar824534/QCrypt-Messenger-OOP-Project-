#ifndef MESSENGERAPP_H
#define MESSENGERAPP_H

#include "Contact.h"
#include "Message.h"
#include "MyVector.h"
#include "CryptoManager.h"

class MessengerApp
{
private:
    Contact contacts[3];
    MyVector<Message> chats[3];
    CryptoManager* manager;
    int activeContact;
    bool eveMode;

    int  readChoice();
    void waitForEnter();
    void clearScreen();


    void printBanner();
    void showContacts();
    void showChat(int idx);
    void sendMessage(int idx);
    void showCipherMenu();


    void loadChat(int idx);
    void saveMessage(int idx, const Message& msg);

public:
    MessengerApp();
    ~MessengerApp();
    void run();
};

#endif 
