#include "../include/Library.hpp"

int main() {
    LibrarySystem library;
    
    std::cout << "Initializing Library Management System...\n";
    library.loadData("data/books.txt", "data/transactions.txt");
    library.displayMenu();
    
    return 0;
}