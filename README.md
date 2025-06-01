# ChocAn Data Processing System

A simplified data processing system developed for Chocoholics Anonymous (ChocAn), designed by **Team Whitespace** as part of the CS314 Software Engineering course at Portland State University.

## 🚀 Project Overview

This project simulates a real-world service management system that allows ChocAn providers and managers to:

- Validate members
- Log services provided
- View the provider directory
- Generate weekly reports for members, providers, and management

The system uses a **terminal-based interface** and integrates with an **SQLite-backed database** for secure and persistent data storage.

## 👥 Team Whitespace

- Piper Lake  
- Son Phan  
- Lan Luu  
- Tin Duong  
- Hunter Gambee-Iddings  

## 📁 Project Structure
```bash 
ChocAn_Data_Center/
├── src/
| ├── reports/
| | ├── members/
| | ├── providers/
| | └── provider_directory.txt
│ ├── database/
│ │ └── chocan.db
│ ├── models/
│ │ ├── Member.h / Member.cpp
│ │ ├── Provider.h / Provider.cpp
│ │ └── Service.h / Service.cpp
│ ├── sqlite/
│ │ ├── shell.c
│ │ ├── sqlite3.c
│ │ ├── sqlite3.h
│ │ └── sqlite3ext.h
│ ├── terminals/
│ │ ├── TerminalSession.h / TerminalSession.cpp
│ │ ├── ProviderTerminal.h / ProviderTerminal.cpp
│ │ ├── ManagerTerminal.h / ManagerTerminal.cpp
│ │ └── OperatorTerminal.h / OperatorTerminal.cpp
│ ├── ChocAnSystem.h / ChocAnSystem.cpp
│ ├── Database.h / Database.cpp
│ └── main.cpp
├── Makefile
└── README.md
```

## 🧩 Features

- **Terminal Interface** for providers, managers, and operators
- **Member Validation** against status in the database
- **Service Logging** with automatic fee calculation
- **Weekly Reports**: member, provider, and summary.
- **SQLite Integration** for efficient data storage and querying
- **Modular Architecture** using OOP and design patterns (Singleton, Facade)

## 🛠️ How to Build & Run

### 🔧 Prerequisites

- C++17 or later
- `sqlite3` development libraries installed

### 🧪 Build
1. Ensure a C++ compiler (e.g., `g++`) is installed.
2. From the root directory, run the following command:
```bash
make
```

▶️ Run
After building, run the application using:
```bash
./chocan
```

### 📜 License
This project was developed for educational purposes under Portland State University's CS314 course. Not for commercial use.

