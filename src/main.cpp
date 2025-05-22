/*
 *  Created: May 16, 2025
 *-----------------------
 *  main.cpp
 * 
*/
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <memory>
#include "ChocAnSystem.h"
#include "Database.h"
#include "terminals/TerminalSession.h"
#include "terminals/ProviderTerminal.h"
#include "terminals/ManagerTerminal.h"
#include "terminals/OperatorTerminal.h"
#include "models/Member.h"
#include "models/Provider.h"
#include "models/Service.h"

using namespace std;

// Prototype

/**
 * Displays the introductory message for the CHOCAN Data Processing System.
 *
 * This function outputs a welcome message to the console.
 * It does not take any parameters or return any values.
 */
void intro();

/**
 * Prompts the user for input and stores the result in the provided variable.
 *
 * @tparam T The type of the input variable.
 * @param input A reference to the variable where the user input will be stored.
 * @param prompt An optional string that specifies the prompt message. Defaults to "Enter a value:".
 */
template <typename T>
void getInput(T &input, const string &prompt = "Enter a value: ");

/**
 * Validates whether a user ID consists only of digits and is 8 or 9 characters long.
 *
 * @param userID A string representing the user ID to validate.
 * @return True if the user ID is numeric and has a length of 8 or 9; otherwise, false.
 */
bool validateUserIdFormat(const string userID);

/**
 * Checks if a given string consists only of digit characters.
 *
 * @param str A reference to the string to check.
 * @return True if the string contains only digits; otherwise, false.
 */
bool is_digits(const string &str);

int
main() {
    int loop{};

    do {
        string userID {};
       
        // Welcome message
        intro();

        // scan userID
        getInput(userID, "Please enter userID:\n > ");

        // validateUserIDformat
        if (validateUserIdFormat(userID)) {
            int role {};
            // Authenticate UserID, return the role (int)
            role = ChocAnSystem::getInstance().authenticateUser(userID);

            // created unique_ptr<TerminalSession> 
            unique_ptr<TerminalSession> session {};

            // determine which Terminal to start
            switch (role) {
            case 0: // OperatorTerminal 
                session = make_unique<OperatorTerminal>();
                // check for session == nullptr;
                if (session == nullptr) {
                    cerr << "Error: cannot start Operator Terminal!" << endl;
                    return EXIT_FAILURE;
                }
                break;
            
            case 1: // ManagerTerminal
                session = make_unique<ManagerTerminal>();
                // check for session == nullptr;
                if (session == nullptr) {
                    cerr << "Error: cannot start Manager Terminal!" << endl;
                    return EXIT_FAILURE;
                }
                break;

            case 2: // ProviderTerminal
                session = make_unique<ProviderTerminal>();
                // check for session == nullptr;
                if (session == nullptr) {
                    cerr << "Error: cannot start Manager Terminal!" << endl;
                    return EXIT_FAILURE;
                }

                break;

            case (-1):
                cout << "Invalid UserID, no assigned terminal for this role!" << endl;
                break;

            default: // other case
                cerr << "Error: undefined userID cases. End Terminal!" << endl;
                return EXIT_FAILURE;
            }
               
            if (role != (-1)) {
                session->setCurrentUserID(userID);
                session->runSession();
            }
            
            // if true: ChocAnSystem::getInstance.authenticateUser(userID) : return an int
                // switch (int): 
                // if int = 0: start Operator Terminal
                // if int = 1: start Manager Terminal
                // if int = 2: start Provider Terminal
                //      
                //      auto session = make_unique<ProviderTerminal>();
                //      int memberStatus = session->validateMember()
                //      {
                //          if memberStatus = 0: output [VALIDATED] and continue to menu
                //          if memberStatus = 1: output [SUSPEND] if member id is corrected but balance is due -> end session
                //          if memberStatus = -1: output [INVALID] if member id is not correct -> end session
                //      }
                // if int = -1: end session
                // } end switch case
                //
                // session->setCurrentUserID(userID)   // this will be the ProviderID needed for the report
                // session-> runSession() : This will run the main terminal of the correct role
            // if false: end session
            cout << "Session End. . . " << endl;
            loop++;
        } else {
            cerr << "Error: invalid userID!" <<endl;
        }
        cout << endl;
    } while (loop < 5);

    return EXIT_SUCCESS;
}

// ------------------------------------------------ //
/////// Function Defination ////////
void intro()
{
    cout << "\n\t\tCHOCAN DATA PROCESSING SYSTEM" << endl; 
}

template <typename T>
void getInput(T &input, const string &prompt)
{
    cout << prompt;
    //cin >> input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(1024, '\n');

        cout << "Invalid input format. please try again.\n > ";
    }
}

bool validateUserIdFormat(const string userID)
{
    bool validated {false};

    if (is_digits(userID)) {
        if (userID.length() == 8 || userID.length() == 9) {
            validated = true;
        }
    }

    return validated;
}

bool is_digits(const string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

