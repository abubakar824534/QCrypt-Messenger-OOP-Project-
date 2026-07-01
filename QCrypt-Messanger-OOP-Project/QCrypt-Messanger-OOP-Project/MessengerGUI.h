#ifndef MESSENGERGUI_H
#define MESSENGERGUI_H

#include "Contact.h"
#include "CryptoManager.h"
#include "Message.h"
#include "MyVector.h"
#include "raylib.h"

class MessengerGUI
{
private:
    Contact contacts[3];
    MyVector<Message> chats[3];
    CryptoManager* manager;
    int activeContact;

    int selectedCipher;
    char inputBuffer[256];
    int inputLen;
    int scrollOffset; 
    bool cipherDropdownOpen;
    int backspaceTimer;
    bool eveMode;

    Color headerColor;
    Color sidebarBg;
    Color chatBg;
    Color bubbleColor;
    Color sendBtnColor;
    Color tealColor;
    Color textColor;
    Color lightText;
    Color selectedBg;
    Color inputBg;
    Color borderColor;

    static const int WIN_W = 1000;
    static const int WIN_H = 700;
    static const int SIDEBAR_W = 300;
    static const int HEADER_H = 60;
    static const int INPUT_H = 70;
    static const int CONTACT_ITEM_H = 80;
    static const int BUBBLE_H = 100;
    static const int BUBBLE_GAP = 15;

    Font mainFont;
    void drawText(const char* text, float x, float y, float fontSize, Color color);
    float measureText(const char* text, float fontSize);

    void loadChat(int idx);
    void saveMessage(int idx, const Message& msg);

    int getChatHeight(int contactIdx);

    void drawSidebar();
    void drawChatHeader();
    void drawChatMessages();
    void drawInputBar();
    void drawCipherDropdown();

    void handleInput();
    void sendCurrentMessage();

public:
    MessengerGUI();
    ~MessengerGUI();

    bool init();
    void run();
    void close();
};

#endif