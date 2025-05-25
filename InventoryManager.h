#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "./Item/DVD.h"
#include "./Item/EBook.h"
#include "./Item/PrintedBook.h"

using namespace std;

class InventoryManager {
 private:
  string filename;  // path of inventory file

  // read one line from CSV file, one line represent an item
  // instantiate an object based on its type
  Item* LineToItem(const string& line);

  // transform an Item object into one line CSV
  string ItemToLine(const Item* item);

 public:
  InventoryManager(const string& file);

  void LoadInventory(vector<Item*>& items);

  void SaveInventory(const vector<Item*>& items);

  ~InventoryManager();
};

#endif