#include <iostream>
#include <cassert>
#include "TerminalSession.h"

TerminalSession::TerminalSession()
{
}

void TerminalSession::runSession()
{
    int input {};
    int numberOfOption {};

    std::cout << "Login Success" << std::endl;
    
    do { 
        numberOfOption = showMenu();    // Call to child class showMenu, and return the number of menu options
        std::cout << "Please choose your option: " << std::endl;
        std::cout << "> ";
        std::cin >> input;

        while (input < 0 || input > numberOfOption) {       // validate the input of user
            std::cout << "Invalid option, please choose again: \n> ";
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cin >> input;
        }
        
        commandHandler(input);
    } while (input != 0);
}

void TerminalSession::setCurrentUserID(const int ID)
{
    assert(ID);
    userID = ID;
}

TerminalSession::~TerminalSession()
{}
