#include<iostream>
#include<string>
#include"Item.h"
#include"Book.h"

Book::Book(int id, const std::string& title, bool isAvailable, int num,
           const std::string& author, const std::string& isbn)
    : Item(id, title, isAvailable, num), author(author), isbn(isbn) {}

std::string Book::GetAuthor() const {
    return author;
}

std::string Book::GetIsbn() const {
    return isbn;
}

void Book::DisplayInfo() const {
    std::cout << "Book ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
              << "Quantity: " << num << "\n"
              << "Type: " << GetType() << "\n";
}

std::string Book::GetType() const {
    return "Book";
}


