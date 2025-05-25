# Makefile
MAKEFLAGS += --no-print-directory

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Executable name
TARGET = a

# Source files
SRCS = main.cpp \
       LibrarySystem.cpp \
       InventoryManager.cpp \
	   TransactionLogger.cpp \
	   Search.cpp \
       ./Item/PrintedBook.cpp \
	   ./Item/EBook.cpp \
	   ./Item/DVD.cpp \
	   ./Item/Item.cpp \
	   ./Item/Book.cpp \
	   ./User/User.cpp \
	   ./User/Reader.cpp \
	   ./User/Admin.cpp


# Build and run tests
.PHONY: all compile run clean

compile:
	@$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run:
	@./$(TARGET) 

clean:
	@rm -f $(TARGET)

all:
	@$(MAKE) compile
	@$(MAKE) run
	@$(MAKE) clean