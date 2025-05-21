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
#include "TerminalSession.h"

class OperatorTerminal: public TerminalSession {
    public:
        OperatorTerminal();
        virtual ~OperatorTerminal();

        // Overwrite parent function
        int     showMenu();
        void    commandHandler(int input);

        // unique function

};

#endif  // OPERATOR_TERMINAL_H