#include "PrintedBook.h"
#include<iostream>
#include<string>
PrintedBook::PrintedBook(int id, const std::string& title, bool isAvailable, int num,
                         const std::string& author, const std::string& isbn,
                         const std::string& shelf_location)
    : Book(id, title, isAvailable, num, author, isbn),
      shelf_location(shelf_location) {}

std::string PrintedBook::GetShelfLocation() const {
    return shelf_location;
}

void PrintedBook::DisplayInfo() const {
    std::cout << "Printed Book ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Shelf Location: " << shelf_location << "\n"
              << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
              << "Quantity: " << num << "\n"
              << "Type: " << GetType() << "\n";
}

std::string PrintedBook::GetType() const {
    return "PrintedBook";
}

std::string PrintedBook::ToCsv() const {
    return this->GetType() + "," + 
           std::to_string(id) + "," + 
           title + "," +
           (isAvailable ? "true" : "false") + "," + 
           std::to_string(num) + "," +
           author + "," +
           isbn + "," +
           shelf_location;
}
