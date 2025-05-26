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
 */
#ifndef PROVIDER_TERMINAL_H
#define PROVIDER_TERMINAL_H
#include <string>
#include "TerminalSession.h"
#include "..\ChocAnSystem.h"

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
        void getInput(std::string &input, const std::string &prompt = "Enter a value: ");
        bool validateMemberIdFormat(const std::string& ID);
        bool validateServiceCodeFormat(const std::string& servCode);
        bool validateServiceDateFormat(const std::string& servDate);
        bool is_digits(const std::string &str);
};

#endif