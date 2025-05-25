#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

#include "Item/Book.h"
#include "Item/DVD.h"
#include "Item/Item.h"

using namespace std;

class Search {
 public:
  static vector<Item*> SearchByID(const vector<Item*>& items, int id);

  static vector<Item*> SearchByTitle(const vector<Item*>& items,
                                     const string& title);

  // author or director
  static vector<Item*> SearchByCreator(const vector<Item*>& items,
                                       const string& name);
};

#endif