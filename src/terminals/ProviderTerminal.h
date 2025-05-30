/*
 * Created: May 16, 2025
 *----------------------------- 
 * ProviderTerminal.h
 * ProviderTerminal class create a Terminal for provider to interact with the ChocAn System
 * Provider can validate Membership status
 * Provider can bill and record a service session
 * Provider can request a Provider Directory
 *
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 * 
 * 
 * -----------------------------
 * Function Documentation:
 *
 * ProviderTerminal()
 *    Constructs a new ProviderTerminal object.
 *
 * ~ProviderTerminal()
 *    Destroys the ProviderTerminal object and resets session state.
 *
 * int showMenu()
 *    Displays the menu based on the session state (validated member or not).
 *    @return The number of available options to display.
 *
 * void commandHandler(int input)
 *    Handles user commands based on the selected menu option.
 *    @param input An integer representing the user's selected command.
 *
 * int validateMembership()
 *    Prompts for and validates a member ID by communicating with ChocAnSystem.
 *    @return An integer status code: 0 (VALIDATED), 1 (SUSPENDED), -1 (INVALID).
 *
 * float billService()
 *    Bills a validated member for a provided service. Collects and validates input,
 *    retrieves service information, and logs the session through ChocAnSystem.
 *    @return The fee associated with the billed service.
 *
 * void requestProviderDirectory()
 *    Requests and outputs the Provider Directory by calling ChocAnSystem.
 *
 * bool validateMemberIdFormat(const std::string& ID)
 *    Validates whether the given member ID is a 9-digit number.
 *    @param ID A string representing the member ID.
 *    @return True if the ID is valid, false otherwise.
 *
 * bool validateServiceCodeFormat(const std::string& servCode)
 *    Validates whether the given service code is a 6-digit number.
 *    @param servCode A string representing the service code.
 *    @return True if the service code is valid, false otherwise.
 *
 * bool validateServiceDateFormat(const std::string& servDate)
 *    Validates whether the given date string follows the MM-DD-YYYY format and is a valid date.
 *    @param servDate A string representing the date of service.
 *    @return True if the date is valid, false otherwise.
 *
 */
#ifndef PROVIDER_TERMINAL_H
#define PROVIDER_TERMINAL_H
#include <string>
#include "TerminalSession.h"
#include "../ChocAnSystem.h"

class ProviderTerminal: public TerminalSession {
    public:
        ProviderTerminal();
        virtual ~ProviderTerminal();

        // Overwrite parent function
        int     showMenu();
        void    commandHandler(int input);

        // unique function
        int     validateMembership();
        float   billService();
        void    requestProviderDirectory();

    protected:
        std::string memberID;                       // stores member id of the validate session
        bool isMemberValidated = false;     // check if member is validated

        // Helper Function
        bool validateServiceCodeFormat(const std::string& servCode);
        bool validateServiceDateFormat(const std::string& servDate);
};

#endif