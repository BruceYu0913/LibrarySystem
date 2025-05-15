#ifndef BOOK_H
#define BOOK_H

#include "Item.h"
#include <string>
#include <iostream>

class Book : public Item {
protected:
    std::string author;
    std::string isbn;

public:
    Book(int id, const std::string& title, bool isAvailable, int num,
         const std::string& author, const std::string& isbn);

    std::string GetAuthor() const;
    std::string GetIsbn() const;

    void DisplayInfo() const override;
    std::string GetType() const override;
};

#endif
