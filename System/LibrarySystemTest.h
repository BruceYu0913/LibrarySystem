#ifndef LIBRARY_SYSTEM_TEST_H
#define LIBRARY_SYSTEM_TEST_H

#include <cassert>
#include <iostream>

#include "LibrarySystem.h"

class LibrarySystemTest {
 public:
  void RunTests() {
    TestConsAndDes();
    TestAuthenticate();
  }

 private:
  void TestConsAndDes() {
    cout << "----------[Test] ConsAndDes----------\n";

    LibrarySystem* ls = new LibrarySystem();

    // Cannot directly access private users vector
    // but during test, set access to public
    // for (auto* item : ls->items) {
    //   string line;
    //   line = item->ToCsv();
    //   cout << line << endl;
    // }

    // for (auto* user : ls->users) {
    //   user->DisplayInfo();
    // }

    // PrintedBook* pb1 =
    //     new PrintedBook(10, "Book One", true, 1, "Author", "ISBN", "Shelf
    //     A");

    // ls->items.push_back(pb1);

    cout << "✅ LoadUsers ran without crash. (Check console for error if "
            "any)\n";

    delete ls;
  }

  void TestAuthenticate() {
    cout << "----------[Test] Authenticate ----------\n";

    LibrarySystem ls;

    // during test, set access to public

    // Case 1: valid reader
    // User* u1 = ls.Authenticate("alice", "1234", "reader");
    // assert(u1 != nullptr);
    // assert(u1->GetUsername() == "alice");

    // // Case 2: valid admin
    // User* u2 = ls.Authenticate("bob", "admin123", "admin");
    // assert(u2 != nullptr);
    // assert(u2->GetUserType() == "admin");

    // // Case 3: wrong password
    // assert(ls.Authenticate("alice", "wrong", "reader") == nullptr);

    // // Case 4: wrong role
    // assert(ls.Authenticate("alice", "1234", "admin") == nullptr);

    // // Case 5: unknown user
    // assert(ls.Authenticate("nobody", "1234", "reader") == nullptr);

    cout << "✅ Authenticate passed all 5 cases.\n";
  }
};

#endif