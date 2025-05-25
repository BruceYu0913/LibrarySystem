#ifndef TRANSACTION_LOGGER_TEST_H
#define TRANSACTION_LOGGER_TEST_H

#include <cassert>

#include "./Item/DVD.h"
#include "./Item/EBook.h"
#include "./Item/PrintedBook.h"
#include "./User/Reader.h"
#include "TransactionLogger.h"

class TransactionLoggerTest {
 public:
  void RunTests() {
    TestLogBorrowAndReturn();
    TestPrintAll();
    TestExportToFile();
  }

 private:
  void TestLogBorrowAndReturn() {
    cout << "----------[Test] LogBorrow & LogReturn----------\n";

    TransactionLogger logger("test_transactions.csv");

    Reader reader(101, "TestUser", "pw");

    PrintedBook pb1(10, "Book One", true, 1, "Author", "ISBN", "Shelf A");
    EBook eb1(20, "EBook1", true, 1, "Author", "ISBN", "xxx.com", 10.22, "PDF",
              time(0));
    DVD dvd1(30, "DVD1", true, 1, "Director", 120, "mp4", true);

    logger.LogBorrow(&reader, &pb1);
    logger.LogReturn(&reader, &pb1);

    logger.LogBorrow(&reader, &eb1);
    logger.LogReturn(&reader, &eb1);

    logger.LogBorrow(&reader, &dvd1);
    logger.LogReturn(&reader, &dvd1);

    ifstream file("test_transactions.csv");
    assert(file.is_open());

    string line;
    int count = 0;
    while (std::getline(file, line)) {
      ++count;
      cout << line << endl;
    }
    file.close();

    assert(count >= 6);  // at least 6 logs
    cout << "✅ LogBorrow & LogReturn PASSED.\n";
  }

  void TestPrintAll() {
    std::cout << "----------[Test] PrintAll----------\n";
    TransactionLogger logger("test_transactions.csv");
    logger.PrintAll();
  }

  void TestExportToFile() {
    cout << "----------[Test] ExportToFile----------\n";

    TransactionLogger logger("test_transactions.csv");
    string log_file_copy = "test_transactions_copy.csv";
    logger.ExportToFile(log_file_copy);

    ifstream check_file(log_file_copy);
    assert(check_file.is_open());

    int line_count = 0;
    string line;
    while (getline(check_file, line)) {
      ++line_count;
    }
    check_file.close();

    assert(line_count >= 6);
    cout << "✅ ExportToFile PASSED.\n";
  }
};

#endif