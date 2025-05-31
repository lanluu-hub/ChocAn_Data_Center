/**
 * Created: May 16, 2025
 * -------------------------------------
 * @file main.cpp
 *
 * @brief Entry point of the ChocAn Data Processing System.
 * Manages user login, authentication, and terminal routing for different user roles:
 * Operator, Manager, and Provider.
 * 
 * 
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
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

// ===============================
//         FUNCTION HEADERS
// ===============================

/**
 * @brief Displays the introductory message for the CHOCAN Data Processing System.
 */
void intro();

/**
 * @brief Prompts the user for input and stores the result in the provided variable.
 * @tparam T The type of the input variable.
 * @param input A reference to the variable where the user input will be stored.
 * @param prompt An optional string that specifies the prompt message. Defaults to "Enter a value:".
 */
template <typename T>
void getInput(T &input, const string &prompt = "Enter a value: ");

/**
 * @brief Validates whether a user ID consists only of digits and is 8 or 9 characters long.
 * @param userID A string representing the user ID to validate.
 * @return True if the user ID is numeric and valid; otherwise, false.
 */
bool validateUserIdFormat(const string userID);

/**
 * @brief Checks if a given string consists only of digit characters.
 * @param str A reference to the string to check.
 * @return True if the string contains only digits; otherwise, false.
 */
bool is_digits(const string &str);

// ===============================
//         MAIN FUNCTION
// ===============================

/**
 * @brief Main driver for terminal session execution and authentication.
 *
 * Handles userID input, validates the format, authenticates against the ChocAn system,
 * and starts the appropriate terminal session based on the user role.
 *
 * @return EXIT_SUCCESS on successful completion.
 */
int
main() {
    do {
        string userID {};
       
        // Display welcome message
        intro();

        // Request user ID
        getInput(userID, "Please enter userID:\n > ");
        cin.ignore(1024, '\n');

        // Validate user ID format
        if (validateUserIdFormat(userID)) {
            int role {};
            role = ChocAnSystem::getInstance().authenticateUser(userID);

            unique_ptr<TerminalSession> session {};

            // Launch appropriate terminal based on role
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
                exit(EXIT_FAILURE);
            }
               
            // Launch terminal session if role is valid
            if (role != (-1)) {
                session->setCurrentUserID(userID);
                session->runSession();
            }
            
            cout << "Session End. . . " << endl;
        } else {
            cerr << "Error: invalid userID!" <<endl;
        }
        cout << endl;
    } while (1);

    return EXIT_SUCCESS;
}

// ===============================
//         FUNCTION DEFINITIONS
// ===============================

void intro()
{
    cout << "\n\t\tCHOCAN DATA PROCESSING SYSTEM" << endl; 
}

template <typename T>
void getInput(T &input, const string &prompt)
{
    cout << prompt;
    //cin >> input;
    while (!(cin >>input)) {
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

