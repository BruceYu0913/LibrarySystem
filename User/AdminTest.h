#ifndef ADMIN_TEST_H
#define ADMIN_TEST_H

#include <cassert>
#include <iostream>

#include "../Item/DVD.h"
#include "../Item/EBook.h"
#include "../Item/PrintedBook.h"
#include "../TransactionLogger.h"
#include "Admin.h"

class AdminTest {
 public:
  void RunTests() {
    TestAddItem();
    TestDeleteItem();
    TestUpdateItemQuantity();
    TestTransactionLogging();
    TestDisplay();
  }

 private:
  void TestAddItem() {
    cout << "----------[Test] AddItem----------\n";

    Admin admin(1, "admin", "pw");
    vector<Item*> items;

    PrintedBook pb1(10, "Book One", true, 1, "Author", "ISBN", "Shelf A");
    EBook eb1(20, "EBook1", true, 1, "Author", "ISBN", "xxx.com", 10.22, "PDF",
              time(0));
    DVD dvd1(30, "DVD1", true, 1, "Director", 120, "mp4", true);

    admin.AddItem(items, &pb1);
    admin.AddItem(items, &eb1);
    admin.AddItem(items, &dvd1);

    assert(items.size() == 3);
    assert(items[0]->GetTitle() == "Book One");
    assert(items[1]->GetTitle() == "EBook1");
    assert(items[2]->GetTitle() == "DVD1");

    cout << "✅ AddItem PASSED.\n";
  }

  void TestDeleteItem() {
    cout << "----------[Test] DeleteItem----------\n";

    Admin admin(2, "admin2", "pw");
    vector<Item*> items;

    PrintedBook pb1(10, "Book One", true, 1, "Author", "ISBN", "Shelf A");
    EBook eb1(20, "EBook1", true, 1, "Author", "ISBN", "xxx.com", 10.22, "PDF",
              time(0));
    DVD dvd1(30, "DVD1", true, 1, "Director", 120, "mp4", true);

    items.push_back(&pb1);
    items.push_back(&eb1);
    items.push_back(&dvd1);

    assert(admin.DeleteItem(items, 10) == true);
    assert(items.size() == 2);
    assert(items[0]->GetId() == 20);
    assert(items[1]->GetId() == 30);

    cout << "✅ DeleteItem PASSED.\n";
  }

  void TestUpdateItemQuantity() {
    cout << "----------[Test] UpdateItemQuantity----------\n";

    Admin admin(3, "admin3", "pw");
    vector<Item*> items;

    Item* book =
        new PrintedBook(1004, "Target Book", true, 5, "X", "003", "S2");
    items.push_back(book);

    assert(admin.UpdateItemNum(items, 1004, 0) == true);
    assert(book->GetNum() == 0);
    assert(book->GetAvailable() == false);

    assert(admin.UpdateItemNum(items, 1004, 4) == true);
    assert(book->GetNum() == 4);
    assert(book->GetAvailable() == true);

    std::cout << "✅ UpdateItemQuantity PASSED.\n";
  }

  void TestTransactionLogging() {
    cout << "----------[Test] ViewTransaction & ExportTransaction----------\n";

    Admin admin(4, "admin4", "pw");
    TransactionLogger logger("admin_test_log.csv");

    // add some data to csv
    Reader reader(10, "TestReader", "pw");
    PrintedBook book(5001, "Log Book", true, 1, "Auth", "ISBN", "Loc");

    logger.LogBorrow(&reader, &book);
    logger.LogReturn(&reader, &book);

    // check the log
    admin.ViewTransaction(logger);

    // export log
    string export_path = "admin_test_exported_log.csv";
    admin.ExportTransaction(logger, export_path);

    ifstream f(export_path);
    assert(f.is_open());
    int lines = 0;
    string line;
    while (getline(f, line)) {
      ++lines;
    }
    f.close();

    assert(lines >= 2);  // at least 2 lines data
    cout << "✅ ViewTransaction & ExportTransaction PASSED.\n";
  }

  void TestDisplay() {
    cout << "----------[Test] Display----------\n";

    Admin admin1(111, "test name", "pass");
    admin1.DisplayInfo();
  }
};

#endif