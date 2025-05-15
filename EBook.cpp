#include "EBook.h"

EBook::EBook(int id, const std::string& title, bool isAvailable, int num,
             const std::string& author, const std::string& isbn,
             const std::string& download_link, float file_size,
             const std::string& format, time_t expiry_date)
    : Book(id, title, isAvailable, num, author, isbn),
      download_link(download_link), file_size(file_size),
      format(format), expiry_date(expiry_date) {}

std::string EBook::GetLink() const {
    return download_link;
}

std::string EBook::GetFormat() const {
    return format;
}

bool EBook::CheckExpiry() const {
    time_t now = time(nullptr);
    return now > expiry_date;
}

void EBook::AutoExpire() {
    if (CheckExpiry()) {
        isAvailable = false;
    }
}

void EBook::DisplayInfo() const {
    std::cout << "EBook ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Download Link: " << download_link << "\n"
              << "File Size: " << file_size << " MB\n"
              << "Format: " << format << "\n"
              << "Expiry: " << ctime(&expiry_date) // prints readable date
              << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
              << "Quantity: " << num << "\n"
              << "Type: " << GetType() << "\n";
}

std::string EBook::GetType() const {
    return "EBook";
}


