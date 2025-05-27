#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

#include "../Item/Item.h"
#include "User.h"

class Reader : public User {
 private:
  vector<Item*> borrowed_items;
  int borrow_limit;  // default 5

 public:
  Reader(int id, const string& usn, const string& psw);

  bool BorrowItem(Item* item);
  bool ReturnItem(Item* item);
  void ShowBorrowedItems() const;
  bool CanBorrow() const;
  vector<Item*> GetBorrowedItems() const;
  int GetNumberBorrowed() const;
  void SetBorrowLimit(int limit);
  void DisplayInfo() const override;
};

#endif