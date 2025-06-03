#include <iostream>
#include <cassert>
#include "TerminalSession.h"
#include "../Utils.h"

TerminalSession::TerminalSession()
{
}

void TerminalSession::runSession()
{
    int input {};
    int numberOfOption {};

    std::cout << "[Login Success]\n";
    std::cout << "---------------\n\n";
    pressEnterToContinue();

    do { 
        do {
            numberOfOption = showMenu();    // Call to child class showMenu, and return the number of menu options
            std::cout << "Please choose your option: " << std::endl;
            std::cout << "> ";
            input = getInput();
            clearScreen();

            if (input < 0 || input > numberOfOption) {
                std::cout << "Invalid option, please choose again\n";
            }
        } while (input < 0 || input > numberOfOption);
        
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

void TerminalSession::getInput(std::string &input, const std::string &prompt) 
{
    std::cout << prompt;
    while (!std::getline(std::cin, input) || input.empty()) {
        std::cin.clear();
        std::cout << "\nInvalid input format. Please try again.\n > ";
    }
}

bool TerminalSession::validateIDFormat(const std::string &ID) const
{
    bool validated {false};

    if (is_digits(userID)) {
        if (ID.length() == 9 || ID.length() == 8) {
            validated = true;
        }
    }
    return validated;
}

bool TerminalSession::is_digits(const std::string &str) const
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

TerminalSession::~TerminalSession()
{}

