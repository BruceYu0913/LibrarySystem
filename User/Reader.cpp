#include "Reader.h"

Reader::Reader(int id, const string& usn, const string& psw)
    : User(id, usn, psw, "reader"), borrow_limit(5) {}

bool Reader::BorrowItem(Item* item) {
  // item not available
  if (!item || !item->GetAvailable()) return false;
  // reader cannot borrow anymore
  if ((int)borrowed_items.size() >= borrow_limit) return false;

  borrowed_items.push_back(item);
  return true;
}

bool Reader::ReturnItem(Item* item) {
  for (auto it = borrowed_items.begin(); it != borrowed_items.end(); ++it) {
    if (*it == item) {
      borrowed_items.erase(it);
      return true;
    }
  }
  return false;
}

void Reader::ShowBorrowedItems() const {
  cout << "Borrowed Items by " << username << endl;
  for (const auto& item : borrowed_items) {
    cout << "- " << item->GetTitle() << " (ID: " << item->GetId() << endl;
  }
}

bool Reader::CanBorrow() const {
  return (int)borrowed_items.size() < borrow_limit;
}

vector<Item*> Reader::GetBorrowedItems() const { return borrowed_items; }

int Reader::GetNumberBorrowed() const { return borrowed_items.size(); }

void Reader::SetBorrowLimit(int limit) {
  if (limit >= 0) {
    borrow_limit = limit;
  }
}

void Reader::DisplayInfo() const {
  cout << "[Reader] Username: " << username << " | ID: " << id
       << " | Borrowed: " << borrowed_items.size() << " / " << borrow_limit
       << endl;
}