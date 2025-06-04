
#include <sqlite3.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

#include <filesystem>
namespace fs = std::filesystem;

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
    std::string id_column = (table == "Members") ? "member_id" : (table == "Users") ? "user_id"
                                                                                    : "";

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
    sqlite3_bind_int64(stmt, 5, std::stoll(id)); // Correctly bind numeric ID

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
    sqlite3_stmt *stmt;

    // 1. Members Table (simple insert)
    if (table == "Members")
    {
        query = R"SQL(
            INSERT INTO Members (name, address, city, state, zip_code, status)
            VALUES (?, ?, ?, ?, ?, 'Active');
        )SQL";

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            std::cerr << " Failed to prepare Members insert: " << sqlite3_errmsg(db) << "\n";
            return false;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, city.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, state.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, zip.c_str(), -1, SQLITE_STATIC);

        /*
            int memberID = 0;
            std::string m_maxQuery = "SELECT MAX(member_id) FROM Members;";

            if (sqlite3_prepare_v2(db, m_maxQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                std::cerr << " Failed to query max member ID: " << sqlite3_errmsg(db) << "\n";
                return false;
            }

            if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_type(stmt, 0) != SQLITE_NULL)
            {
                memberID = sqlite3_column_int(stmt, 0) + 1;
            }
            std::cout << "Member added with ID: " << memberID << "\n";
        */
    }

    // 2. Users Table (specifically for Provider)
    else if (table == "Users")
    {
        // Step 1: Get next available provider ID
        const char *maxQuery = "SELECT MAX(user_id) FROM Users WHERE user_type = 'Provider';";

        if (sqlite3_prepare_v2(db, maxQuery, -1, &stmt, nullptr) != SQLITE_OK)
        {
            std::cerr << " Failed to query max provider ID: " << sqlite3_errmsg(db) << "\n";
            return false;
        }

        int newID = 200000001;
        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_type(stmt, 0) != SQLITE_NULL)
        {
            newID = sqlite3_column_int(stmt, 0) + 1;
        }
        sqlite3_finalize(stmt);

        // Step 2: Insert with new provider ID
        query = R"SQL(
            INSERT INTO Users (user_id, name, address, city, state, zip_code, user_type)
            VALUES (?, ?, ?, ?, ?, ?, 'Provider');
        )SQL";

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            std::cerr << " Failed to prepare Provider insert: " << sqlite3_errmsg(db) << "\n";
            return false;
        }

        sqlite3_bind_int(stmt, 1, newID);
        sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, city.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, state.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, zip.c_str(), -1, SQLITE_STATIC);

        std::cout << "Provider added with ID: " << newID << "\n";
    }
    else
    {
        std::cerr << " Invalid table name: " << table << "\n";
        return false;
    }

    // Final execution
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success)
    {
        std::cerr << " Failed to execute insert: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}

/* Deleting User by ID */

bool Database::deleteUser(const std::string &table, const std::string &id)
{
    std::string id_column = (table == "Members") ? "member_id" : (table == "Users") ? "user_id"
                                                                                    : "";

    if (id_column.empty())
    {
        std::cerr << "Invalid table: " << table << "\n";
        return false;
    }

    if (!std::all_of(id.begin(), id.end(), ::isdigit))
    {
        std::cerr << "Invalid numeric ID: " << id << "\n";
        return false;
    }

    std::string query = "DELETE FROM " + table + " WHERE " + id_column + " = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare delete statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int64(stmt, 1, std::stoll(id));

    bool success = (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0);
    sqlite3_finalize(stmt);
    return success;
}

/* Operator Terminal End*/

/* Manager Terminal */

void Database::generateMemberReport(const std::string memberID, const std::string bestDate, std::string &filePath)
{
    Member member = getMember(memberID);
    if (member.memberID.empty())
    {
        std::cerr << "Member not found.\n";
        return;
    }

    std::ostringstream report;
    report << "[Member Report]\n";
    report << "Member Name   : " << member.memberName << "\n";
    report << "Member Number : " << member.memberID << "\n";
    report << "Street Address: " << member.memberStreetAddress << "\n";
    report << "City          : " << member.memberCity << "\n";
    report << "State         : " << member.memberState << "\n";
    report << "Zip Code      : " << member.memberZipCode << "\n\n";
    report << "Services Received:\n";
    report << "----------------------------------------\n";

    // Using Member Report View
    const char *query = R"SQL(
        SELECT DateOfService, ProviderName, ServiceName
        FROM MemberReportView
        WHERE ID = ? AND DateOfService >=?
        ORDER BY DateOfService;
    )SQL";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare member report query: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind as integer for member_id
    sqlite3_bind_int(stmt, 1, std::stoi(memberID));
    sqlite3_bind_text(stmt, 2, bestDate.c_str(), -1, SQLITE_STATIC);

    bool hasServices = false;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        hasServices = true;
        std::string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string providerName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string serviceName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        report << "Date of Service : " << date << "\n";
        report << "Provider Name   : " << providerName << "\n";
        report << "Service Name    : " << serviceName << "\n\n";
    }

    if (!hasServices)
    {
        report << "No services found for this member.\n";
    }

    sqlite3_finalize(stmt);

    std::ofstream outFile(filePath);
    if (!outFile)
    {
        std::cerr << "Failed to open report file.\n";
        return;
    }

    outFile << report.str();
    outFile.close();
}

