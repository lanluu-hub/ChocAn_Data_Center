
#include <sqlite3.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
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
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error open DB: " << sqlite3_errmsg(db) << std::endl;

        if (db)
        {
            sqlite3_close(db);
            db = nullptr;
        }

        return false;
    }

    return true;
}

void Database::CloseConnection()
{
    if (db != nullptr)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

Database &Database::getInstance()
{
    static Database instance;
    return instance;
}

// >>>>>>>>>>>>>>>>>>>>> Provider Terminal <<<<<<<<<<<<<<<<<<<<<<<<<

int Database::authenticateUser(const std::string userID)
{
    // Database logic to get role based on userID;
    // if int = 0: Operator Terminal
    // if int = 1: Manager Terminal
    // if int = 2: Provider Terminal
    // if int = -1: invalid, no terminal, if userID not found
    int role = -1;

    const char *query = "SELECT user_type FROM Users WHERE user_id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return -1;
    }
    // Bind userID to SQL query

    if (sqlite3_bind_text(stmt, 1, userID.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind user ID. \n";
        sqlite3_finalize(stmt);
        return -1;
    }

    // combine or concate the query with userID passed in the argument
    // Final: SELECT user_type FROM Users WHERE user_id = userID;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string userType = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
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

    const char *query = "SELECT service_code, name, fee FROM Services ORDER BY service_code;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return services;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string code = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        double fee = sqlite3_column_double(stmt, 2);

        Service s(code, name, fee);
        services.push_back(s);
    }

    sqlite3_finalize(stmt);
    return services;
}

int Database::validateMembership(const std::string &memberID)
{
    const char *query = "SELECT status FROM Members Where member_id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return -1;
    }

    // Bind the member ID to the query
    if (sqlite3_bind_text(stmt, 1, memberID.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind member ID.\n";
        sqlite3_finalize(stmt);
        return -1;
    }

    int result = -1;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char *statusText = sqlite3_column_text(stmt, 0);
        std::string status = statusText ? reinterpret_cast<const char *>(statusText) : "";

        if (status == "Active")
        {
            std::cout << "[VALIDATED]\n";
            result = 0;
        }
        else if (status == "Suspended")
        {
            std::cout << "[SUSPEND]\n";
            result = 1;
        }
        else
        {
            std::cout << "[INVALID]\n";
            result = -1;
        }
    }
    else
    {
        std::cout << "[INVALID]\n";
        result = -1;
    }

    sqlite3_finalize(stmt);
    return result;
}

Service Database::getService(const std::string serviceCode)
{
    Service s;

    const char *query = "SELECT service_code, name, fee FROM Services WHERE service_code = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return s;
    }

    // Bind the member ID to the query
    if (sqlite3_bind_text(stmt, 1, serviceCode.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind serviceCode.\n";
        sqlite3_finalize(stmt);
        return s;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string s_code = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string s_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        float s_fee = sqlite3_column_double(stmt, 2);
        Service result(s_code, s_name, s_fee);
        sqlite3_finalize(stmt);
        return result;
    }
    else
    {
        sqlite3_finalize(stmt);
        return s;
    }
}

