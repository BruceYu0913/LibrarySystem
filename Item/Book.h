#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

#include "Item.h"

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

  std::string ToCsv() const override;
};

#endif