void Database::generateProviderReport(const std::string providerID, const std::string bestDate, std::string &filePath)
{
    Provider provider = getProvider(providerID);
    if (provider.providerID.empty())
    {
        std::cerr << "Provider not found.\n";
        return;
    }

    std::ostringstream report;
    report << "[Provider Report]\n";
    report << "Provider Name   : " << provider.providerName << "\n";
    report << "Provider Number : " << provider.providerID << "\n";
    report << "Street Address  : " << provider.providerStreetAddress << "\n";
    report << "City            : " << provider.providerCity << "\n";
    report << "State           : " << provider.providerState << "\n";
    report << "Zip Code        : " << provider.providerZipCode << "\n\n";
    report << "Services Provided:\n";
    report << "----------------------------------------\n";

    // Convert bestDate from YYYY-MM-DD to MM-DD-YYYY format if needed
    std::string dbDate = bestDate; // or convert format if necessary

    // Use your exact ProviderReportView
    const char *query = R"SQL(
        SELECT DateOfService, 
               TimeStamp, 
               MemberName, 
               MemberID, 
               ServiceCode, 
               ServiceFee
        FROM ProviderReportView
        WHERE ProviderID = ? AND DateOfService >= ?

        ORDER BY DateOfService;
    )SQL";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare provider report query: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Bind as integer for provider_id
    sqlite3_bind_int(stmt, 1, std::stoi(providerID));
    sqlite3_bind_text(stmt, 2, dbDate.c_str(), -1, SQLITE_STATIC);

    int totalConsultations = 0;
    double totalFee = 0.0;
    bool hasServices = false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        hasServices = true;
        std::string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string timestamp = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string memberName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string memberID = std::to_string(sqlite3_column_int(stmt, 3));
        std::string serviceCode = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        double fee = sqlite3_column_double(stmt, 5);

        report << "Date of Service   : " << date << "\n";
        report << "Record Timestamp  : " << timestamp << "\n";
        report << "Member Name       : " << memberName << "\n";
        report << "Member Number     : " << memberID << "\n";
        report << "Service Code      : " << serviceCode << "\n";
        report << "Fee               : $" << std::fixed << std::setprecision(2) << fee << "\n\n";

        totalConsultations++;
        totalFee += fee;
    }

    sqlite3_finalize(stmt);

    if (!hasServices)
    {
        report << "No services found for this provider.\n";
    }

    report << "----------------------------------------\n";
    report << "Total Consultations : " << totalConsultations << "\n";
    report << "Total Fee           : $" << std::fixed << std::setprecision(2) << totalFee << "\n";

    std::ofstream outFile(filePath);
    if (!outFile)
    {
        std::cerr << "Failed to open report file: " << filePath << "\n";
        return;
    }

    outFile << report.str();
    outFile.close();
}

void Database::generateSummaryReport(const std::string bestDate, const std::string &filePath)
{
    // Create parent directories if they don't exist
    // fs::create_directories(fs::path(filePath).parent_path());

    std::ofstream out(filePath);
    if (!out.is_open())
    {
        std::cerr << "Failed to open summary report file: " << filePath << "\n";
        return;
    }

    out << "[Summary Report]\n\n";
    out << "Provider Name         | Consultations | Total Fee\n";
    out << "--------------------------------------------------\n";


    // Using your exact SummaryReportView
    const char* query = R"SQL(
        SELECT
            ProviderName,
            COUNT(NumConsultations),
            SUM(TotalFee)
        FROM SummaryReportView
        WHERE DateOfService >= ?
        --AND DateOfService < ?
        GROUP BY ProviderName
        ORDER BY ProviderName
    )SQL";
    
    /*
    const char *query = R"SQL(
        SELECT
            u.name AS ProviderName,
            --u.user_id AS ProviderID,
            COUNT(s.service_code) AS NumConsultations,
            SUM(sv.fee) AS TotalFee
            --s.date_of_service AS DateOfService
            --s.date_of_service) AS LastServiceDate
            FROM ServiceLogs s
                JOIN Users u ON s.provider_id = u.user_id
                JOIN Services sv ON s.service_code = sv.service_code
            WHERE s.date_of_service >= ?
            GROUP BY u.user_id;
    )SQL";
    */
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Query preparation error: " << sqlite3_errmsg(db) << "\n";
        out.close();
        return;
    }

    sqlite3_bind_text(stmt, 1, bestDate.c_str(), -1, SQLITE_STATIC);

    int totalProviders = 0;
    int totalConsults = 0;
    double totalFees = 0.0;
    bool hasData = false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        hasData = true;
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        int consults = sqlite3_column_int(stmt, 1);
        double fee = sqlite3_column_double(stmt, 2);

        out << std::left << std::setw(22) << name
            << "| " << std::setw(14) << consults
            << "| $" << std::fixed << std::setprecision(2) << fee << "\n";

        totalProviders++;
        totalConsults += consults;
        totalFees += fee;
    }

    sqlite3_finalize(stmt);

    if (!hasData)
    {
        out << "No provider data found for the reporting period.\n";
    }

    out << "--------------------------------------------------\n";
    out << "Total Providers       : " << totalProviders << "\n";
    out << "Total Consultations   : " << totalConsults << "\n";
    out << "Total Fees            : $" << std::fixed << std::setprecision(2) << totalFees << "\n";

    out.close();
}
/* Manager Terminal End */

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
