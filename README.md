# Library Management System (Data Structures)

A robust, terminal-based Library Management System built strictly using foundational Data Structures in C++. This project demonstrates manual memory management and algorithm implementation without relying on the Standard Template Library (STL).

## 📌 Core Architecture
* **Linked List (Book Inventory):** The library's catalog is dynamically managed using a custom Singly Linked List, allowing for efficient, scalable storage of book records.
* **Queue (Waitlist System):** When a book is out of stock, borrowing requests are pushed to a custom FIFO (First-In-First-Out) Queue.
* **Stack (Return History):** Returned books are tracked using a custom LIFO (Last-In-First-Out) Stack, keeping a chronological log of recent returns.

## ⚙️ Features
* **Custom TSV Parsing:** Reads tab-separated values from external text files (`books.txt`, `transactions.txt`) to initialize the system state.
* **Transaction Processing:** Handles borrow and return operations, automatically managing stock levels and routing overflow to the waitlist.
* **Manual Memory Management:** Full implementation of destructors (`~BookLinkedList`, `~BorrowQueue`, `~ReturnStack`) utilizing pointer traversal to ensure zero memory leaks.

## 🛠️ Technologies & Build System
* **Language:** C++ (Standard 17)
* **Architecture:** Object-Oriented Programming (OOP) with custom structs/classes
* **Build System:** CMake
* **Compiler:** GCC (MinGW-w64) / Clang / MSVC

## 🚀 Installation & Build Instructions

### Prerequisites
* CMake (>= 3.10)
* A C++ compiler (GCC, Clang, or MSVC)

### Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/Firatdondar/LibraryManagementSystem.git
   cd LibraryManagementSystem
   ```
2. Configure and build using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. Run the application:
   ```bash
   ./LibraryManagementSystem
   ```
