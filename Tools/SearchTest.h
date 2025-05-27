#ifndef SEARCH_TEST_H
#define SEARCH_TEST_H

#include <cassert>
#include <iostream>

#include "../Item/DVD.h"
#include "../Item/EBook.h"
#include "../Item/PrintedBook.h"
#include "./Search.h"

class SearchTest {
 public:
  void RunTests() {
    TestSearchByID();
    TestSearchByTitle();
    TestSearchByCreator();
  }

 private:
  vector<Item*> GenerateSampleItems() {
    vector<Item*> items;

    items.push_back(
        new PrintedBook(1, "C++ Primer", true, 3, "Lippman", "ISBN1", "A1"));
    items.push_back(new EBook(2, "Advanced C++", true, 2, "Charles", "ISBN2",
                              "https://link", 5.6f, "PDF", 1704067200));
    items.push_back(
        new PrintedBook(3, "Design Patterns", true, 1, "Gamma", "ISBN2", "B2"));
    items.push_back(new DVD(4, "AI Documentary", true, 2, "James Smith", 90,
                            "Blu-ray", true));
    items.push_back(
        new DVD(5, "C++ Journey", true, 1, "Lippmen", 60, "DVD", true));

    return items;
  }

  void DeleteItems(std::vector<Item*>& items) {
    for (auto item : items) delete item;
    items.clear();
  }

  void TestSearchByID() {
    cout << "----------[Test] SearchByID----------\n";
    vector<Item*> items = GenerateSampleItems();

    vector<Item*> result = Search::SearchByID(items, 3);
    assert(result.size() == 1);
    assert(result[0]->GetTitle() == "Design Patterns");

    cout << "✅ SearchByID passed.\n";

    DeleteItems(items);
  }

  void TestSearchByTitle() {
    cout << "----------[Test] SearchByTitle (fuzzy match)----------\n";
    vector<Item*> items = GenerateSampleItems();

    vector<Item*> result = Search::SearchByTitle(items, "C++");
    assert(result.size() == 3);  // "C++ Primer", "Advanced C++", "C++ Journey"

    cout << "✅ SearchByTitle passed.\n";

    DeleteItems(items);
  }

  void TestSearchByCreator() {
    cout << "----------[Test] SearchByCreator (author or director)----------\n";
    vector<Item*> items = GenerateSampleItems();

    vector<Item*> result = Search::SearchByCreator(items, "Lipp");
    assert(result.size() == 2);  // 1 PrintedBook + 1 DVD

    auto result2 = Search::SearchByCreator(items, "Gamma");
    assert(result2.size() == 1);
    assert(result2[0]->GetTitle() == "Design Patterns");

    std::cout << "✅ SearchByCreator passed.\n";

    DeleteItems(items);
  }
};

#endif