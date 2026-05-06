# Anonymous Multithreaded Chat System 🚀

A high-performance, real-time chat application built using **C++16** and **WinSock2**. This project demonstrates the implementation of a server-client architecture capable of handling multiple connections simultaneously using multithreading.

## 🌟 Features
* **Asynchronous Communication:** Uses `std::thread` to handle sending and receiving messages without blocking the UI.
* **Socket Programming:** Built on top of Windows Sockets (WSA) for reliable local/network communication.
* **Anonymous Identity:** Simple, clean console-based UI where users are identified as "Anonymous".
* **Modern C++:** Compiled using GCC 16.1 (UCRT64) with the latest standards.

## 🛠️ Built With
* [C++](https://isocpp.org/) - Programming Language
* [MSYS2](https://www.msys2.org/) - Software Distribution and Building Platform
* [MinGW-w64](https://www.mingw-w64.org/) - GCC for Windows

## 🚀 Getting Started

### Prerequisites
* Windows OS
* GCC/G++ Compiler (Version 13+ recommended)

### Compilation
To compile the server and client files, run the following commands in your terminal:

```bash
# Compile Server
g++ server.cpp -o server.exe -lws2_32

# Compile Client
g++ client.cpp -o client.exe -lws2_32
