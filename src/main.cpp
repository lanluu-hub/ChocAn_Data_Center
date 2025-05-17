/*
 *  Created: May 16, 2025
 *-----------------------
 *  main.cpp
 * 
*/
#include <cstdlib>
#include <iostream>
#include <memory>
#include "terminals\TerminalSession.h"

using namespace std;

int
main() {
    do {
    // Welcome message

    // scan userID

    // validateUserIDformat
    
    // created unique_ptr<TerminalSession> 
    // if true: Database::getInstance.authenticateUser(userID) : return an int
        // switch (int): 
        // if int = 0: start Operator Terminal
        // if int = 1: start Manager Terminal
        // if int = 2: start Provider Terminal
        // if int = -1: end session
    // if false: end session

    cout << "Looping" << endl;
    } while (1);

    return EXIT_SUCCESS;
}