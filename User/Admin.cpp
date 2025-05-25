#include "Admin.h"

Admin::Admin(int id, const string& usn, const string& pw)
    : User(id, usn, pw, "admin") {}

void Admin::AddItem(vector<Item*>& items, Item* new_item) {
  if (new_item) {
    items.push_back(new_item);
    cout << "✅ Item added: " << new_item->GetTitle() << endl;
  }
}

bool Admin::DeleteItem(vector<Item*>& items, int item_id) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if ((*it)->GetId() == item_id) {
      cout << "✅ Deleting item: " << (*it)->GetTitle() << endl;
      items.erase(it);
      return true;
    }
  }

  cout << "❌ Item ID not found.\n";
  return false;
}

bool Admin::UpdateItemNum(vector<Item*>& items, int item_id, int new_num) {
  for (auto& item : items) {
    if (item->GetId() == item_id) {
      item->SetNum(new_num);

      if (new_num > 0) {
        item->SetAvailable(true);
      } else {
        item->SetAvailable(false);
      }

      cout << "✅ Quantity updated: " << item->GetTitle()
           << " | New Quantity: " << new_num << endl;
      return true;
    }
  }

  cout << "❌ Item ID not found.\n";
  return false;
}

void Admin::ViewTransaction(const TransactionLogger& logger) const {
  logger.PrintAll();
}

void Admin::ExportTransaction(const TransactionLogger& logger,
                              const string& filepath) const {
  logger.ExportToFile(filepath);
}

void Admin::DisplayInfo() const {
  cout << "[Admin] Username: " << username << " | ID: " << id << endl;
}