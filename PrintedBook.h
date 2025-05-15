#ifndef PRINTEDBOOK_H
#define PRINTEDBOOK_H

#include "Book.h"
#include <string>
#include <iostream>

class PrintedBook : public Book {
protected:
    std::string shelf_location;

public:
    PrintedBook(int id, const std::string& title, bool isAvailable, int num,
                const std::string& author, const std::string& isbn,
                const std::string& shelf_location);

    std::string GetShelfLocation() const;

    void DisplayInfo() const override;
    std::string GetType() const override;
};

#endif
