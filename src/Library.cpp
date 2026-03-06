#include "../include/Library.hpp"

// --- BookLinkedList Implementation ---
BookLinkedList::~BookLinkedList() {
    BookNode* current = head;
    while (current != nullptr) {
        BookNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void BookLinkedList::addBook(Book newBook) {
    BookNode* newNode = new BookNode(newBook);
    if (!head) {
        head = newNode;
    } else {
        BookNode* current = head;
        while (current->next) current = current->next;
        current->next = newNode;
    }
}

void BookLinkedList::listBooks() const {
    if (!head) {
        std::cout << "Library is currently empty.\n";
        return;
    }
    std::cout << "\n--- Available Books ---\n";
    std::cout << "ID    | Title                | Author               | Stock\n";
    std::cout << "------|----------------------|----------------------|------\n";
    BookNode* current = head;
    while (current) {
        std::cout.width(5); std::cout << std::left << current->data.id << " | ";
        std::cout.width(20); std::cout << std::left << current->data.title << " | ";
        std::cout.width(20); std::cout << std::left << current->data.author << " | ";
        std::cout << current->data.stock << "\n";
        current = current->next;
    }
    std::cout << "-----------------------------------------------------------\n";
}

Book* BookLinkedList::searchBook(int bookId) {
    BookNode* current = head;
    while (current) {
        if (current->data.id == bookId) return &(current->data);
        current = current->next;
    }
    return nullptr;
}

// --- BorrowQueue Implementation ---
BorrowQueue::~BorrowQueue() {
    while (!isEmpty()) dequeue();
}

void BorrowQueue::enqueue(Transaction t) {
    QueueNode* newNode = new QueueNode(t);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

Transaction BorrowQueue::dequeue() {
    if (isEmpty()) return Transaction(-1, "Error", -1, -1);
    QueueNode* temp = front;
    Transaction data = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return data;
}

Transaction BorrowQueue::peek() const {
    if (isEmpty()) return Transaction(-1, "Error", -1, -1);
    return front->data;
}

bool BorrowQueue::isEmpty() const { return front == nullptr; }

void BorrowQueue::listQueue() const {
    if (isEmpty()) {
        std::cout << "Borrow queue is empty.\n";
        return;
    }
    std::cout << "\n--- Pending Borrow Requests (Queue) ---\n";
    QueueNode* current = front;
    while (current) {
        std::cout << "Student ID: " << current->data.studentId
                  << " | Name: " << current->data.studentName
                  << " | Book ID: " << current->data.bookId << "\n";
        current = current->next;
    }
    std::cout << "---------------------------------------\n";
}

// --- ReturnStack Implementation ---
ReturnStack::~ReturnStack() {
    while (!isEmpty()) pop();
}

void ReturnStack::push(Transaction t) {
    StackNode* newNode = new StackNode(t);
    newNode->next = top;
    top = newNode;
}

Transaction ReturnStack::pop() {
    if (isEmpty()) return Transaction(-1, "Error", -1, -1);
    StackNode* temp = top;
    Transaction data = temp->data;
    top = top->next;
    delete temp;
    return data;
}

bool ReturnStack::isEmpty() const { return top == nullptr; }

void ReturnStack::listStack() const {
    if (isEmpty()) {
        std::cout << "Return stack is empty.\n";
        return;
    }
    std::cout << "\n--- Recently Returned Books (Stack) ---\n";
    StackNode* current = top;
    while (current) {
        std::cout << "Student ID: " << current->data.studentId
                  << " | Name: " << current->data.studentName
                  << " | Book ID: " << current->data.bookId << "\n";
        current = current->next;
    }
    std::cout << "---------------------------------------\n";
}

// --- LibrarySystem Implementation ---
Book LibrarySystem::parseBookLine(const std::string& line) {
    std::stringstream ss(line);
    std::string segment;
    Book tempBook;
    try {
        std::getline(ss, segment, '\t');
        if (!segment.empty()) tempBook.id = std::stoi(segment); else return Book(0);
        std::getline(ss, segment, '\t'); tempBook.title = segment;
        std::getline(ss, segment, '\t'); tempBook.author = segment;
        std::getline(ss, segment, '\t');
        if (!segment.empty()) tempBook.stock = std::stoi(segment); else tempBook.stock = 0;
    } catch (...) { return Book(0); }
    return tempBook;
}

Transaction LibrarySystem::parseTransactionLine(const std::string& line) {
    std::stringstream ss(line);
    std::string segment;
    Transaction tempT;
    try {
        std::getline(ss, segment, '\t');
        if (!segment.empty()) tempT.studentId = std::stoi(segment); else return Transaction(-1);
        std::getline(ss, segment, '\t'); tempT.studentName = segment;
        std::getline(ss, segment, '\t');
        if (!segment.empty()) tempT.bookId = std::stoi(segment); else tempT.bookId = -1;
        std::getline(ss, segment, '\t');
        if (!segment.empty()) tempT.operation = std::stoi(segment); else tempT.operation = -1;
    } catch (...) { return Transaction(-1); }
    return tempT;
}

void LibrarySystem::loadData(const std::string& bookFile, const std::string& transactionFile) {
    std::ifstream fileB(bookFile);
    std::string line;
    if (fileB.is_open()) {
        std::getline(fileB, line); // header
        while (std::getline(fileB, line)) {
            Book b = parseBookLine(line);
            if (b.id != 0) bookList.addBook(b);
        }
        fileB.close();
    } else { std::cerr << "ERR: Cannot open " << bookFile << "\n"; }

    std::ifstream fileT(transactionFile);
    if (fileT.is_open()) {
        std::getline(fileT, line); // header
        while (std::getline(fileT, line)) {
            Transaction t = parseTransactionLine(line);
            if (t.studentId != -1 && t.bookId != -1 && (t.operation == 0 || t.operation == 1)) {
                if (t.operation == 1) borrowBook(t, true);
                else returnBook(t, true);
            }
        }
        fileT.close();
    } else { std::cerr << "ERR: Cannot open " << transactionFile << "\n"; }
}

void LibrarySystem::borrowBook(Transaction t, bool silent) {
    Book* b = bookList.searchBook(t.bookId);
    if (!b) {
        if (!silent) std::cout << " > Book ID " << t.bookId << " not found.\n";
    } else {
        if (b->stock > 0) {
            b->stock--;
            if (!silent) std::cout << " > '" << b->title << "' borrowed successfully. Remaining stock: " << b->stock << "\n";
        } else {
            if (!silent) std::cout << " > '" << b->title << "' is out of stock. Request added to queue.\n";
            borrowQueue.enqueue(t);
        }
    }
}

void LibrarySystem::returnBook(Transaction t, bool silent) {
    Book* b = bookList.searchBook(t.bookId);
    if (!b) {
        if (!silent) std::cout << " > Book ID " << t.bookId << " not found.\n";
    } else {
        b->stock++;
        if (!silent) std::cout << " > '" << b->title << "' returned. Stock updated to: " << b->stock << "\n";
        returnStack.push(t);

        if (!silent && !borrowQueue.isEmpty()) {
            if (borrowQueue.peek().bookId == b->id) {
                std::cout << " > Notice: There is a pending request for this book in the queue.\n";
            }
        }
    }
}

int LibrarySystem::safeIntegerInput() {
    int value;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void LibrarySystem::manualBorrow() {
    std::cout << "Enter Student ID: "; int sId = safeIntegerInput();
    std::cout << "Enter Book ID: "; int bId = safeIntegerInput();
    borrowBook(Transaction(sId, "Manual Entry", bId, 1), false);
}

void LibrarySystem::manualReturn() {
    std::cout << "Enter Student ID: "; int sId = safeIntegerInput();
    std::cout << "Enter Book ID: "; int bId = safeIntegerInput();
    returnBook(Transaction(sId, "Manual Entry", bId, 0), false);
}

void LibrarySystem::processSelection(int choice) {
    switch (choice) {
        case 1: bookList.listBooks(); break;
        case 2: borrowQueue.listQueue(); break;
        case 3: returnStack.listStack(); break;
        case 4: manualBorrow(); break;
        case 5: manualReturn(); break;
        case 0: std::cout << "Shutting down system...\n"; break;
        default: std::cout << "Invalid selection.\n"; break;
    }
}

void LibrarySystem::displayMenu() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Library Management Console ===\n";
        std::cout << "1. List All Books (Linked List)\n";
        std::cout << "2. View Borrow Queue (Queue)\n";
        std::cout << "3. View Return History (Stack)\n";
        std::cout << "4. Manual Book Issue\n";
        std::cout << "5. Manual Book Return\n";
        std::cout << "0. Exit\n";
        std::cout << "Select operation: ";
        choice = safeIntegerInput();
        processSelection(choice);
    }
}