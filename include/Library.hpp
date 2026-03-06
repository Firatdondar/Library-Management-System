#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

struct Book {
    int id;
    std::string title;
    std::string author;
    int stock;
    Book(int id = 0, std::string t = "", std::string a = "", int s = 0) : id(id), title(t), author(a), stock(s) {}
};

struct Transaction {
    int studentId;
    std::string studentName;
    int bookId;
    int operation; // 1: Borrow, 0: Return

    Transaction(int sId = 0, std::string name = "", int bId = 0, int op = -1) 
        : studentId(sId), studentName(name), bookId(bId), operation(op) {}
};

struct BookNode {
    Book data;
    BookNode* next;
    BookNode(Book b) : data(b), next(nullptr) {}
};

struct QueueNode {
    Transaction data;
    QueueNode* next;
    QueueNode(Transaction t) : data(t), next(nullptr) {}
};

struct StackNode {
    Transaction data;
    StackNode* next;
    StackNode(Transaction t) : data(t), next(nullptr) {}
};

class BookLinkedList {
private:
    BookNode* head;
public:
    BookLinkedList() : head(nullptr) {}
    ~BookLinkedList();
    void addBook(Book newBook);
    void listBooks() const;
    Book* searchBook(int bookId);
};

class BorrowQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    BorrowQueue() : front(nullptr), rear(nullptr) {}
    ~BorrowQueue();
    void enqueue(Transaction t);
    Transaction dequeue();
    Transaction peek() const;
    bool isEmpty() const;
    void listQueue() const;
};

class ReturnStack {
private:
    StackNode* top;
public:
    ReturnStack() : top(nullptr) {}
    ~ReturnStack();
    void push(Transaction t);
    Transaction pop();
    bool isEmpty() const;
    void listStack() const;
};

class LibrarySystem {
private:
    BookLinkedList bookList;
    BorrowQueue borrowQueue;
    ReturnStack returnStack;

    Book parseBookLine(const std::string& line);
    Transaction parseTransactionLine(const std::string& line);
    void borrowBook(Transaction t, bool silent = false);
    void returnBook(Transaction t, bool silent = false);
    void manualBorrow();
    void manualReturn();
    int safeIntegerInput();

public:
    void loadData(const std::string& bookFile, const std::string& transactionFile);
    void displayMenu();
    void processSelection(int choice);
};

#endif