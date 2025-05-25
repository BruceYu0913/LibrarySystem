#include "Item.h"

#include <iostream>
#include <string>

Item::Item(int id, const std::string& title, bool isAvailable, int num)
    : id(id), title(title), isAvailable(isAvailable), num(num) {}

int Item::GetId() const { return id; }

std::string Item::GetTitle() const { return title; }

bool Item::GetAvailable() const { return isAvailable; }

void Item::SetAvailable(bool status) { isAvailable = status; }

int Item::GetNum() const { return num; }

void Item::SetNum(int n) { num = n; }

Item::~Item() {}
