#ifndef MESSENGERGUI_H
#define MESSENGERGUI_H

#include "Contact.h"
#include "CryptoManager.h"
#include "Message.h"
#include "MyVector.h"
#include "raylib.h"
#include "BB84Cipher.h"
#include "CaesarCipher.h"
#include "ROT13Cipher.h"
#include "RSACipher.h"
#include "VigenereCipher.h"
#include "XORCipher.h"
#include <fstream>
#include <iostream>

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

    static Color makeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        Color c;
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = a;
        return c;
    }

    static Rectangle makeRect(float x, float y, float w, float h)
    {
        Rectangle r;
        r.x = x;
        r.y = y;
        r.width = w;
        r.height = h;
        return r;
    }

    void drawText(const char* text, float x, float y, float fontSize, Color color)
    {
        Vector2 pos;
        pos.x = x;
        pos.y = y;
        if (mainFont.texture.id == 0)
        {
            DrawText(text, (int)x, (int)y, (int)fontSize, color);
        }
        else
        {
            DrawTextEx(mainFont, text, pos, fontSize, 1.0f, color);
        }
    }

    float measureText(const char* text, float fontSize)
    {
        if (mainFont.texture.id == 0)
        {
            return (float)MeasureText(text, (int)fontSize);
        }
        return MeasureTextEx(mainFont, text, fontSize, 1.0f).x;
    }

    int getChatHeight(int contactIdx)
    {
        if (contactIdx < 0 || contactIdx >= 3)
        {
            return 0;
        }
        int height = 0;
        for (int i = 0; i < chats[contactIdx].size(); ++i)
        {
            int infoH;
            if (chats[contactIdx][i].hasCipherInfo())
            {
                infoH = 90;
            }
            else
            {
                infoH = 0;
            }
            height += BUBBLE_H + infoH + BUBBLE_GAP;
        }
        return height;
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
                            pipe1 = i;
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
                    chats[idx].push_back(Message(plainStr, encStr, cipherStr));
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

    void drawSidebar()
    {
        DrawRectangle(0, 0, SIDEBAR_W, WIN_H, sidebarBg);
        DrawRectangle(0, 0, SIDEBAR_W, HEADER_H, headerColor);

        drawText("Contacts", 20.0f, 15.0f, 24.0f, WHITE);
        DrawLine(SIDEBAR_W - 1, 0, SIDEBAR_W - 1, WIN_H, borderColor);

        for (int i = 0; i < 3; ++i)
        {
            Rectangle itemRect = makeRect(0.0f, (float)(HEADER_H + i * CONTACT_ITEM_H), (float)(SIDEBAR_W - 1), (float)CONTACT_ITEM_H);

            if (activeContact == i)
            {
                DrawRectangleRec(itemRect, selectedBg);
            }
            else if (CheckCollisionPointRec(GetMousePosition(), itemRect))
            {
                DrawRectangleRec(itemRect, makeColor(245, 245, 245, 255));
            }

            drawText(contacts[i].getName().c_str(), 20.0f, itemRect.y + 15.0f, 22.0f, textColor);
            drawText(contacts[i].getPhone().c_str(), 20.0f, itemRect.y + 45.0f, 16.0f, lightText);

            int count = chats[i].size();
            if (count > 0)
            {
                MyString cntStr = MyString::fromInt(count);
                DrawCircle(SIDEBAR_W - 25, (int)(itemRect.y + 40.0f), 12.0f, tealColor);
                drawText(cntStr.c_str(), (float)(SIDEBAR_W - 25) - measureText(cntStr.c_str(), 14.0f) / 2.0f, itemRect.y + 33.0f, 14.0f, WHITE);
            }

            DrawLine(20, (int)(itemRect.y + CONTACT_ITEM_H - 1), SIDEBAR_W - 20, (int)(itemRect.y + CONTACT_ITEM_H - 1), borderColor);
        }
    }

    void drawChatHeader()
    {
        DrawRectangle(SIDEBAR_W, 0, WIN_W - SIDEBAR_W, HEADER_H, headerColor);
        if (activeContact >= 0)
        {
            drawText(contacts[activeContact].getName().c_str(), (float)(SIDEBAR_W + 20), 10.0f, 24.0f, WHITE);
            drawText(contacts[activeContact].getPhone().c_str(), (float)(SIDEBAR_W + 20), 38.0f, 16.0f, makeColor(200, 200, 200, 255));
        }
        else
        {
            drawText("Select a contact to start chatting", (float)(SIDEBAR_W + 20), 15.0f, 24.0f, WHITE);
        }

        Rectangle eveBtn = { 700.0f, 15.0f, 140.0f, 30.0f };
        Color eveColor;
        if (eveMode)
        {
            eveColor = makeColor(220, 50, 50, 255);
        }
        else
        {
            eveColor = makeColor(150, 150, 150, 255);
        }
        DrawRectangleRounded(eveBtn, 0.2f, 10, eveColor);

        const char* eveTxt;
        if (eveMode)
        {
            eveTxt = "Eve: ACTIVE";
        }
        else
        {
            eveTxt = "Eve: OFF";
        }
        int tW = MeasureText(eveTxt, 16);
        drawText(eveTxt, 700.0f + (140.0f - (float)tW) / 2.0f, 22.0f, 16.0f, WHITE);
    }

    void drawChatMessages()
    {
        DrawRectangle(SIDEBAR_W, HEADER_H, WIN_W - SIDEBAR_W, WIN_H - HEADER_H - INPUT_H, chatBg);

        if (activeContact < 0)
        {
            return;
        }

        int totalMsgs = chats[activeContact].size();
        if (totalMsgs == 0)
        {
            return;
        }

        int totalHeight = getChatHeight(activeContact) + 40;
        int visibleHeight = WIN_H - HEADER_H - INPUT_H;

        BeginScissorMode(SIDEBAR_W, HEADER_H, WIN_W - SIDEBAR_W, visibleHeight);

        int yPos = HEADER_H + 20 - scrollOffset;

        for (int i = 0; i < totalMsgs; ++i)
        {
            Message& msg = chats[activeContact][i];

            bool hasInfo = msg.hasCipherInfo();
            int infoPanelH;
            if (hasInfo)
            {
                infoPanelH = 90;
            }
            else
            {
                infoPanelH = 0;
            }
            int totalBubbleH = BUBBLE_H + infoPanelH;

            if (yPos + totalBubbleH < HEADER_H || yPos > WIN_H - INPUT_H)
            {
                yPos += totalBubbleH + BUBBLE_GAP;
            }
            else
            {
                int bubbleW = WIN_W - SIDEBAR_W - 80;
                int bubbleX = SIDEBAR_W + 40;

                DrawRectangleRounded(makeRect((float)bubbleX, (float)yPos, (float)bubbleW, (float)BUBBLE_H), 0.2f, 10, bubbleColor);

                drawText(msg.getCipherName().c_str(), (float)(bubbleX + 15), (float)(yPos + 10), 18.0f, tealColor);

                drawText("Encrypted:", (float)(bubbleX + 15), (float)(yPos + 35), 16.0f, lightText);
                drawText(msg.getEncryptedText().c_str(), (float)(bubbleX + 100), (float)(yPos + 35), 18.0f, textColor);

                drawText("Decrypted:", (float)(bubbleX + 15), (float)(yPos + 60), 16.0f, lightText);
                drawText(msg.getPlainText().c_str(), (float)(bubbleX + 100), (float)(yPos + 60), 18.0f, BLACK);

                if (hasInfo)
                {
                    int infoY = yPos + BUBBLE_H + 4;
                    Color infoBg = makeColor(224, 242, 241, 255);
                    Color infoBorder = makeColor(0, 150, 136, 255);

                    DrawRectangleRounded(makeRect((float)bubbleX, (float)infoY, (float)bubbleW, (float)(infoPanelH - 8)), 0.15f, 10, infoBg);
                    DrawRectangleRoundedLines(makeRect((float)bubbleX, (float)infoY, (float)bubbleW, (float)(infoPanelH - 8)), 0.15f, 10, infoBorder);

                    MyString infoStr = msg.getCipherInfo();
                    MyString cipherName = msg.getCipherName();
                    const char* info = infoStr.c_str();

                    if (cipherName == "BB84 Quantum")
                    {
                        int keyLen = 0, errPct = 0, pSent = 0, pRcvd = 0, eveDetected = 0;
                        char keyPreview[512] = { 0 };

                        int* targetInts[5] = { &keyLen, &errPct, &pSent, &pRcvd, &eveDetected };
                        int currentTarget = 0;
                        int j = 0;
                        while (info[j] != '\0' && currentTarget < 5)
                        {
                            int val = 0;
                            while (info[j] >= '0' && info[j] <= '9')
                            {
                                val = val * 10 + (info[j] - '0');
                                j++;
                            }
                            *targetInts[currentTarget] = val;
                            currentTarget++;
                            if (info[j] == '|')
                            {
                                j++;
                            }
                        }
                        int k = 0;
                        while (info[j] != '\0' && k < 511)
                        {
                            keyPreview[k++] = info[j++];
                        }
                        keyPreview[k] = '\0';

                        if (eveDetected)
                        {
                            drawText("[!] EVE DETECTED! Key Aborted", (float)(bubbleX + 15), (float)(infoY + 6), 16.0f, makeColor(220, 50, 50, 255));
                        }
                        else
                        {
                            drawText("BB84 Protocol Simulation", (float)(bubbleX + 15), (float)(infoY + 6), 16.0f, infoBorder);
                        }

                        MyString statLine1 = MyString("Key Length: ") + MyString::fromInt(keyLen) + " bits   |   Error Rate: " + MyString::fromInt(errPct) + "%   |   Photons Sent: " + MyString::fromInt(pSent) + "   |   Received: " + MyString::fromInt(pRcvd);
                        drawText(statLine1.c_str(), (float)(bubbleX + 15), (float)(infoY + 28), 15.0f, textColor);

                        MyString statLine2 = MyString("Shared Key: ") + keyPreview;
                        drawText(statLine2.c_str(), (float)(bubbleX + 15), (float)(infoY + 50), 15.0f, makeColor(60, 60, 60, 255));
                    }
                    else if (cipherName == "RSA-style Cipher")
                    {
                        int e_val = 0, n_val = 0, d_val = 0;
                        int* targetInts[3] = { &e_val, &n_val, &d_val };
                        int currentTarget = 0;
                        int j = 0;
                        while (info[j] != '\0' && currentTarget < 3)
                        {
                            int val = 0;
                            while (info[j] >= '0' && info[j] <= '9')
                            {
                                val = val * 10 + (info[j] - '0');
                                j++;
                            }
                            *targetInts[currentTarget] = val;
                            currentTarget++;
                            if (info[j] == '|') j++;
                        }

                        drawText("RSA Encryption Details", (float)(bubbleX + 15), (float)(infoY + 6), 16.0f, infoBorder);

                        MyString statLine1 = MyString("Public Key (e,n): (") + MyString::fromInt(e_val) + "," + MyString::fromInt(n_val) + ")   |   Private Key (d,n): (" + MyString::fromInt(d_val) + "," + MyString::fromInt(n_val) + ")";
                        drawText(statLine1.c_str(), (float)(bubbleX + 15), (float)(infoY + 28), 15.0f, textColor);

                        MyString statLine2 = MyString("Padding applied: Yes (Semantic Security using Rand)");
                        drawText(statLine2.c_str(), (float)(bubbleX + 15), (float)(infoY + 50), 15.0f, makeColor(60, 60, 60, 255));
                    }
                }

                yPos += totalBubbleH + BUBBLE_GAP;
            }
        }

        if (totalHeight > visibleHeight)
        {
            int maxScroll = totalHeight - visibleHeight;
            if (maxScroll > 0)
            {
                float scrollbarHeight = ((float)visibleHeight / (float)totalHeight) * (float)visibleHeight;
                if (scrollbarHeight < 20.0f) scrollbarHeight = 20.0f;

                float thumbY = (float)HEADER_H + ((float)scrollOffset / (float)maxScroll) * ((float)visibleHeight - scrollbarHeight);
                DrawRectangle(WIN_W - 12, (int)thumbY, 8, (int)scrollbarHeight, makeColor(0, 0, 0, 50));
            }
        }

        EndScissorMode();
    }

    void drawInputBar()
    {
        if (activeContact < 0)
        {
            return;
        }

        int inputY = WIN_H - INPUT_H;
        DrawRectangle(SIDEBAR_W, inputY, WIN_W - SIDEBAR_W, INPUT_H, inputBg);
        DrawLine(SIDEBAR_W, inputY, WIN_W, inputY, borderColor);

        Rectangle cipherBtn = makeRect((float)SIDEBAR_W + 10.0f, (float)inputY + 10.0f, 130.0f, 50.0f);
        DrawRectangleRounded(cipherBtn, 0.3f, 10, WHITE);
        DrawRectangleLinesEx(cipherBtn, 1.0f, borderColor);
        drawText(manager->getCipher(selectedCipher)->getName().c_str(), cipherBtn.x + 10.0f, cipherBtn.y + 15.0f, 18.0f, tealColor);
        drawText("v", cipherBtn.x + 110.0f, cipherBtn.y + 15.0f, 18.0f, tealColor);

        Rectangle inputRect = makeRect(cipherBtn.x + 140.0f, (float)inputY + 10.0f, (float)(WIN_W - SIDEBAR_W - 250), 50.0f);
        DrawRectangleRounded(inputRect, 0.3f, 10, WHITE);
        DrawRectangleLinesEx(inputRect, 1.0f, borderColor);

        if (inputLen == 0)
        {
            drawText("Type a message...", inputRect.x + 15.0f, inputRect.y + 15.0f, 20.0f, lightText);
        }
        else
        {
            drawText(inputBuffer, inputRect.x + 15.0f, inputRect.y + 15.0f, 20.0f, textColor);
            float textW = measureText(inputBuffer, 20.0f);
            if ((int)(GetTime() * 2) % 2 == 0)
            {
                DrawLine((int)(inputRect.x + 15.0f + textW + 2.0f), (int)(inputRect.y + 15.0f), (int)(inputRect.x + 15.0f + textW + 2.0f), (int)(inputRect.y + 35.0f), textColor);
            }
        }

        Rectangle sendBtn = makeRect(inputRect.x + inputRect.width + 10.0f, (float)inputY + 10.0f, 80.0f, 50.0f);
        bool sendHover = CheckCollisionPointRec(GetMousePosition(), sendBtn);
        Color currentSendBtnColor;
        if (sendHover)
        {
            currentSendBtnColor = tealColor;
        }
        else
        {
            currentSendBtnColor = sendBtnColor;
        }
        DrawRectangleRounded(sendBtn, 0.3f, 10, currentSendBtnColor);
        drawText("SEND", sendBtn.x + 15.0f, sendBtn.y + 15.0f, 18.0f, WHITE);
    }

    void drawCipherDropdown()
    {
        if (!cipherDropdownOpen)
        {
            return;
        }

        int inputY = WIN_H - INPUT_H;
        int numCiphers = manager->getCipherCount();
        int dropH = numCiphers * 40;
        Rectangle dropRect = makeRect((float)SIDEBAR_W + 10.0f, (float)inputY - (float)dropH, 150.0f, (float)dropH);

        DrawRectangleRec(dropRect, WHITE);
        DrawRectangleLinesEx(dropRect, 1.0f, borderColor);

        for (int i = 0; i < numCiphers; ++i)
        {
            Rectangle itemRect = makeRect(dropRect.x, dropRect.y + (float)i * 40.0f, dropRect.width, 40.0f);
            if (CheckCollisionPointRec(GetMousePosition(), itemRect))
            {
                DrawRectangleRec(itemRect, selectedBg);
                if (IsMouseButtonPressed(0))
                {
                    selectedCipher = i;
                    cipherDropdownOpen = false;
                }
            }
            drawText(manager->getCipher(i)->getName().c_str(), itemRect.x + 10.0f, itemRect.y + 10.0f, 18.0f, textColor);
        }
    }

    void sendCurrentMessage()
    {
        if (inputLen == 0)
        {
            return;
        }

        Cipher* cipher = manager->getCipher(selectedCipher);
        if (cipher->getName() == "BB84 Quantum")
        {
            BB84Cipher* bb84 = (BB84Cipher*)cipher;
            bb84->setEveActive(eveMode);
        }

        MyString message(inputBuffer);
        MyString encrypted = cipher->encrypt(message);

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

        Message msg(message, encrypted, cipher->getName(), extraInfo);
        chats[activeContact].push_back(msg);
        saveMessage(activeContact, msg);

        inputBuffer[0] = '\0';
        inputLen = 0;

        int totalHeight = getChatHeight(activeContact) + 40;
        int visibleHeight = WIN_H - HEADER_H - INPUT_H;
        int maxScroll = totalHeight - visibleHeight;

        if (maxScroll > 0)
        {
            scrollOffset = maxScroll;
        }
    }

    void handleInput()
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(0) && mouse.x < SIDEBAR_W && mouse.y > HEADER_H)
        {
            int clickedIdx = ((int)mouse.y - HEADER_H) / CONTACT_ITEM_H;
            if (clickedIdx >= 0 && clickedIdx < 3)
            {
                activeContact = clickedIdx;
                cipherDropdownOpen = false;

                int totalHeight = getChatHeight(activeContact) + 40;
                int visibleHeight = WIN_H - HEADER_H - INPUT_H;
                int maxScroll = totalHeight - visibleHeight;

                if (maxScroll > 0)
                {
                    scrollOffset = maxScroll;
                }
                else
                {
                    scrollOffset = 0;
                }
            }
        }

        Rectangle eveBtn = { 700.0f, 15.0f, 140.0f, 30.0f };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, eveBtn))
        {
            eveMode = !eveMode;
        }

        if (activeContact < 0)
        {
            return;
        }

        int inputY = WIN_H - INPUT_H;
        Rectangle cipherBtn = makeRect((float)SIDEBAR_W + 10.0f, (float)inputY + 10.0f, 130.0f, 50.0f);
        if (IsMouseButtonPressed(0))
        {
            if (CheckCollisionPointRec(mouse, cipherBtn))
            {
                cipherDropdownOpen = !cipherDropdownOpen;
            }
            else if (!CheckCollisionPointRec(mouse, makeRect((float)SIDEBAR_W + 10.0f, (float)inputY - ((float)manager->getCipherCount() * 40.0f), 150.0f, (float)(manager->getCipherCount() * 40))))
            {
                cipherDropdownOpen = false;
            }
        }

        Rectangle inputRect = makeRect(cipherBtn.x + 140.0f, (float)inputY + 10.0f, (float)(WIN_W - SIDEBAR_W - 250), 50.0f);
        Rectangle sendBtn = makeRect(inputRect.x + inputRect.width + 10.0f, (float)inputY + 10.0f, 80.0f, 50.0f);

        if (IsMouseButtonPressed(0) && CheckCollisionPointRec(mouse, sendBtn))
        {
            sendCurrentMessage();
        }

        if (!cipherDropdownOpen)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (inputLen < 255))
                {
                    inputBuffer[inputLen] = (char)key;
                    inputBuffer[inputLen + 1] = '\0';
                    inputLen++;
                }
                key = GetCharPressed();
            }

            if (IsKeyDown(KEY_BACKSPACE))
            {
                backspaceTimer++;
                if (backspaceTimer == 1 || (backspaceTimer > 20 && backspaceTimer % 3 == 0))
                {
                    if (inputLen > 0)
                    {
                        inputLen--;
                        inputBuffer[inputLen] = '\0';
                    }
                }
            }
            else
            {
                backspaceTimer = 0;
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                sendCurrentMessage();
            }
        }

        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f)
        {
            int visibleHeight = WIN_H - HEADER_H - INPUT_H;
            int totalHeight = getChatHeight(activeContact) + 40;
            int maxScroll = totalHeight - visibleHeight;

            if (maxScroll < 0) maxScroll = 0;

            scrollOffset -= (int)(wheel * 30.0f);

            if (scrollOffset < 0) scrollOffset = 0;
            if (scrollOffset > maxScroll) scrollOffset = maxScroll;
        }
    }

