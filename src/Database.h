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
#include "models/Member.h" // for member report
#include "models/Provider.h" // for provider report. 

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
        

        

        /* 
            Operator Terminal Functionalities
        */
        // Member Functionalities
        bool deleteMember(const std::string &memberID);
        // Provider Functionalities
        

        bool deleteProvider(const std::string &providerID);


        /* 
            Manager Terminal 
        */
        //Functions for generating reports
        void generateMemberReport(const std::string memberID, const std::string bestDate, std::string &filePath);
        void generateProviderReport(const std::string providerID, const std::string bestDate, std::string &filePath);


        /* 
            Record a service into ServiceLog Table
        */
        bool serviceLog (const std::string& providerId, 
                         const std::string& memberID,
                         const std::string& serviceCode, 
                         const std::string& dateOfService,
                         const std::string& timeStamp,
                         const std::string& comment);



        /* 
            Utilities 
        */

        std::string generateNewID(const std::string& type);
        
        //Search
        bool search(const std::string &table, const std::string &column, const std::string &id);
        bool searchMember(const std::string memberID);
        bool searchProvider(const std::string providerID);

        // Update 
        bool update(const std::string& id,
                    const std::string& table,
                    const std::string& address,
                    const std::string& city,
                    const std::string& state,
                    const std::string& zip);

        // Add
        bool add(const std::string& table, 
                    const std::string& name,
                    const std::string& address,
                    const std::string& city,
                    const std::string& state,
                    const std::string& zip);

        bool deleteUser(const std::string& table, const std::string& id);

        //Functions for get dby ID/Code
        Service getService(const std::string serviceCode);
        Member getMember(const std::string memberID);
        Provider getProvider(const std::string providerID);

    private:
        Database();
        ~Database();

        sqlite3* db;

        // Helper function
        bool OpenConnection();
        void CloseConnection();
};


#endif // DATABASE_H