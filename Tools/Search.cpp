#include "Search.h"

vector<Item*> Search::SearchByID(const vector<Item*>& items, int id) {
  // initialize
  vector<Item*> results;

  for (Item* item : items) {
    // match id
    if (item->GetId() == id) {
      results.push_back(item);
      break;
    }
  }

  return results;
}

vector<Item*> Search::SearchByTitle(const vector<Item*>& items,
                                    const string& title) {
  // initialize
  vector<Item*> results;

  for (Item* item : items) {
    // match title
    if (item->GetTitle().find(title) != string::npos) {
      results.push_back(item);
    }
  }

  return results;
}

vector<Item*> Search::SearchByCreator(const vector<Item*>& items,
                                      const string& name) {
  // initialize
  vector<Item*> results;

  for (Item* item : items) {
    // dynamicly convert Item to Book
    Book* book = dynamic_cast<Book*>(item);
    // if book is not nullptr
    if (book && book->GetAuthor().find(name) != string::npos) {
      results.push_back(item);
      continue;  // finish current loop
    }

    // dynamicly convert Item to DVD
    DVD* dvd = dynamic_cast<DVD*>(item);
    // if dvd is not nullptr
    if (dvd && dvd->GetDirector().find(name) != string::npos) {
      results.push_back(item);
    }
  }

  return results;
}