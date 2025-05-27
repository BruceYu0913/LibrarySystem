#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
 protected:
  int id;
  string username;
  string password;
  string user_type;  // "reader" | "admin"

 public:
  User(const int id, const string& username, const string& password,
       const string& user_type);

  virtual ~User();

  int GetId() const;
  string GetUsername() const;
  string GetPassword() const;
  string GetUserType() const;

  void SetUsername(const string& uname);
  void SetPassword(const string& pwd);

  virtual void DisplayInfo() const = 0;
};

#endif