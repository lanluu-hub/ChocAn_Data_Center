
#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Database.h"


Database::Database() : db(nullptr)
{
    OpenConnection();
}

Database::~Database()
{
    CloseConnection();
}

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

int Database::authenticateUser(const std::string& userID)
{
    // Database logic to get role based on userID;
    // if int = 0: Operator Terminal
    // if int = 1: Manager Terminal
    // if int = 2: Provider Terminal
    // if int = -1: invalid, no terminal, if userID not found 
    return 2;
}

std::vector<Service> Database::getProviderDirectory()
{
    std::vector<Service> services;

    const char* query = "SELECT service_code, name, fee FROM Services ORDER BY service_code;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return services;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string code     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string name     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double fee           = sqlite3_column_double(stmt, 2);

        Service s(code, name, fee);
        services.push_back(s);
    }

    sqlite3_finalize(stmt);
    return services;
}