/*
    Record a service into ServiceLog Table
*/
bool Database::serviceLog(const std::string &providerId,
                          const std::string &memberID,
                          const std::string &serviceCode,
                          const std::string &dateOfService,
                          const std::string &timestamp,
                          const std::string &comments)
{
    const char *query = R"SQL( 
        INSERT INTO ServiceLogs (
            date_of_service, timestamp_recorded, provider_id, member_id, service_code, comments
        ) VALUES (?, ?, ?, ?, ?, ?);
    )SQL";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare insert: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, dateOfService.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, timestamp.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, providerId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, memberID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, serviceCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, comments.c_str(), -1, SQLITE_STATIC);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    if (!success)
    {
        std::cerr << "Failed to insert service log: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}

/* Functionalities for Operator Terminal*/

bool Database::update(const std::string &id,
                      const std::string &table,
                      const std::string &address,
                      const std::string &city,
                      const std::string &state,
                      const std::string &zip)
{
    std::string id_column = (table == "Members") ? "member_id" :
                            (table == "Users")   ? "user_id"   : "";

    if (id_column.empty())
    {
        std::cerr << "Invalid table: " << table << "\n";
        return false;
    }

    // Ensure ID is numeric before converting
    if (!std::all_of(id.begin(), id.end(), ::isdigit))
    {
        std::cerr << "Invalid numeric ID: " << id << "\n";
        return false;
    }

    std::string query = "UPDATE " + table +
                        " SET address = ?, city = ?, state = ?, zip_code = ? WHERE " + id_column + " = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare update: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, city.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, state.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, zip.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 5, std::stoll(id));  // Correctly bind numeric ID

    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        int changes = sqlite3_changes(db);
        success = (changes > 0);
        if (!success)
        {
            std::cerr << "No rows updated. Possibly invalid ID: " << id << "\n";
        }
    }
    else
    {
        std::cerr << "Failed to execute update: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}


bool Database::add(const std::string &table,
                   const std::string &name,
                   const std::string &address,
                   const std::string &city,
                   const std::string &state,
                   const std::string &zip)
{
    std::string query;
    sqlite3_stmt* stmt;

    // 1. Members Table (simple insert)
    if (table == "Members") {
        query = R"SQL(
            INSERT INTO Members (name, address, city, state, zip_code, status)
            VALUES (?, ?, ?, ?, ?, 'Active');
        )SQL";

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << " Failed to prepare Members insert: " << sqlite3_errmsg(db) << "\n";
            return false;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, city.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, state.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, zip.c_str(), -1, SQLITE_STATIC);

    }
    // 2. Users Table (specifically for Provider)
    else if (table == "Users") {
        // Step 1: Get next available provider ID
        const char* maxQuery = "SELECT MAX(user_id) FROM Users WHERE user_type = 'Provider';";

        if (sqlite3_prepare_v2(db, maxQuery, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << " Failed to query max provider ID: " << sqlite3_errmsg(db) << "\n";
            return false;
        }

        int newID = 200000001;
        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
            newID = sqlite3_column_int(stmt, 0) + 1;
        }
        sqlite3_finalize(stmt);

        // Step 2: Insert with new provider ID
        query = R"SQL(
            INSERT INTO Users (user_id, name, address, city, state, zip_code, user_type)
            VALUES (?, ?, ?, ?, ?, ?, 'Provider');
        )SQL";

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << " Failed to prepare Provider insert: " << sqlite3_errmsg(db) << "\n";
            return false;
        }

        sqlite3_bind_int(stmt, 1, newID);
        sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, city.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, state.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, zip.c_str(), -1, SQLITE_STATIC);

        std::cout << " Provider added with ID: " << newID << "\n";
    }
    else {
        std::cerr << " Invalid table name: " << table << "\n";
        return false;
    }

    // Final execution
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << " Failed to execute insert: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}


bool Database::deleteUser(const std::string& table, const std::string &id)
{
    std::string id_column = (table == "Members") ? "member_id" :
                            (table == "Users")   ? "user_id"   : "";

    if (id_column.empty()) {
        std::cerr << "Invalid table: " << table << "\n";
        return false;
    }

    if (!std::all_of(id.begin(), id.end(), ::isdigit)) {
        std::cerr << "Invalid numeric ID: " << id << "\n";
        return false;
    }

    std::string query = "DELETE FROM " + table + " WHERE " + id_column + " = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare delete statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int64(stmt, 1, std::stoll(id));

    bool success = (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0);
    sqlite3_finalize(stmt);
    return success;
}



/* Operator Terminal End*/

/* Utilities functions*/

bool Database::searchMember(const std::string memberID)
{
    return search("Members", "member_id", memberID);
}
bool Database::searchProvider(const std::string providerID)
{
    return search("Users", "user_id", providerID);
}

bool Database::search(const std::string &table, const std::string &column, const std::string &id)
{
    // Validate that the ID is numeric
    if (!std::all_of(id.begin(), id.end(), ::isdigit))
    {
        std::cerr << "Invalid numeric ID: " << id << "\n";
        return false;
    }
    std::string query = "SELECT 1 FROM " + table + " WHERE " + column + " = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int64(stmt, 1, std::stoll(id));

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return exists;
}

Member Database::getMember(const std::string memberID)
{
    const char *query = "SELECT * FROM Members WHERE member_id = ?;";
    sqlite3_stmt *stmt;
    Member member;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
        return member;
    sqlite3_bind_text(stmt, 1, memberID.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        member.memberID = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        member.memberName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        member.memberStreetAddress = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        member.memberCity = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        member.memberState = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        member.memberZipCode = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        // member.memberStatus   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
    }

    sqlite3_finalize(stmt);
    return member;
}
Provider Database::getProvider(const std::string providerID)
{
    const char *query = "SELECT * FROM Users WHERE user_id = ?;";
    sqlite3_stmt *stmt;
    Provider provider;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
        return provider;
    sqlite3_bind_text(stmt, 1, providerID.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        provider.providerID = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        provider.providerName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        provider.providerStreetAddress = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        provider.providerCity = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        provider.providerState = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        provider.providerZipCode = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    }

    sqlite3_finalize(stmt);
    return provider;
}
