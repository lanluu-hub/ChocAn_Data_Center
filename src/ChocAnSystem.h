/**
 * @date Created: May 17, 2025
 *----------------------------- 
 * @file ChocAnSystem.h
 * 
 * @brief Defines the ChocAnSystem class, which serves as the centralized control 
 * system for the ChocAn Data Processing System.
 * 
 * The ChocAnSystem class manages member and provider operations, validates inputs, 
 * processes service transactions, and interfaces with the underlying database. 
 * It is implemented as a Singleton to ensure consistent state management across the application.
 * 
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef CHOCAN_SYSTEM_H
#define CHOCAN_SYSTEM_H
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "Database.h"
#include "models/Service.h"
#include "models/Member.h"
#include "models/Provider.h"

class Service;  //  forward declaration

/**
 * @class ChocAnSystem
 * @brief Singleton class providing centralized access to core system operations such as
 *        user authentication, service logging, and management of members and providers.
 */
class ChocAnSystem {
    public:
        /// @brief Deleted copy constructor to prevent duplicate instances.
        ChocAnSystem(const ChocAnSystem& obj) = delete;
        
        /**
         * @brief Returns the Singleton instance of ChocAnSystem.
         * @return Reference to the unique ChocAnSystem instance.
         */ 
        static ChocAnSystem& getInstance();

        // ---------------- Provider Terminal Functions ---------------- //

        /**
         * @brief Authenticates a user ID to determine terminal access.
         * @param userID The user ID to authenticate.
         * @return An integer representing the user's role (e.g., member, provider, operator).
         */
        int authenticateUser (const std::string& userID);

        /**
         * @brief Validates a member’s active status.
         * @param memberID The member ID to validate.
         * @return Status code (e.g., valid, suspended, invalid).
         */
        int validateMembership(std::string& memberID);

        /**
         * @brief Retrieves the service fee associated with a given service code.
         * @param servCode The 6-digit service code.
         * @return The fee associated with the service.
         */
        float getServiceFee(const std::string& servCode);

        std::string getServiceName(const std::string& servCode);
         /**
         * @brief Logs a service transaction to the system database.
         * @param providerID The ID of the provider delivering the service.
         * @param memberID The ID of the member receiving the service.
         * @param serviceCode The code identifying the service performed.
         * @param serviceDate The date the service was provided.
         * @param serviceComment Optional comment regarding the service.
         * @return True if the service log was successfully recorded, false otherwise.
         */
        bool serviceLog(std::string& providerID, std::string& memberID
                        , std::string& serviceCode, std::string& serviceDate, std::string& serviceComment);

        /**
         * @brief Retrieves and displays the provider directory, then saves it to a file.
         *
         * This function fetches a list of services available in the provider directory
         * from the database. It then prints this directory to the console and saves it
         * to a formatted text file for provider reference.
         *
         * The output file path is defined by the constant `PROVIDDER_DIRECTORY_PATH`.
         */
        void getProviderDirectory();
        
        /**
         * @brief Displays the provider directory in a formatted table.
         *
         * This function prints a list of service entries to the console in a human-readable
         * table format. It includes headers for service code, service name, and service fee,
         * along with visual formatting for readability.
         *
         * @param providerDirectory A reference to a vector of Service objects representing
         *        the provider directory to display.
         */
        void displayProviderDirectory(std::vector<Service> & providerDirectory);

        /**
         * @brief Writes the provider directory to a formatted text file.
         *
         * Outputs the list of services to a file at the given file path using a structured
         * layout suitable for provider use. The function returns true if the operation
         * succeeds, or false if the file cannot be opened.
         *
         * @param services A reference to a vector of Service objects to be written.
         * @param filePath A string specifying the file path for saving the directory.
         * @return True if the file was written successfully; false otherwise.
         */
        bool writeProviderDirectoryToFile(std::vector<Service> & services, const std::string & filePath);

        
        // ---------------- Manager Terminal Functions ---------------- //      
        
        /**
         * @brief Generates a detailed report for a specific member.
         * @param memberID The unique ID of the member whose report is to be generated.
         */
        void generateMemberReport(const std::string & memberID);

        // [comments]
        void printReport(const std::string & filePath);
        
        // [comments]
        void generateProviderReport(const std::string & providerID);

        // [comments]
        void generateSummaryReport();

        // ---------------- Operator Terminal - Member Management ---------------- //
        
        /**
         * @brief Adds a new member to the system using individual attribute values.
         * @param newName The full name of the new member.
         * @param newAddr The street address of the new member.
         * @param newCity The city of residence for the new member.
         * @param newState The state of residence for the new member.
         * @param newZip The ZIP code of the new member's address.
         * @return True if the member was successfully added; false otherwise.
         */
        bool addNewMember(const std::string & newName, const std::string & newAddr
                         , const std::string & newCity, const std::string & newState, const std::string & newZip);

