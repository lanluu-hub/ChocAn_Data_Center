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
#include "models/Member.h"   // for member report
#include "models/Provider.h" // for provider report.

class Service;

class Database
{
public:
    // delete Copy constructor to prevent copy
    Database(const Database &obj) = delete;
    /**
     * @brief Returns the singleton instance of the Database class.
     * @return A reference to the single Database instance.
     *
     * @note Ensures only one shared connection to the SQLite database exists across the application.
     */
    static Database &getInstance();

    /**
     * @brief Authenticates a user based on their ID.
     * @param userID The ID of the user to authenticate.
     * @return An integer status code indicating authentication result.
     */
    int authenticateUser(const std::string userID);

    /**
     * @brief Retrieves the full provider directory from the database.
     * @return A vector of Service objects representing the provider directory.
     */
    std::vector<Service> getProviderDirectory();

    /**
     * @brief Validates a member's ID against the database.
     * @param memberID The ID of the member to validate.
     * @return An integer status code indicating validation result.
     */
    int validateMembership(const std::string &memberID);

    /*
            Operator Terminal Functionalities
        */
    /**
     * @brief Deletes a member from the database.
     * @param memberID The ID of the member to delete.
     * @return True if deletion was successful, false otherwise.
     */
    bool deleteMember(const std::string &memberID);

    /**
     * @brief Deletes a provider from the database.
     * @param providerID The ID of the provider to delete.
     * @return True if deletion was successful, false otherwise.
     */
    bool deleteProvider(const std::string &providerID);

    // Provider Functionalities

    /**
     * @brief Logs a service provided to a member into the ServiceLog table.
     * @param providerId The ID of the provider.
     * @param memberID The ID of the member.
     * @param serviceCode The code of the service provided.
     * @param dateOfService The date the service was provided.
     * @param timeStamp The timestamp of when the service was logged.
     * @param comment Optional comment about the service.
     * @return True if the service was logged successfully, false otherwise.
     */
    bool serviceLog(const std::string &providerId,
                    const std::string &memberID,
                    const std::string &serviceCode,
                    const std::string &dateOfService,
                    const std::string &timeStamp,
                    const std::string &comment);

    /*
        Utilities
    */

    /**
     * @brief Searches for a record in a specific table and column.
     * @param table The name of the table to search.
     * @param column The column to match the ID against.
     * @param id The ID to search for.
     * @return True if the record exists, false otherwise.
     */
    bool search(const std::string &table, const std::string &column, const std::string &id);

    /**
     * @brief Searches for a member by ID.
     * @param memberID The ID of the member.
     * @return True if the member exists, false otherwise.
     */
    bool searchMember(const std::string memberID);

    /**
     * @brief Searches for a provider by ID.
     * @param providerID The ID of the provider.
     * @return True if the provider exists, false otherwise.
     */
    bool searchProvider(const std::string providerID);

    /**
     * @brief Adds a new user to the specified table.
     * @param table The table to add the user to ("members", "providers", etc.).
     * @param name The name of the user.
     * @param address The address of the user.
     * @param city The city of the user.
     * @param state The state of the user.
     * @param zip The ZIP code of the user.
     * @return True if the user was added successfully, false otherwise.
     */
    bool add(const std::string &table,
             const std::string &name,
             const std::string &address,
             const std::string &city,
             const std::string &state,
             const std::string &zip);

    /**
     * @brief Updates a user's address information in the database.
     * @param id The ID of the user.
     * @param table The table to update ("members", "providers", etc.).
     * @param address The new address.
     * @param city The new city.
     * @param state The new state.
     * @param zip The new ZIP code.
     * @return True if the update was successful, false otherwise.
     */
    bool update(const std::string &id,
                const std::string &table,
                const std::string &address,
                const std::string &city,
                const std::string &state,
                const std::string &zip);

    /**
     * @brief Deletes a user from the specified table.
     * @param table The table to delete the user from.
     * @param id The ID of the user to delete.
     * @return True if the user was deleted successfully, false otherwise.
     */
    bool deleteUser(const std::string &table, const std::string &id);

    /**
     * @brief Retrieves a Service object by its service code.
     * @param serviceCode The code of the service.
     * @return A Service object corresponding to the given code.
     */
    Service getService(const std::string serviceCode);

    /**
     * @brief Retrieves a Member object by their ID.
     * @param memberID The ID of the member.
     * @return A Member object corresponding to the given ID.
     */
    Member getMember(const std::string memberID);

    /**
     * @brief Retrieves a Provider object by their ID.
     * @param providerID The ID of the provider.
     * @return A Provider object corresponding to the given ID.
     */
    Provider getProvider(const std::string providerID);

    /*
        Manager Terminal
    */

    /**
     * @brief Generates a report for a specific member.
     * @param memberID The ID of the member.
     * @param bestDate The date to use for the report (e.g., current date).
     * @param filePath Output parameter to store the path of the generated report file.
     */
    void generateMemberReport(const std::string memberID, const std::string bestDate, std::string &filePath);

    /**
     * @brief Generates a report for a specific provider.
     * @param providerID The ID of the provider.
     * @param bestDate The date to use for the report (e.g., current date).
     * @param filePath Output parameter to store the path of the generated report file.
     */
    void generateProviderReport(const std::string providerID, const std::string bestDate, std::string &filePath);

    /**
     * @brief Generates a weekly summary report of all providers.
     *
     * This function aggregates the number of consultations and total service fees
     * for each provider who has submitted service logs within the last 7 days from
     * the specified cutoff date. It also computes total metrics across all providers.
     *
     * @param bestDate The lower-bound date (YYYY-MM-DD) for including service logs.
     *                   Typically set to 7 days before the current date.
     * @param filePath The output file path (e.g., reports/summary/SummaryReport_<date>.txt)
     *                 where the summary report will be written.
     */
    void generateSummaryReport(const std::string bestDate, const std::string &filePath);

private:
    Database();
    ~Database();

    sqlite3 *db;

    // Helper function
    bool OpenConnection();
    void CloseConnection();
};

#endif // DATABASE_H