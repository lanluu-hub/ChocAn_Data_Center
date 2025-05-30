/*
 * Created: May 17, 2025
 * -----------------------------
 * Database.h
 * 
 * This file defines the Database class, which provides an interface for interacting
 * with the underlying SQLite database used by the ChocAn Data Processing System.
 * It is responsible for validating users, logging services, retrieving provider
 * directory information, and generating report data.
 * 
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>
#include <vector>
#include "models/Service.h"

class Service;

class Database {
    public:
        // delete Copy constructor to prevent copy
        Database(const Database& obj) = delete;

        // Returns the thread-safe, lazily-initialized Singleton instance of the Database class.
        // This ensures only one shared connection point to the SQLite database exists 
        // across the entire application.
        //
        // Usage:
        //     Database::getInstance().validateMember(...);
        //     Database::getInstance().logService(...);
        //
        // Syntax:
        //     Database::getInstance().[Public_Method_Name](...);
        static Database& getInstance();

        // Other Public Function here
        int authenticateUser(const std::string userID);
        std::vector<Service> getProviderDirectory();
        int validateMembership(const std::string& memberID);

        Service getService(const std::string serviceCode);


    private:
        Database();
        ~Database();

        sqlite3* db;

        // Helper function
        bool OpenConnection();
        void CloseConnection();
};


#endif // DATABASE_H