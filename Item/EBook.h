#ifndef EBOOK_H
#define EBOOK_H

#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

#include "Book.h"

class EBook : public Book {
 protected:
  std::string download_link;
  float file_size;     // in MB
  std::string format;  // "PDF", "EPUB"
  time_t expiry_date;

 public:
  EBook(int id, const std::string& title, bool isAvailable, int num,
        const std::string& author, const std::string& isbn,
        const std::string& download_link, float file_size,
        const std::string& format, time_t expiry_date);

  std::string GetLink() const;
  std::string GetFormat() const;

  void AutoExpire();  // if current time > expiry_date, let unavailable
  bool CheckExpiry() const;

  void DisplayInfo() const override;
  std::string GetType() const override;

  std::string ToCsv() const override;
};

#endif