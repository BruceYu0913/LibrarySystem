#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "./Item/Book.h"
#include "./Item/DVD.h"
#include "./Item/EBook.h"
#include "./Item/Item.h"
#include "./Item/PrintedBook.h"
#include "./User/Admin.h"
#include "./User/Reader.h"
#include "./User/User.h"
#include "InventoryManager.h"
#include "Search.h"
#include "TransactionLogger.h"

using namespace std;

class LibrarySystem {
 private:
  // program status
  bool running = true;

  // main data
  vector<Item*> items;
  vector<User*> users;

  // next ID counters for each item type (start from 8-digit base)
  // prefix 11-PrintedBook
  // prefix 12-EBook
  // prefix 21-DVD
  int next_pbk_id = 11000001;
  int next_ebk_id = 12000001;
  int next_dvd_id = 21000001;

  // file paths
  const string inventory_file_path = "./DataFiles/inventory.csv";
  const string user_file_path = "./DataFiles/users.csv";
  const string log_file_path = "./DataFiles/logs.csv";

  // managers
  InventoryManager inventory_manager;
  TransactionLogger logger;

 public:
  LibrarySystem();   // constructor
  ~LibrarySystem();  // destructor

  void Run();  // the main function to run the program

 private:
  void LoadUsers();  // load user info from CSV
  User* Authenticate(const string& username, const string& password,
                     const string& role);
  void LoadBorrowedRecords();
  void SaveBorrowedRecords();
  void InitNextIdsFromItems();

  void ShowLoginMenu();
  void AdminMenu(Admin* admin);
  void ReaderMenu(Reader* reader);
};

#endif