public:
    MessengerGUI() : activeContact(0), selectedCipher(0), inputLen(0), scrollOffset(0), cipherDropdownOpen(false), backspaceTimer(0), eveMode(false)
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

        inputBuffer[0] = '\0';

        headerColor = makeColor(7, 94, 84, 255);
        sidebarBg = makeColor(255, 255, 255, 255);
        chatBg = makeColor(236, 229, 221, 255);
        bubbleColor = makeColor(220, 248, 198, 255);
        sendBtnColor = makeColor(37, 211, 102, 255);
        tealColor = makeColor(18, 140, 126, 255);
        textColor = makeColor(48, 48, 48, 255);
        lightText = makeColor(150, 150, 150, 255);
        selectedBg = makeColor(240, 240, 240, 255);
        inputBg = makeColor(250, 250, 250, 255);
        borderColor = makeColor(210, 210, 210, 255);

        for (int i = 0; i < 3; ++i)
        {
            loadChat(i);
        }
    }

    ~MessengerGUI()
    {
        delete manager;
    }

    bool init()
    {
        InitWindow(WIN_W, WIN_H, "QCrypt Messenger");
        SetTargetFPS(60);
        mainFont = LoadFontEx("C:\\Windows\\Fonts\\segoeui.ttf", 32, 0, 250);
        if (mainFont.texture.id == 0)
        {
            mainFont = LoadFontEx("C:\\Windows\\Fonts\\arial.ttf", 32, 0, 250);
        }
        return true;
    }

    void run()
    {
        while (!WindowShouldClose())
        {
            handleInput();

            BeginDrawing();
            ClearBackground(chatBg);

            drawSidebar();
            drawChatHeader();
            drawChatMessages();
            drawInputBar();
            drawCipherDropdown();

            EndDrawing();
        }
    }

    void close()
    {
        if (mainFont.texture.id != 0)
        {
            UnloadFont(mainFont);
        }
        CloseWindow();
    }
};

#endif