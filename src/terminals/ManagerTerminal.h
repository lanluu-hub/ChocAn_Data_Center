/*
 * Created: May 20, 2025
 *----------------------------- 
 * ManagerTerminal.h
 * ManagerTerminal class create a Terminal for Manager to interact with the ChocAn System
 * Manager can request ChocAn system to prints the following report:
 *      Member Report:  [add description]
 *      Provider Report: [add description]
 *      Summary Report: [add description]
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef MANAGER_TERMINAL_H
#define MANAGER_TERMINAL_H
#include "TerminalSession.h"

class ManagerTerminal: public TerminalSession {
    public:
        ManagerTerminal();
        virtual ~ManagerTerminal();

        // Overwrite parent function
        int     showMenu();
        void    commandHandler(int input);

        // unique function

};

#endif  // MANAGER_TERMINAL_H