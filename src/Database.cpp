
#include <sqlite3.h>
#include <fstream>
#include <cstring>
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

int Database::authenticateUser(const std::string userID)
{
    // Database logic to get role based on userID;
    // if int = 0: Operator Terminal
    // if int = 1: Manager Terminal
    // if int = 2: Provider Terminal
    // if int = -1: invalid, no terminal, if userID not found 
    int role = -1; 

    const char * query = "SELECT user_type FROM Users WHERE user_id = ?;";

    sqlite3_stmt* stmt; 

    if(sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return -1;
    }
    //Bind userID to SQL query

    if(sqlite3_bind_text(stmt, 1, userID.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind user ID. \n";
        sqlite3_finalize(stmt); 
        return -1;
    }

    // combine or concate the query with userID passed in the argument
    // Final: SELECT user_type FROM Users WHERE user_id = userID;

    if(sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string userType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (userType == "Operator")
            role = 0;
        else if (userType == "Manager")
            role = 1;   
        else if (userType == "Provider")
            role = 2;
    }

    sqlite3_finalize(stmt);
    return role;
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


//
int Database::validateMembership(const std::string& memberID)
{
    const char * query = "SELECT status FROM Members Where member_id = ?;";
    sqlite3_stmt* stmt; 

     if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return -1;
    }

    // Bind the member ID to the query
    if (sqlite3_bind_text(stmt, 1, memberID.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind member ID.\n";
        sqlite3_finalize(stmt);
        return -1;
    }

    int result = -1;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* statusText = sqlite3_column_text(stmt, 0);
        std::string status = statusText ? reinterpret_cast<const char*>(statusText) : "";

        if (status == "Active") {
            std::cout << "[VALIDATED]\n";
            result = 0;
        } else if (status == "Suspended") {
            std::cout << "[SUSPEND]\n";
            result = 1;
        } else {
            std::cout << "[INVALID]\n";
            result = -1;
        }
    } else {
        std::cout << "[INVALID]\n";
        result = -1;
    }

    sqlite3_finalize(stmt);
    return result;
}