#include "LibrarySystem.h"

void PauseAndClear() {
  cout << "Press Enter to continue...\n";
  cin.get();  // Wait for Enter key
  system("clear");
}

bool IsStrictInteger(const string& s) {
  if (s.empty()) return false;
  for (char c : s) {
    if (!isdigit(c)) return false;
  }
  return true;
}

string GenerateExportLogFilename() {
  // get current time
  time_t now = time(nullptr);
  tm* local = localtime(&now);

  // format file name
  char buffer[64];
  strftime(buffer, sizeof(buffer), "./ExportLog/log_%Y%m%d_%H%M%S.csv", local);

  return string(buffer);
}

string ToUpper(const string& s) {
  string result = s;
  transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

bool ParseExpiryDate(const string& input, time_t& output_time) {
  tm tm_parsed = {};
  istringstream ss(input);
  ss >> get_time(&tm_parsed, "%Y-%m-%d");
  if (ss.fail()) return false;

  tm_parsed.tm_hour = 0;  // normalize to start of day
  tm_parsed.tm_min = 0;
  tm_parsed.tm_sec = 0;

  time_t expiry = mktime(&tm_parsed);
  if (expiry <= time(nullptr)) return false;

  output_time = expiry;
  return true;
}

LibrarySystem::LibrarySystem()
    : inventory_manager(inventory_file_path), logger(log_file_path) {
  // load all items from file
  inventory_manager.LoadInventory(items);

  // load all users from file
  LoadUsers();

  // load reader_id <-> item_id
  LoadBorrowedRecords();

  // initialize next ID counters
  InitNextIdsFromItems();
}

LibrarySystem::~LibrarySystem() {
  // save current inventory to file
  inventory_manager.SaveInventory(items);

  // save reader_id <-> item_id
  SaveBorrowedRecords();

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

  while (running) {
    ShowLoginMenu();  // Display login interface
  }
}

void LibrarySystem::InitNextIdsFromItems() {
  for (Item* item : items) {
    int id = item->GetId();

    if (id >= 11000000 && id < 12000000) {
      next_pbk_id = max(next_pbk_id, id + 1);
    } else if (id >= 12000000 && id < 13000000) {
      next_ebk_id = max(next_ebk_id, id + 1);
    } else if (id >= 21000000 && id < 22000000) {
      next_dvd_id = max(next_dvd_id, id + 1);
    }
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

void LibrarySystem::LoadBorrowedRecords() {
  ifstream file("./DataFiles/borrowed.csv");  // input stream
  if (!file.is_open()) {
    cout << "⚠️ Failed to open borrowed.csv. Skipping borrowed item loading.\n";
    return;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty()) continue;

    stringstream ss(line);
    string reader_id_str, item_id_str;
    getline(ss, reader_id_str, ',');
    getline(ss, item_id_str, ',');

    int reader_id = stoi(reader_id_str);
    int item_id = stoi(item_id_str);

    // find matching Reader*
    Reader* reader = nullptr;
    for (User* user : users) {
      if (user->GetId() == reader_id && user->GetUserType() == "reader") {
        reader = dynamic_cast<Reader*>(user);
        break;
      }
    }

    // find matching Item*
    Item* item = nullptr;
    for (Item* it : items) {
      if (it->GetId() == item_id) {
        item = it;
        break;
      }
    }

    if (reader && item) {
      reader->BorrowItem(item);  // record it in reader object
    }
  }

  file.close();
}

void LibrarySystem::SaveBorrowedRecords() {
  ofstream file("./DataFiles/borrowed.csv");
  if (!file.is_open()) {
    cout << "⚠️ Failed to open borrowed.csv for writing.\n";
    return;
  }

  for (User* user : users) {
    if (user->GetUserType() != "reader") continue;

    Reader* reader = dynamic_cast<Reader*>(user);
    if (!reader) continue;

    vector<Item*> borrowed = reader->GetBorrowedItems();

    for (Item* item : borrowed) {
      file << reader->GetId() << "," << item->GetId() << "\n";
    }
  }

  file.close();
}

void LibrarySystem::ShowLoginMenu() {
  while (true) {
    // display menu
    cout << "\n========== Login Menu ==========\n";
    cout << "1. Login as Reader\n";
    cout << "2. Login as Admin\n";
    cout << "0. Exit Program\n";
    cout << "===============================\n";
    cout << "Enter your choice (0/1/2): ";

    string input;
    getline(cin >> ws, input);

    // make sure the input can only be 0, 1, 2
    if (input != "0" && input != "1" && input != "2") {
      cout << "❌ Invalid input. Please enter 0, 1, or 2.\n";
      PauseAndClear();
      continue;
    }

    int choice = stoi(input);  // safe input

    // exit program
    if (choice == 0) {
      cout << "👋 Exiting program... Goodbye!\n";
      running = false;
      return;
    }

    // choice only 1 and 2
    string role = (choice == 1) ? "reader" : "admin";

    system("clear");

    // ask user to input username and password
    string username, password;

    cout << "Username: ";
    getline(cin >> ws, username);

    cout << "Password: ";
    getline(cin >> ws, password);

    // authenticate user information
    User* user = Authenticate(username, password, role);
    if (user == nullptr) {
      cout << "❌ Login failed. Please check your username and password.\n";
      PauseAndClear();
    } else {
      cout << "✅ Login successful. Welcome, " << username << "!\n";
      system("clear");

      if (role == "reader") {
        Reader* reader = dynamic_cast<Reader*>(user);
        if (reader) ReaderMenu(reader);
      } else {
        Admin* admin = dynamic_cast<Admin*>(user);
        if (admin) AdminMenu(admin);
      }
    }
  }
}

void LibrarySystem::AdminMenu(Admin* admin) {
  while (true) {
    admin->DisplayInfo();

    cout << "\n========== Admin Menu ==========\n";
    cout << "1. View all items\n";
    cout << "2. Add new item\n";
    cout << "3. Delete item by ID\n";
    cout << "4. Update item quantity\n";
    cout << "5. View logs\n";
    cout << "6. Export log file\n";
    cout << "0. Logout\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";

    string input;
    getline(cin >> ws, input);

    if (input == "0") {
      cout << "👋 Logging out...\n";
      PauseAndClear();
      break;
    } else if (input == "1") {
      // View all items
      system("clear");
      cout << "========== All Items ==========\n";

      if (items.empty()) {
        cout << "⚠️ No items available in the library.\n";
      } else {
        for (Item* item : items) {
          cout << "Type: " << item->GetType() << " | ID: " << item->GetId()
               << " | Title: " << item->GetTitle()
               << " | Quantity: " << item->GetNum()
               << " | Available: " << (item->GetAvailable() ? "Yes" : "No");

          Book* book = dynamic_cast<Book*>(item);
          DVD* dvd = dynamic_cast<DVD*>(item);

          if (book) {
            cout << " | Author: " << book->GetAuthor();
          } else if (dvd) {
            cout << " | Director: " << dvd->GetDirector();
          }

          cout << endl;
        }
        cout << "=================================\n";
      }

      PauseAndClear();
    } else if (input == "2") {
      // Add new item
      system("clear");

      cout << "========== Add New Item ==========\n";
      cout << "Select item type to add:\n";
      cout << "1. PrintedBook\n";
      cout << "2. EBook\n";
      cout << "3. DVD\n";
      cout << "Enter your choice: ";

      string type_input;
      getline(cin >> ws, type_input);

      int type = 0;
      if (IsStrictInteger(type_input)) {
        type = stoi(type_input);
      } else {
        cout << "❌ Invalid choice.\n";
        PauseAndClear();
        continue;
      }

      if (type < 1 || type > 3) {
        cout << "❌ Choice must be 1~3.\n";
        PauseAndClear();
        continue;
      }

      cout << "=================================\n";

      // get title from user
      string title;
      cout << "Enter Title: ";
      getline(cin >> ws, title);

      // get num from user
      string num_input;
      cout << "Enter Quantity: ";
      getline(cin >> ws, num_input);
      if (!IsStrictInteger(num_input)) {
        cout << "❌ Invalid quantity.\n";
        PauseAndClear();
        continue;
      }
      int num = stoi(num_input);

      // set is_available
      bool is_available = num > 0;

      // automatically assign ID
      int id;
      if (type == 1)
        id = next_pbk_id++;
      else if (type == 2)
        id = next_ebk_id++;
      else if (type == 3)
        id = next_dvd_id++;
      cout << "Generated ID: " << id << "\n";

      Item* new_item = nullptr;

      if (type == 1) {
        string author, isbn, location;

        cout << "Enter Author: ";
        getline(cin >> ws, author);

        cout << "Enter ISBN: ";
        getline(cin >> ws, isbn);

        cout << "Enter Location: ";
        getline(cin >> ws, location);

        new_item = new PrintedBook(id, title, is_available, num, author, isbn,
                                   location);
      } else if (type == 2) {
        string author, isbn, download_link, format, file_size_input,
            expiry_input;
        float file_size;
        time_t expiry_date;

        cout << "Enter Author: ";
        getline(cin >> ws, author);

        cout << "Enter ISBN: ";
        getline(cin >> ws, isbn);

        cout << "Enter Download Link: ";
        getline(cin >> ws, download_link);

        // ask for file size
        while (true) {
          cout << "Enter File Size (in MB): ";
          string file_size_input;
          getline(cin >> ws, file_size_input);

          try {
            file_size = stof(file_size_input);
            if (file_size <= 0.0f) {
              throw invalid_argument("Non-positive");
            }
            break;  // valid
          } catch (...) {
            cout << "❌ Invalid input. Please enter a positive number.\n";
          }
        }

        // ask for format, only pdf and epub
        while (true) {
          cout << "Enter Format (PDF or EPUB, case-insensitive): ";
          getline(cin >> ws, format);

          string fmt_upper = ToUpper(format);
          if (fmt_upper == "PDF" || fmt_upper == "EPUB") {
            format = fmt_upper;  // convert to uppercase
            break;
          } else {
            cout << "❌ Invalid format. Please enter either PDF or EPUB.\n";
          }
        }

        // ask for expiry date
        while (true) {
          cout << "Enter Expiry Date (YYYY-MM-DD): ";
          getline(cin >> ws, expiry_input);

          if (ParseExpiryDate(expiry_input, expiry_date)) {
            break;  // ✅ valid date
          } else {
            cout << "❌ Invalid date. Please use YYYY-MM-DD and ensure it's a "
                    "future date.\n";
          }
        }

        new_item = new EBook(id, title, is_available, num, author, isbn,
                             download_link, file_size, format, expiry_date);

      } else if (type == 3) {
        string director, media_type, duration_input;
        int duration;

        cout << "Enter Director: ";
        getline(cin >> ws, director);

        // ask for duration
        while (true) {
          cout << "Enter Duration (in minutes): ";
          getline(cin >> ws, duration_input);
          if (!IsStrictInteger(duration_input)) {
            cout << "❌ Invalid input. Must be a positive integer.\n";
            continue;
          }

          duration = stoi(duration_input);
          if (duration <= 0) {
            cout << "❌ Duration must be greater than 0.\n";
            continue;
          }

          break;
        }

        cout << "Enter Media Type (e.g., mp4, mkv): ";
        getline(cin >> ws, media_type);

        new_item = new DVD(id, title, is_available, num, director, duration,
                           media_type, true);
      }

      if (new_item) {
        items.push_back(new_item);
        inventory_manager.SaveInventory(items);
        cout << "✅ Item added successfully with ID " << id << "!\n";
      } else {
        cout << "❌ Failed to create item.\n";
      }

      PauseAndClear();

    } else if (input == "3") {
      // Delete item
      system("clear");

      cout << "========== Delete Item ==========\n";
      cout << "Enter item ID to delete: ";

      string id_input;
      getline(cin >> ws, id_input);

      if (!IsStrictInteger(id_input)) {
        cout << "❌ Invalid input. Please enter a valid integer ID.\n";
        PauseAndClear();
        continue;
      }

      int id = stoi(id_input);
      Item* to_delete = nullptr;
      auto it = items.begin();

      for (; it != items.end(); ++it) {
        if ((*it)->GetId() == id) {
          to_delete = *it;
          break;
        }
      }

      if (!to_delete) {
        cout << "❌ No item found with ID " << id << ".\n";
        PauseAndClear();
        continue;
      }

      cout << "=================================\n";
      cout << "Item found:\n";
      to_delete->DisplayInfo();
      cout << "=================================\n";

      cout << "\nAre you sure you want to delete this item? (Y/N): ";
      string confirm;
      getline(cin >> ws, confirm);

      if (confirm == "Y" || confirm == "y") {
        delete to_delete;                        // Free memory
        items.erase(it);                         // Remove from vector
        inventory_manager.SaveInventory(items);  // Save changes

        cout << "✅ Item deleted successfully.\n";
      } else {
        cout << "❎ Deletion cancelled.\n";
      }

      PauseAndClear();

    } else if (input == "4") {
      // Update item quantity
      system("clear");

      cout << "========== Update Item Quantity ==========\n";
      cout << "Enter item ID to update: ";

      string id_input;
      getline(cin >> ws, id_input);

      if (!IsStrictInteger(id_input)) {
        cout << "❌ Invalid ID input. Please enter a valid integer.\n";
        PauseAndClear();
        continue;
      }

      int id = stoi(id_input);

      // Search for item
      Item* item = nullptr;
      for (Item* it : items) {
        if (it->GetId() == id) {
          item = it;
          break;
        }
      }

      // no this id in items
      if (!item) {
        cout << "❌ Item with ID " << id << " not found.\n";
        PauseAndClear();
        continue;
      }

      cout << "Current quantity: " << item->GetNum() << "\n";
      cout << "Enter new quantity (>= 0): ";

      // get the new quantity from user
      string qty_input;
      getline(cin >> ws, qty_input);

      if (!IsStrictInteger(qty_input)) {
        cout << "❌ Invalid input. Please enter a non-negative integer.\n";
        PauseAndClear();
        continue;
      }

      int new_qty = stoi(qty_input);
      item->SetNum(new_qty);

      // Auto update available status
      item->SetAvailable(new_qty > 0);

      // Save changes
      inventory_manager.SaveInventory(items);

      cout << "✅ Quantity updated successfully.\n";

      PauseAndClear();

    } else if (input == "5") {
      // View logs
      system("clear");

      logger.PrintAll();

      PauseAndClear();
    } else if (input == "6") {
      // Export logs
      system("clear");

      cout << "========== Export Log ==========\n";

      string filename = GenerateExportLogFilename();
      logger.ExportToFile(filename);

      PauseAndClear();
    } else {
      cout << "❌ Invalid input. Please try again.\n";
      PauseAndClear();
    }
  }
}

void LibrarySystem::ReaderMenu(Reader* reader) {
  while (true) {
    // show user info
    reader->DisplayInfo();

    // display menu
    cout << "\n========== Reader Menu ==========\n";
    cout << "1. View all items\n";
    cout << "2. View borrowed items\n";
    cout << "3. Borrow item by ID\n";
    cout << "4. Return item by ID\n";
    cout << "5. Search item by ID\n";
    cout << "6. Search item by title\n";
    cout << "7. Search item by author/director\n";
    cout << "0. Logout\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";

    string input;
    getline(cin >> ws, input);

    if (input == "0") {
      cout << "👋 Logging out...\n";
      PauseAndClear();
      break;
    } else if (input == "1") {
      system("clear");
      // View all items
      cout << "========== All Items ==========\n";

      if (items.empty()) {
        cout << "⚠️ No items available in the library.\n";
      } else {
        for (Item* item : items) {
          cout << "Type: " << item->GetType() << " | ID: " << item->GetId()
               << " | Title: " << item->GetTitle()
               << " | Quantity: " << item->GetNum()
               << " | Available: " << (item->GetAvailable() ? "Yes" : "No");

          Book* book = dynamic_cast<Book*>(item);
          DVD* dvd = dynamic_cast<DVD*>(item);

          if (book) {
            cout << " | Author: " << book->GetAuthor();
          } else if (dvd) {
            cout << " | Director: " << dvd->GetDirector();
          }

          cout << endl;
        }

        cout << "=================================\n";
      }

      PauseAndClear();
    } else if (input == "2") {
      system("clear");

      // View borrowed items
      reader->ShowBorrowedItems();
      cout << "=================================\n";

      PauseAndClear();
    } else if (input == "3") {
      // Borrow item
      system("clear");

      cout << "========== Borrow Item ==========\n";
      cout << "Enter item ID to borrow: ";

      string id_input;
      getline(cin >> ws, id_input);

      if (!IsStrictInteger(id_input)) {
        cout << "❌ Invalid input. Please enter a valid integer ID.\n";
        PauseAndClear();
        continue;
      }

      int id = stoi(id_input);

      // Find the item by ID
      Item* item = nullptr;
      for (Item* it : items) {
        if (it->GetId() == id) {
          item = it;
          break;
        }
      }

      if (!item) {
        cout << "❌ Item with ID " << id << " does not exist.\n";
      } else if (!item->GetAvailable()) {
        cout << "❌ This item is currently not available.\n";
      } else if (item->GetNum() <= 0) {
        cout << "❌ No copies left to borrow.\n";
      } else {
        // Check if reader already borrowed it
        bool alreadyBorrowed = false;
        for (Item* b : reader->GetBorrowedItems()) {
          if (b->GetId() == id) {
            alreadyBorrowed = true;
            break;
          }
        }

        if (alreadyBorrowed) {
          cout << "⚠️ You have already borrowed this item.\n";
        } else {
          reader->BorrowItem(item);
          item->SetNum(item->GetNum() - 1);
          if (item->GetNum() == 0) {
            item->SetAvailable(false);
          }

          logger.LogBorrow(reader, item);
          SaveBorrowedRecords();
          inventory_manager.SaveInventory(items);

          cout << "✅ Item borrowed successfully!\n";
        }
      }

      PauseAndClear();
    } else if (input == "4") {
      // Return item
      system("clear");

      cout << "========== Return Item ==========\n";
      cout << "Enter item ID to return: ";

      string id_input;
      getline(cin >> ws, id_input);

      if (!IsStrictInteger(id_input)) {
        cout << "❌ Invalid input. Please enter a valid integer ID.\n";
        PauseAndClear();
        continue;
      }

      int id = stoi(id_input);
      vector<Item*> borrowed = reader->GetBorrowedItems();
      Item* item_to_return = nullptr;

      for (Item* item : borrowed) {
        if (item->GetId() == id) {
          item_to_return = item;
          break;
        }
      }

      if (!item_to_return) {
        cout << "❌ You have not borrowed item with ID " << id << ".\n";
      } else {
        reader->ReturnItem(item_to_return);
        item_to_return->SetNum(item_to_return->GetNum() + 1);
        item_to_return->SetAvailable(true);

        logger.LogReturn(reader, item_to_return);
        SaveBorrowedRecords();
        inventory_manager.SaveInventory(items);

        cout << "✅ Item returned successfully!\n";
      }

      PauseAndClear();
    } else if (input == "5") {
      // Search by ID
      system("clear");

      cout << "========== Search by ID ==========\n";
      cout << "Enter item ID to search: ";

      string id_input;
      getline(cin >> ws, id_input);

      if (!IsStrictInteger(id_input)) {
        cout << "❌ Invalid input. Please enter a valid integer ID.\n";
        PauseAndClear();
        continue;
      }

      int id = stoi(id_input);
      vector<Item*> result = Search::SearchByID(items, id);

      if (result.empty()) {
        cout << "❌ No item found with ID " << id << ".\n";
      } else {
        cout << "✅ Item found:\n";
        result[0]->DisplayInfo();
        cout << "=================================\n";
      }

      PauseAndClear();
    } else if (input == "6") {
      // Search by title
      system("clear");

      cout << "========== Search by Title ==========\n";
      cout << "Enter keyword to search in title: ";

      string keyword;
      getline(cin >> ws, keyword);

      if (keyword.empty()) {
        cout << "❌ Keyword cannot be empty.\n";
        PauseAndClear();
        continue;
      }

      vector<Item*> result = Search::SearchByTitle(items, keyword);

      if (result.empty()) {
        cout << "❌ No items found with title containing \"" << keyword
             << "\".\n";
      } else {
        cout << "✅ Items found:\n";
        for (Item* item : result) {
          cout << "Type: " << item->GetType() << " | ID: " << item->GetId()
               << " | Title: " << item->GetTitle()
               << " | Quantity: " << item->GetNum()
               << " | Available: " << (item->GetAvailable() ? "Yes" : "No");

          Book* book = dynamic_cast<Book*>(item);
          DVD* dvd = dynamic_cast<DVD*>(item);

          if (book) {
            cout << " | Author: " << book->GetAuthor();
          } else if (dvd) {
            cout << " | Director: " << dvd->GetDirector();
          }

          cout << endl;
        }
        cout << "=================================\n";
      }

      PauseAndClear();
    } else if (input == "7") {
      // Search by creator
      system("clear");

      cout << "========== Search by Author/Director ==========\n";
      cout << "Enter keyword to search: ";

      string keyword;
      getline(cin >> ws, keyword);

      if (keyword.empty()) {
        cout << "❌ Keyword cannot be empty.\n";
        PauseAndClear();
        continue;
      }

      vector<Item*> result = Search::SearchByCreator(items, keyword);

      if (result.empty()) {
        cout << "❌ No items found with creator containing \"" << keyword
             << "\".\n";
      } else {
        cout << "✅ Items found:\n";
        for (Item* item : result) {
          cout << "Type: " << item->GetType() << " | ID: " << item->GetId()
               << " | Title: " << item->GetTitle()
               << " | Quantity: " << item->GetNum()
               << " | Available: " << (item->GetAvailable() ? "Yes" : "No");

          // Show author or director
          Book* book = dynamic_cast<Book*>(item);
          DVD* dvd = dynamic_cast<DVD*>(item);

          if (book) {
            cout << " | Author: " << book->GetAuthor();
          } else if (dvd) {
            cout << " | Director: " << dvd->GetDirector();
          }
          cout << endl;
        }
        cout << "=================================\n";
      }

      PauseAndClear();
    } else {
      cout << "❌ Invalid input. Please try again.\n";
      PauseAndClear();
    }
  }
}
