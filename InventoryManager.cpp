#include "InventoryManager.h"

Item* InventoryManager::LineToItem(const string& line) {
  stringstream ss(line);       // use line as a stream
  string field;                // store every field
  vector<std::string> fields;  // store all the fields

  while (getline(ss, field, ',')) {
    // split line with ','  put field in fields
    fields.push_back(field);
  }

  if (fields.empty()) return nullptr;

  string type = fields[0];  // the first field in CSV file is the type

  if (type == "PrintedBook") {
    if (fields.size() < 8) return nullptr;

    int id = stoi(fields[1]);
    string title = fields[2];
    bool isAvailable = (fields[3] == "true");
    int num = stoi(fields[4]);
    string author = fields[5];
    string isbn = fields[6];
    string shelf_location = fields[7];

    return new PrintedBook(id, title, isAvailable, num, author, isbn,
                           shelf_location);
  }

  else if (type == "EBook") {
    if (fields.size() < 11) return nullptr;

    int id = stoi(fields[1]);
    string title = fields[2];
    bool isAvailable = (fields[3] == "true");
    int num = stoi(fields[4]);
    string author = fields[5];
    string isbn = fields[6];
    string download_link = fields[7];
    float file_size = stof(fields[8]);
    string format = fields[9];
    time_t expiry_date = static_cast<time_t>(stoll(fields[10]));

    return new EBook(id, title, isAvailable, num, author, isbn, download_link,
                     file_size, format, expiry_date);
  }

  else if (type == "DVD") {
    if (fields.size() < 9) return nullptr;

    int id = stoi(fields[1]);
    string title = fields[2];
    bool isAvailable = (fields[3] == "true");
    int num = stoi(fields[4]);
    string director = fields[5];
    int duration = stoi(fields[6]);
    string media_type = fields[7];
    bool is_playable = (fields[8] == "true");

    return new DVD(id, title, isAvailable, num, director, duration, media_type,
                   is_playable);
  }

  else {
    return nullptr;
  }
}

string InventoryManager::ItemToLine(const Item* item) { return item->ToCsv(); }

InventoryManager::InventoryManager(const string& file) : filename(file) {}

void InventoryManager::LoadInventory(vector<Item*>& items) {
  // clear all data in items, avoid data repeat
  items.clear();

  ifstream inventory_file(filename);  // open inventory file
  if (!inventory_file.is_open()) {
    // if the path is not correct, stop the function
    cout << "⚠️ Failed to open inventory file: " << filename << endl;
    return;
  }

  string line;
  while (getline(inventory_file, line)) {
    if (line.empty()) continue;  // ignore empty line in csv file

    Item* item = LineToItem(line);  // convert one line into Item object
    if (item != nullptr) {
      items.push_back(item);  // add this item into the vector
    } else {
      cout << "Failed to parse line: " << line << endl;
    }
  }

  inventory_file.close();  // close this file
}

void InventoryManager::SaveInventory(const vector<Item*>& items) {
  // open the inventory file
  ofstream inventory_file(filename);
  if (!inventory_file.is_open()) {
    cout << "⚠️ Failed to open inventory file for writing: " << filename << endl;
    return;
  }

  // use a loop to write all items information in CSV file
  vector<Item*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); ++itr) {
    Item* item = *itr;
    string line = ItemToLine(item);
    inventory_file << line << "\n";
  }

  inventory_file.close();  // close file
}

InventoryManager::~InventoryManager() {}