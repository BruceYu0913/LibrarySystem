#ifndef USER_TEST_H
#define USER_TEST_H

#include <cassert>
#include <iostream>

#include "User.h"

class MockUser : public User {
 public:
  MockUser(int id, const std::string& username, const std::string& password,
           const std::string& user_type)
      : User(id, username, password, user_type) {}

  void DisplayInfo() const override {
    cout << "ID: " << id << endl;
    cout << "MockUser: " << username << endl;
  }
};

class UserTest {
 public:
  void RunTests() {
    TestDisplay();
    TestGetter();
    TestSetter();
  }

 private:
  void TestDisplay() {
    cout << "----------Running TestDisplay----------" << endl;
    MockUser user(1001, "Alice", "Secret123", "reader");
    user.DisplayInfo();
    cout << "✅ TestDisplay finished, check the output information." << endl;
  }

  void TestGetter() {
    cout << "----------Running TestGetter----------" << endl;

    MockUser user(1001, "Alice", "Secret123", "reader");

    assert(user.GetId() == 1001);
    assert(user.GetUsername() == "Alice");
    assert(user.GetPassword() == "Secret123");
    assert(user.GetUserType() == "reader");

    cout << "✅ TestGetter PASSED." << endl;
  }

  void TestSetter() {
    cout << "----------Running TestSetter----------" << endl;

    MockUser user(1002, "Bob", "abc", "reader");

    user.SetUsername("Charlie");
    user.SetPassword("xyz123");

    assert(user.GetUsername() == "Charlie");
    assert(user.GetPassword() == "xyz123");

    cout << "✅ TestSetter PASSED." << endl;
  }
};

#endif
