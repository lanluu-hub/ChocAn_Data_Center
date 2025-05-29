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

    std::cout << "\nLogin Success\n" << std::endl;
    
    do { 
        numberOfOption = showMenu();    // Call to child class showMenu, and return the number of menu options
        std::cout << "Please choose your option: " << std::endl;
        std::cout << "> ";
        input = getInput();

        while (input < 0 || input > numberOfOption) {       // validate the input of user
            std::cout << "Invalid option, please choose again: \n> ";
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            input = getInput();
        }
        
        commandHandler(input);
    } while (input != 0);
}

void TerminalSession::setCurrentUserID(const std::string& ID)
{
    userID = ID;
}

int TerminalSession::getInput() const
{
    int input {};

    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');

        std::cout << "Please enter a valid input option. [0, 1, 2, ...]" << std::endl;
        std::cout << "> ";
    }
    std::cin.ignore(1024, '\n');
    return input;
}

TerminalSession::~TerminalSession()
{}
