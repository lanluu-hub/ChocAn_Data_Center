#include <iostream>
#include <vector>
#include "Database.h"

Database::Database() : db(nullptr)
{
    OpenConnection();
}

Database::~Database()
{}

bool Database::OpenConnection()
{
    CloseConnection();

    int exit{};

    exit = sqlite3_open("src/database/chocan.db", &db);

    // check if connection is open, then close the opened connection

    // failed to open a connection to db file
    if (exit != SQLITE_OK) {
        std::cerr << "Error open DB: " << sqlite3_errmsg(db) << std::endl;

        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
        
        return false;
    } 
    
    return true;
}

void Database::CloseConnection()
{
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

Database& Database::getInstance()
{
    static Database instance;
    return instance;
}

int Database::authenticateUser(const std::string userID) 
{
    // Database logic to get role based on userID;
    // if int = 0: Operator Terminal
    // if int = 1: Manager Terminal
    // if int = 2: Provider Terminal
    // if int = -1: invalid, no terminal, if userID not found 
    return 2;
}