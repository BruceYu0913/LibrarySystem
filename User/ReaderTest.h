#ifndef READER_TEST_H
#define READER_TEST_H

#include <cassert>
#include <iostream>

#include "../Item/DVD.h"
#include "../Item/EBook.h"
#include "../Item/PrintedBook.h"
#include "Reader.h"

class ReaderTest {
 public:
  void RunTests() {
    TestConstructorAndAccessors();
    TestBorrowItem();
    TestReturnItem();
    TestCanBorrow();
    TestDisplayFunctions();
  }

 private:
  void TestConstructorAndAccessors() {
    cout << "----------[Test] Constructor & Accessors----------" << endl;

    Reader reader(10001, "testuser", "pass123");
    assert(reader.GetId() == 10001);
    assert(reader.GetUsername() == "testuser");
    assert(reader.GetPassword() == "pass123");
    assert(reader.GetUserType() == "reader");
    assert(reader.GetNumberBorrowed() == 0);

    cout << "✅ Constructor & Accessors PASSED." << endl;
  }

  void TestBorrowItem() {
    cout << "----------[Test] BorrowItem----------" << endl;

    Reader reader(10002, "user2", "pass");

    reader.SetBorrowLimit(3);

    PrintedBook pb1(10, "Book One", true, 1, "Author", "ISBN", "Shelf A");
    PrintedBook pb2(11, "Book Two", false, 1, "Author", "ISBN", "Shelf B");

    EBook eb1(20, "EBook1", true, 1, "Author", "ISBN", "xxx.com", 10.22, "PDF",
              time(0));
    EBook eb2(21, "EBook2", false, 1, "Author", "ISBN", "xxx.com", 10.22, "PDF",
              time(0));

    DVD dvd1(30, "DVD1", true, 1, "Director", 120, "mp4", true);
    DVD dvd2(30, "DVD2", false, 1, "Director", 120, "mp4", true);
    DVD dvd3(30, "DVD3", true, 1, "Director", 120, "mp4", true);

    assert(reader.BorrowItem(&pb1) == true);
    assert(reader.BorrowItem(&pb2) == false);

    assert(reader.BorrowItem(&eb1) == true);
    assert(reader.BorrowItem(&eb2) == false);

    assert(reader.BorrowItem(&dvd1) == true);
    assert(reader.BorrowItem(&dvd2) == false);
    assert(reader.BorrowItem(&dvd3) == false);

    assert(reader.GetNumberBorrowed() == 3);

    cout << "✅ BorrowItem PASSED." << endl;
  }

  void TestReturnItem() {
    cout << "----------[Test] ReturnItem----------" << endl;

    Reader reader(3, "user3", "pass");
    PrintedBook book1(20, "Book A", true, 1, "A", "000", "S1");

    assert(reader.BorrowItem(&book1) == true);
    assert(reader.GetNumberBorrowed() == 1);
    assert(reader.ReturnItem(&book1) == true);
    assert(reader.GetNumberBorrowed() == 0);

    PrintedBook book2(21, "Book B", true, 1, "A", "001", "S1");
    assert(reader.ReturnItem(&book2) == false);  // not in borrowed_items

    cout << "✅ ReturnItem PASSED." << endl;
  }

  void TestCanBorrow() {
    cout << "----------[Test] CanBorrow----------" << endl;

    Reader reader(4, "user4", "pw");

    reader.SetBorrowLimit(1);

    PrintedBook book(30, "One", true, 1, "A", "002", "Shelf");

    assert(reader.CanBorrow() == true);
    reader.BorrowItem(&book);
    assert(reader.CanBorrow() == false);

    cout << "✅ CanBorrow PASSED." << endl;
  }

  void TestDisplayFunctions() {
    cout << "----------[Test] Display Functions----------" << endl;

    Reader reader(6, "reader6", "pw");

    PrintedBook pb1(10, "Book One", true, 1, "Author", "ISBN", "Shelf A");
    EBook eb1(20, "EBook1", true, 1, "Author", "ISBN", "xxx.com", 10.22, "PDF",
              time(0));
    DVD dvd1(30, "DVD1", true, 1, "Director", 120, "mp4", true);

    reader.BorrowItem(&pb1);
    reader.BorrowItem(&eb1);
    reader.BorrowItem(&dvd1);

    reader.DisplayInfo();        // user information
    reader.ShowBorrowedItems();  // borrow list

    cout << "✅ Display output printed above." << endl;
  }
};

#endif