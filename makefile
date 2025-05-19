# Lan Luu
# lanluu@pdx.edu
# makefile for ChocAn Data Processing System

CXX = g++
CC = gcc
DEBUG = -g3 
INCLUDES = -I src/sqlite
CXXFLAGS = $(DEBUG) -Wall -std=c++17 $(INCLUDES)

# $@  - The name of the target of the rule
# $<  - The name of the first prerequisite
# $^  - The names of all the prerequisites

# Linker Flags (add SQLite)
#LDFLAGS = -lsqlite3 -Llib -I src/sqlite

SQLITE_SRC = src/sqlite/sqlite3.c
SQLITE_OBJ = src/sqlite/sqlite3.o

# Target executable
TARGET = chocan

# sources files, add more sources file here, use "\" to enter a newline
SRCS = \
	src/main.cpp \
	src/terminals/TerminalSession.cpp \
	src/terminals/ProviderTerminal.cpp \
	src/ChocAnSystem.cpp \
	src/Database.cpp \
	src/models/Member.cpp \
	src/models/Provider.cpp \
	src/models/Service.cpp  


# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET)

# Rule to link object files into the target executable
$(TARGET): $(OBJS) $(SQLITE_OBJ)
	$(CXX) $(CXXFLAGS)	-o $@ $(OBJS)	$(SQLITE_OBJ)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SQLITE_OBJ): $(SQLITE_SRC)
	$(CC) -c $(SQLITE_SRC) -o $(SQLITE_OBJ)

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Clean rule to remove generated files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(TARGET).exe) $(subst /,\,$(OBJS)) $(subst /,\,$(SQLITE_OBJ))
else
	rm -f $(TARGET) $(OBJS) $(SQLITE_OBJ)
endif