#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <vector>

#include "../Item/Item.h"
#include "../TransactionLogger.h"
#include "User.h"

class Admin : public User {
 public:
  Admin(int id, const string& usn, const string& pw);

  void AddItem(vector<Item*>& items, Item* new_item);
  bool DeleteItem(vector<Item*>& items, int item_id);
  bool UpdateItemNum(vector<Item*>& items, int item_id, int new_num);

  void ViewTransaction(const TransactionLogger& logger) const;
  void ExportTransaction(const TransactionLogger& logger,
                         const string& filepath) const;

  void DisplayInfo() const override;
};

#endif