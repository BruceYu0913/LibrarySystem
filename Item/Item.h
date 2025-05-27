#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

class Item {
 protected:
  int id;
  std::string title;
  bool isAvailable;
  int num;

 public:
  Item(int id, const std::string& title, bool isAvailable, int num);

  int GetId() const;
  std::string GetTitle() const;
  bool GetAvailable() const;
  void SetAvailable(bool status);
  int GetNum() const;
  void SetNum(int n);

  virtual void DisplayInfo() const = 0;
  virtual std::string GetType() const = 0;

  virtual std::string ToCsv() const = 0;

  virtual ~Item();
};

#endif
