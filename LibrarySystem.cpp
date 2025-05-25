#include "LibrarySystem.h"

LibrarySystem::LibrarySystem()
    : inventory_manager(inventory_file_path), logger(log_file_path) {
  // load all items from file
  inventory_manager.LoadInventory(items);

  // load all users from file
  LoadUsers();
}

LibrarySystem::~LibrarySystem() {
  // Save current inventory to file
  inventory_manager.SaveInventory(items);

  // release all Item objects
  for (Item* item : items) {
    delete item;
  }
  items.clear();

  // release all User objects
  for (User* user : users) {
    delete user;
  }
  users.clear();
}

void LibrarySystem::Run() {
  cout << "===============================================" << endl;
  cout << "📚 Welcome to the Library System" << endl;
  cout << "===============================================" << endl;

  while (true) {
    ShowLoginMenu();  // Display login interface
  }
}

void LibrarySystem::LoadUsers() {
  ifstream file(user_file_path);  // input stream
  if (!file.is_open()) {
    cout << "⚠️ Failed to open user file: " << user_file_path << endl;
    return;
  }

  string line;

  while (getline(file, line)) {
    if (line.empty()) continue;  // empty line, skip current loop

    // split line with ','
    stringstream ss(line);
    string role, username, password, id_str;
    getline(ss, role, ',');
    getline(ss, username, ',');
    getline(ss, password, ',');
    getline(ss, id_str, ',');

    int id = stoi(id_str);  // convert string to int

    if (role == "reader") {
      users.push_back(new Reader(id, username, password));
    } else if (role == "admin") {
      users.push_back(new Admin(id, username, password));
    } else {
      cout << "❌ Unknown role type: " << role << endl;
    }
  }

  file.close();
}

User* LibrarySystem::Authenticate(const string& username,
                                  const string& password, const string& role) {
  for (User* user : users) {
    if (user->GetUsername() == username && user->GetPassword() == password &&
        user->GetUserType() == role) {
      return user;
    }
  }

  return nullptr;  // not found
}
