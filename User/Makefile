# Makefile
MAKEFLAGS += --no-print-directory

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Executable name
TARGET = a

# Source files
SRCS = Test.cpp \
       User.cpp \
	   Reader.cpp \
	   Admin.cpp \
	   ../Item/Item.cpp \
	   ../Item/Book.cpp \
	   ../Item/PrintedBook.cpp \
	   ../Item/EBook.cpp \
	   ../Item/DVD.cpp \
	   ../TransactionLogger.cpp
       

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