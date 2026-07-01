# QCrypt Messenger 🔐

> A complete Classical & Quantum Cryptography Engine paired with a WhatsApp-style graphical interface. 

QCrypt Messenger is a C++ application designed to encrypt and decrypt messages in real-time using six distinct cryptographic algorithms. Built entirely from scratch for an Object-Oriented Programming course, this project avoids standard C++ containers and relies heavily on custom dynamic memory management and advanced OOP architecture.

## ✨ Key Features
* **Graphical User Interface:** A smooth, WhatsApp-style messenger interface built using the **Raylib** library.
* **Real-time Encryption:** Type a message, select a cipher from the dropdown, and see the encrypted output instantly in a chat bubble.
* **Persistent Chat History:** Messages are automatically saved to and loaded from local `.txt` files.
* **Custom Memory Management:** **Zero** standard library containers (`std::string` or `std::vector`) were used. The project relies entirely on custom-built `MyString` and `MyVector<T>` template classes managing raw dynamic memory on the heap.

## 🧮 Implemented Ciphers
The engine features a highly polymorphic architecture where every algorithm inherits from a base `Cipher` class:
1. **Caesar Cipher:** Basic shift substitution.
2. **ROT13 Cipher:** Self-inverse shift substitution.
3. **Vigenère Cipher:** Polyalphabetic substitution using a keyword and tabula recta lookup.
4. **XOR Cipher:** Bitwise manipulation using a secret byte key.
5. **RSA-style Cipher:** Asymmetric cryptography implementing real modular exponentiation, prime generation, and public/private key pairs.
6. **BB84 Quantum Protocol:** A simulated quantum key distribution (QKD) layer featuring photon polarization, random basis selection, basis reconciliation, and eavesdrop (Eve) detection.

## 🏗️ OOP Architecture Highlights
The backend is structured to demonstrate rigorous Object-Oriented Programming principles:
* **Runtime Polymorphism:** A `CryptoManager` stores an array of abstract `Cipher*` pointers, dispatching `encrypt()` and `decrypt()` calls at runtime without knowing the derived class type.
* **Inheritance:** Features single, multi-level (e.g., `BB84Cipher` → `QuantumCipher` → `Cipher`), and hierarchical inheritance.
* **Encapsulation:** Internal cipher keys, UI states, and contact data are strictly protected, exposing only narrow APIs.

## 🛠️ Build Requirements
To compile and run this project, you will need:
* A C++ compiler (e.g., MinGW/GCC)
* The **Raylib** graphics library (linked with `-lraylib -lgdi32 -lwinmm -lopengl32`)
* A `Makefile` is used to build the project from `main.cpp`.

---
*Developed by M. AbuBakar (BSCS25109)*
