/**
 * @file ProviderTerminal.h
 * @brief Defines the ProviderTerminal class for interacting with the ChocAn system as a provider.
 * 
 * The ProviderTerminal class inherits from TerminalSession and provides a menu-driven interface
 * for service providers. It allows validation of member status, billing of service sessions, and 
 * retrieval of the Provider Directory.
 * 
 * Features:
 * - Member validation
 * - Service billing and logging
 * - Provider Directory request and output
 * 
 * @date Created: May 16, 2025
 * @author
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef PROVIDER_TERMINAL_H
#define PROVIDER_TERMINAL_H
#include <string>
#include "TerminalSession.h"
#include "../ChocAnSystem.h"

/**
 * @class ProviderTerminal
 * @brief Handles provider-specific interactions within the ChocAn system.
 * 
 * This class implements the provider interface, enabling access to services
 * such as membership validation, service billing, and directory retrieval.
 */
class ProviderTerminal: public TerminalSession {
    public:
        /// @brief Constructs a new ProviderTerminal object.
        ProviderTerminal();

        /// @brief Destructor for the ProviderTerminal object.
        virtual ~ProviderTerminal();

        /**
         * @brief Displays the menu based on session context.
         * 
         * Menu options are tailored depending on whether a member has been validated.
         * @return The number of selectable menu options.
         */
        int     showMenu();

        /**
         * @brief Handles command input from the menu.
         * 
         * Routes selected options to their corresponding functionality.
         * @param input The selected menu option.
         */
        void    commandHandler(int input);

         /**
         * @brief Prompts for and validates a member's ID.
         * 
         * Communicates with the ChocAn system to determine membership status.
         * @return Status code: 0 (Validated), 1 (Suspended), -1 (Invalid).
         */
        int     validateMembership();

        /**
         * @brief Bills a validated member for a service session.
         * 
         * Collects relevant details, confirms service code, and submits a billing record.
         * @return The billed service fee.
         */
        float   billService();


        /**
         * @brief Requests and displays the current Provider Directory.
         * 
         * Retrieves the directory from the ChocAn system and formats it for output.
         */
        void    requestProviderDirectory();

    protected:
        std::string memberID;   // The ID of the validated member.
        bool isMemberValidated = false; // Flag indicating if a member has been successfully validated.

        ////////// Helper Function  //////////

        /**
         * @brief Validates the format of a service code.
         * @param servCode The service code as a string.
         * @return True if the format is valid (6-digit number), false otherwise.
         */
        bool validateServiceCodeFormat(const std::string& servCode);

        /**
         * @brief Validates the format and correctness of a service date.
         * @param servDate The service date as a string (MM-DD-YYYY).
         * @return True if the date is valid, false otherwise.
         */
        bool validateServiceDateFormat(const std::string& servDate);
};

#endif