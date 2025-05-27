#ifndef TRANSACTION_LOGGER_H
#define TRANSACTION_LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../Item/Item.h"
#include "../User/Reader.h"

using namespace std;

class TransactionLogger {
 private:
  string log_file_name;

  string GetCurrentTime() const;

 public:
  TransactionLogger(const string& fname);

  ~TransactionLogger();

  void LogBorrow(const Reader* reader, const Item* item);
  void LogReturn(const Reader* reader, const Item* item);

  void PrintAll() const;
  void ExportToFile(const string& outPath) const;
};

#endif