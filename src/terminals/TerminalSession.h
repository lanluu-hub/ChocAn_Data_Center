/*
 * Created: May 16, 2025
 *----------------------------- 
 * TerminalSession.h
 * Abstract base class for all user terminal sessions in the ChocAn system.
 *
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */

#ifndef TERMINAL_SESSION_H
#define TERMINAL_SESSION_H
#include <string>

class TerminalSession {
    public:
        TerminalSession();
        virtual ~TerminalSession();
        
        // This function will be inheritance by its child
        void    runSession();
        void    setCurrentUserID(const std::string& ID);

        // virtual function that will be overwrite by its child class
        virtual int     showMenu() =0;
        virtual void    commandHandler(int input) =0;
    protected:
        std::string userID;

        int getInput() const;
};

#endif