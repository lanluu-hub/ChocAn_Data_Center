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