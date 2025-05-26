#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

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
  void ShowLoginMenu();

  void AdminMenu(Admin* admin);
  void ReaderMenu(Reader* reader);
};

#endif