        /**
         * @brief Searches for a member by ID.
         * @param memberID The 9-digit member ID to search for.
         * @return True if the member exists, false otherwise.
         */
        bool searchMember(const std::string& memberID);

        /**
         * @brief Retrieves the member object given a member ID.
         * @param memberID The 9-digit member ID.
         * @return A Member object containing the member’s data.
         */
        Member getMember(const std::string & memberID);

        /**
         * @brief Updates the address-related fields for a member.
         * @param memberID The ID of the member to update.
         * @param newAddress Updated street address.
         * @param newCity Updated city name.
         * @param newState Updated state abbreviation.
         * @param newZip Updated 5-digit ZIP code.
         * @return True if the update was successful, false otherwise.
         */
        bool updateMember(const std::string & memberID, const std::string & newAddrss
                         , const std::string & newCty, const std::string & newState, const std::string & newZip);

        /**
         * @brief Deletes a member from the system by ID.
         * @param memberID The 9-digit ID of the member to delete.
         * @return True if deletion was successful, false otherwise.
         */
        bool deleteMember(const std::string& memberID);

        // ---------------- Operator Terminal - Provider Management ---------------- //

        /**
         * @brief Adds a new provider to the system using individual attribute values.
         * @param newName The full name of the new provider.
         * @param newAddr The street address of the new provider.
         * @param newCity The city in which the provider operates.
         * @param newState The state in which the provider operates.
         * @param newZip The ZIP code associated with the provider's address.
         * @return True if the provider was successfully added; false otherwise.
         */
        bool addNewProvider(const std::string & newName, const std::string & newAddr
                         , const std::string & newCity, const std::string & newState, const std::string & newZip);

        /**
         * @brief Searches for a provider by ID.
         * @param providerID The 9-digit provider ID to search for.
         * @return True if the provider exists, false otherwise.
         */
        bool searchProvider(const std::string& ProviderID);

         /**
         * @brief Retrieves a provider object by ID.
         * @param providerID The 9-digit provider ID.
         * @return A Provider object with full provider data.
         */
        Provider getProvider(const std::string & ProviderID);

        /**
         * @brief Updates address-related fields for a provider.
         * @param providerID The ID of the provider to update.
         * @param newAddress Updated street address.
         * @param newCity Updated city name.
         * @param newState Updated state abbreviation.
         * @param newZip Updated 5-digit ZIP code.
         * @return True if the update was successful, false otherwise.
         */
        bool updateProvider(const std::string & providerID, const std::string & newAddrss
                         , const std::string & newCty, const std::string & newState, const std::string & newZip);

         /**
         * @brief Deletes a provider from the system by ID.
         * @param providerID The 9-digit ID of the provider to delete.
         * @return True if deletion was successful, false otherwise.
         */
        bool deleteProvider(const std::string& ProviderID);

    private:
        /// @brief Private constructor for Singleton pattern.
        ChocAnSystem();

        /// @brief Destructor.
        ~ChocAnSystem();

        // ---------------- Helper Function ---------------- //

        /**
         * @brief Parses a date string into a std::chrono::system_clock::time_point.
         * @param dateString The date string to parse (e.g., "2025-05-29").
         * @param format The format string used to interpret the date (e.g., "%Y-%m-%d").
         * @return A time_point representing the parsed date.
         *
         * @note If parsing fails, the resulting time_point may be undefined.
         */
        std::chrono::system_clock::time_point parseDate(const std::string& dateString, const std::string& format);

        /**
         * @brief Converts a given time point into a formatted string representation.
         * @param timePoint The time to be formatted.
         * @param format The desired date/time format (e.g., "%Y-%m-%d").
         * @return A string representation of the formatted date and time.
         */
        std::string dateTime(const std::chrono::system_clock::time_point& timePoint,
                        const std::string& format);
        
        /**
         * @brief Retrieves the current system date in YYYY-MM-DD format.
         *
         * This utility function uses the system clock to obtain the current date 
         * and formats it into a human-readable string.
         *
         * @return A std::string representing today's date in "YYYY-MM-DD" format.
         */
        std::string getCurrentDate();

        /**
         * @brief Formats a file name by removing invalid characters.
         * 
         * This function processes the input string by:
         * - Keeping only alphanumeric characters and underscores.
         * - Replacing spaces with underscores.
         * - Ignoring any other special characters.
         * 
         * This ensures the resulting string is safe for use as a file name on most systems.
         *
         * @param fileName The original file name as a string.
         * @return A formatted string safe for use as a file name.
        */
        std::string formatFileName(const std::string & fileName);

};

#endif
