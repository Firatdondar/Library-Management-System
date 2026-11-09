# 📚 Library Management System (Custom Data Structures)

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-064F8C?logo=cmake&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Linked%20List%20%7C%20Queue%20%7C%20Stack-blueviolet)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

A terminal-based **Library Management System** implemented in **C++17** using custom, from-scratch data structures (**Singly Linked List**, **FIFO Queue**, and **LIFO Stack**) with strict manual memory management and zero STL container dependencies.

---

## 🏗️ Data Structure Architecture

| Component | Custom Data Structure | Operational Role | Complexity |
| :--- | :--- | :--- | :--- |
| **Book Catalog** | `BookLinkedList` (Singly Linked List) | Dynamic storage, lookup, and stock tracking of library inventory | $O(N)$ lookup, $O(1)$ head insert |
| **Reservation Waitlist** | `BorrowQueue` (FIFO Queue) | Queues borrower requests when a requested title has zero available copies | $O(1)$ enqueue / dequeue |
| **Return Audit Log** | `ReturnStack` (LIFO Stack) | Maintains a reverse-chronological history of returned books | $O(1)$ push / pop |

---

## ✨ Key Features

- **Automated Waitlist Fulfillment:** When an out-of-stock book is returned, the system automatically dequeues the next waiting patron from `BorrowQueue` and assigns the copy.
- **Custom Tab-Separated Parser:** Initializes book inventory (`data/books.txt`) and executes batch borrow/return transactions (`data/transactions.txt`).
- **Leak-Free RAII Destructors:** Explicit node traversal destructors (`~BookLinkedList`, `~BorrowQueue`, `~ReturnStack`) ensure complete heap deallocation.

---

## 🗂️ Project Structure

```text
Library-Management-System/
├── data/
│   ├── books.txt            # Initial book catalog (ID, Title, Author, Stock)
│   └── transactions.txt     # Batch borrow/return transaction log
├── include/
│   └── Library.hpp          # Linked List, Queue, and Stack class declarations
├── src/
│   ├── Library.cpp          # Core data structure & transaction implementations
│   └── main.cpp             # Application entry point
├── CMakeLists.txt           # Cross-platform CMake build configuration
├── LICENSE                  # MIT License
└── README.md                # Project documentation
```

---

## 🚀 Build & Run Instructions

```bash
git clone https://github.com/Firatdondar/Library-Management-System.git
cd Library-Management-System
mkdir build && cd build
cmake ..
cmake --build .
./LibraryManagementSystem
```

---

## 📄 License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.
