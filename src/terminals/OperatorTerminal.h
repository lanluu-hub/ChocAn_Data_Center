/**
 * @file OperatorTerminal.h
 * @brief Defines the OperatorTerminal class for interacting with the ChocAn system as an operator.
 * 
 * The OperatorTerminal class inherits from TerminalSession and provides a menu-driven interface
 * for system operators. It allows management of members and providers, including their creation,
 * update, and deletion.
 * 
 * Features:
 * - Member and provider data management (add, update, delete)
 * - Input validation for addresses and zip codes
 * - Interactive prompts for confirmation and input
 * 
 * @date Created: May 20, 2025
 * @author
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef OPERATOR_TERMINAL_H
#define OPERATOR_TERMINAL_H
#include <string>
#include "TerminalSession.h"
#include "../ChocAnSystem.h"
#include "../models/Member.h"
#include "../models/Provider.h"

/**
 * @class OperatorTerminal
 * @brief Handles operator-specific interactions within the ChocAn system.
 * 
 * This class implements the operator interface, enabling access to management
 * functionality for Member and Provider records in the ChocAn database.
 */
class OperatorTerminal: public TerminalSession {
    public:
        /// @brief Constructs a new OperatorTerminal object.
        OperatorTerminal();

        /// @brief Destructor for the OperatorTerminal object.
        virtual ~OperatorTerminal();

         /**
         * @brief Displays the operator menu.
         * 
         * Presents a list of available administrative options.
         * @return The number of available menu options.
         */
        int     showMenu();

        /**
         * @brief Handles operator command selection.
         * 
         * Routes the user-selected menu input to its corresponding operation.
         * @param input The selected menu option.
         */
        void    commandHandler(int input);

        /// @brief Adds a new member to the ChocAn system.  
        void addMember();

        /// @brief Updates an existing member's address.
        void updateMember();

        /// @brief Deletes a member from the ChocAn system.
        void deleteMember();

        /// @brief Adds a new provider to the ChocAn system.
        void addProvider();

        /// @brief Updates an existing provider's address.
        void updateProvider();

        /// @brief Deletes a provider from the ChocAn system.
        void deleteProvider();

    protected:
        // Helper Fucntion  //

        /**
         * @brief Validates the format of a U.S. zip code.
         * @param str The zip code string (expected 5 digits).
         * @return True if valid, false otherwise.
         */
        bool validateZipcodeFormat(const std::string &str);

        /**
         * @brief Collects address input for a member or provider.
         * 
         * Prompts the operator to enter address components.
         * @param address Reference for street address.
         * @param city Reference for city name.
         * @param state Reference for 2-letter state abbreviation.
         * @param zip Reference for 5-digit zip code.
         * @param role Descriptor used in prompts (e.g., "Member" or "Provider").
         */
        void getAddressInput(std::string &address, std::string &city
                            , std::string &state, std::string &zip, const std::string &role);

        /**
         * @brief Displays a yes/no confirmation prompt to the operator.
         * @param message The message to display.
         * @return True if the operator confirms (Y/y), false otherwise.
         */
        bool confirmPrompt(const std::string &message);
};

#endif  // OPERATOR_TERMINAL_H