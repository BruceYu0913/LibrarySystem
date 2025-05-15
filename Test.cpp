#include <iostream>
#include "Book.h"
#include "PrintedBook.h"
#include "EBook.h"
#include "DVD.h"

void testBook() {
    Book b(100001, "tongtongtongsahur", true, 4, "jonathan", "9781234567890");
    std::cout << "Book Test:\n";
    std::cout << b.GetId() << "\n";
    std::cout << b.GetTitle() << "\n";
    std::cout << b.GetAuthor() << "\n";
    std::cout << b.GetIsbn() << "\n";
    std::cout << b.GetType() << "\n";
    b.DisplayInfo();
    std::cout << "\n";
}

void testPrintedBook() {
    PrintedBook p(100002, "telalalero Telala", true, 2, "mina park", "9789876543210", "Shelf B2");
    std::cout << "PrintedBook Test:\n";
    std::cout << p.GetId() << "\n";
    std::cout << p.GetTitle() << "\n";
    std::cout << p.GetAuthor() << "\n";
    std::cout << p.GetIsbn() << "\n";
    std::cout << p.GetShelfLocation() << "\n";
    std::cout << p.GetType() << "\n";
    p.DisplayInfo();
    std::cout << "\n";
}

void testEBook() {
    time_t future = time(nullptr) + 3600;
    EBook e(100003, "Digital Fortress", true, 1, "Dan Brown", "9780312944926",
            "http://example.com", 2.5, "EPUB", future);

    std::cout << "EBook Test:\n";
    std::cout << e.GetId() << "\n";
    std::cout << e.GetTitle() << "\n";
    std::cout << e.GetLink() << "\n";
    std::cout << e.GetFormat() << "\n";
    std::cout << (e.CheckExpiry() ? "Expired" : "Valid") << "\n";
    e.AutoExpire();
    std::cout << (e.GetAvailable() ? "Yes" : "No") << "\n";
    e.DisplayInfo();
    std::cout << "\n";
}

void testDVD() {
    DVD d(200001, "Inception", true, 5, "Christopher Nolan", 148, "BluRay", true);
    std::cout << "DVD Test:\n";
    std::cout << d.GetId() << "\n";
    std::cout << d.GetTitle() << "\n";
    std::cout << d.GetDirector() << "\n";
    std::cout << d.GetDuration() << "\n";
    std::cout << d.GetMediaType() << "\n";
    std::cout << (d.CheckPlayable() ? "Playable" : "Not Playable") << "\n";
    d.Play();
    d.DisplayInfo();
    std::cout << "\n";
}

int main() {
    testBook();
    testPrintedBook();
    testEBook();
    testDVD();
    return 0;
}

