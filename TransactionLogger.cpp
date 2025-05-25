#include "TransactionLogger.h"

TransactionLogger::TransactionLogger(const string& fname)
    : log_file_name(fname) {}

TransactionLogger::~TransactionLogger() {}

string TransactionLogger::GetCurrentTime() const {
  time_t now = time(0);  // get current time stamp

  // format time
  char buf[64];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

  // convert into string
  return string(buf);
}

void TransactionLogger::LogBorrow(const Reader* reader, const Item* item) {
  ofstream log_file(log_file_name, ios::app);  // mode: append

  if (!log_file.is_open()) {
    // if can not open log file
    cout << "⚠️ Failed to open log file for writing.\n";
    return;
  }

  // write information to log file
  log_file << "BORROW," << GetCurrentTime() << "," << reader->GetId() << ","
           << reader->GetUsername() << "," << item->GetId() << ","
           << item->GetTitle() << "\n";

  log_file.close();  // close file
}

void TransactionLogger::LogReturn(const Reader* reader, const Item* item) {
  ofstream log_file(log_file_name, ios::app);  // mode: append

  if (!log_file.is_open()) {
    // if can not open log file
    cout << "⚠️ Failed to open log file for writing.\n";
    return;
  }

  // write information to log file
  log_file << "RETURN," << GetCurrentTime() << "," << reader->GetId() << ","
           << reader->GetUsername() << "," << item->GetId() << ","
           << item->GetTitle() << "\n";

  log_file.close();  // close file
}

void TransactionLogger::PrintAll() const {
  ifstream log_file(log_file_name);  // input stream

  if (!log_file.is_open()) {
    // if can not open log file
    cout << "⚠️ Failed to open log file for printing.\n";
    return;
  }

  // output all log information
  cout << "===================== Transaction Log =====================" << endl;
  string line;
  while (getline(log_file, line)) {
    cout << line << endl;
  }
  cout << "===========================================================" << endl;

  log_file.close();  // close file
}

void TransactionLogger::ExportToFile(const string& out_path) const {
  ifstream in_file(log_file_name);  // input stream
  if (!in_file.is_open()) {
    // if can not open log file
    cout << "⚠️ Failed to open source log file: " << log_file_name << endl;
    return;
  }

  ofstream out_file(out_path);  // output stream
  if (!out_file.is_open()) {
    // if can not open aim file
    cout << "⚠️ Failed to open destination file: " << out_path << endl;
    return;
  }

  string line;
  while (getline(in_file, line)) {
    // copy source to destination
    out_file << line << "\n";
  }

  cout << "✅ Log exported to: " << out_path << endl;

  // close file
  in_file.close();
  out_file.close();
}