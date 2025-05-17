#include <iostream>
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
        numberOfOption = showMenu();
        std::cout << "Please choose your option: " << std::endl;
        std::cout << "> ";
        std::cin >> input;

        while (input < 0 || input > numberOfOption) {
            std::cout << "Invalid option, please choose again: \n> ";
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cin >> input;
        }
        
        
        commandHandler(input);
    } while ( input != 0);
}

TerminalSession::~TerminalSession()
{
}

int TerminalSession::showMenu()
{
    return 0;
}

void TerminalSession::commandHandler(int input)
{
    std::cout << input << std::endl;
}
