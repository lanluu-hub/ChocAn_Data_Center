/*
 * Created: May 20, 2025
 *----------------------------- 
 * OperatorTerminal.h
 * OperatorTerminal class create a Terminal for Operator to interact with the ChocAn System
 * Operator can run ChocAn system in Interactive mode, to: 
 *      add/update/delete Member
 *      add/update/delete Provider
 * 
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef OPERATOR_TERMINAL_H
#define OPERATOR_TERMINAL_H
#include <string>
#include "TerminalSession.h"
#include "../ChocAnSystem.h"
#include "../models/Member.h"
#include "../models/Provider.h"

class OperatorTerminal: public TerminalSession {
    public:
        OperatorTerminal();
        virtual ~OperatorTerminal();

        // Overwrite parent function
        int     showMenu();
        void    commandHandler(int input);

        // unique function
        void addMember();
        void updateMember();
        void deleteMember();
        void addProvider();
        void updateProvider();
        void deleteProvider();

    protected:
        // Helper Fucntion  //
        void getInput(std::string &input, const std::string &prompt = "Enter a value: ");
        bool validateZipcodeFormat(const std::string &str);
        bool validateIDFormat(const std::string &str);
        bool is_digits(const std::string &str);
};

#endif  // OPERATOR_TERMINAL_H