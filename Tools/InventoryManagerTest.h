#ifndef INVENTORY_MANAGER_TEST_H
#define INVENTORY_MANAGER_TEST_H

#include "InventoryManager.h"

class InventoryManagerTest {
 public:
  void RunTests() {
    TestLoadInventory();
    TestSaveInventory();
  }

 private:
  void TestLoadInventory() {
    cout << "----------Running TestLoadInventory----------" << endl;

    InventoryManager manager("test_inventory.csv");
    vector<Item*> items;
    manager.LoadInventory(items);

    for (auto* item : items) {
      string line;
      line = item->ToCsv();
      cout << line << endl;
    }

    cout << "✅ TestLoadInventory completed (compare with 'inventory.csv')."
         << endl;

    for (auto* item : items) delete item;
  }

  void TestSaveInventory() {
    cout << "----------Running testSaveInventory----------" << endl;

    InventoryManager manager("test_inventory_output.csv");
    vector<Item*> items;

    items.push_back(new PrintedBook(110008, "Test Book1", true, 2,
                                    "Test Author1", "0000000000", "Shelf X"));

    items.push_back(new EBook(120008, "Test Book2", true, 1, "Test Author2",
                              "0000000001", "xxx.com", 30.2, "PDF", time(0)));

    items.push_back(new DVD(210008, "Test DVD1", true, 3, "Test Director1", 123,
                            "mp4", true));

    manager.SaveInventory(items);

    cout << "✅ TestSaveInventory completed (check 'test_output.csv').\n";

    for (auto* item : items) delete item;
  }
};

#endif