# Lan Luu
# lanluu@pdx.edu
# makefile for ChocAn Data Processing System

CXX = g++
DEBUG = -g3 
CXXFLAGS = $(DEBUG) -Wall -std=c++17

# $@  - The name of the target of the rule
# $<  - The name of the first prerequisite
# $^  - The names of all the prerequisites

# Linker Flags (add SQLite)
LDFLAGS = #-lsqlite3

# Target executable
TARGET = chocan

# sources files, add more sources file here, use "\" to enter a newline
SRCS = \
	src/main.cpp \
	src/terminals/TerminalSession.cpp \
	src/terminals/ProviderTerminal.cpp \
	src/models/Member.cpp \
	src/models/Provider.cpp \
	src/models/Service.cpp  


# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET)

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS)	-o $@ $(OBJS)	$(LDFLAGS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Clean rule to remove generated files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(TARGET).exe) $(subst /,\,$(OBJS))
else
	rm -f $(TARGET) $(OBJS)
endif