#include "User.h"

User::User(const int id, const string& username, const string& password,
           const string& user_type)
    : id(id), username(username), password(password), user_type(user_type) {}

User::~User() {}

int User::GetId() const { return id; }
string User::GetUsername() const { return username; }
string User::GetPassword() const { return password; }
string User::GetUserType() const { return user_type; }

void User::SetUsername(const string& uname) { username = uname; }
void User::SetPassword(const string& pwd) { password = pwd; }