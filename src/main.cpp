/*
 *  Created: May 16, 2025
 *-----------------------
 *  main.cpp
 * 
*/
#include <cstdlib>
#include <iostream>
#include <memory>
#include "ChocAnSystem.h"
#include "terminals\TerminalSession.h"
#include "terminals\ProviderTerminal.h"
#include "models\Member.h"
#include "models\Provider.h"
#include "models\Service.h"

using namespace std;

int
main() {
    do {
    // Welcome message

    // scan userID

    // validateUserIDformat
    
    // created unique_ptr<TerminalSession> 
    unique_ptr<TerminalSession> session;

    session = make_unique<ProviderTerminal>();

    // if true: Database::getInstance.authenticateUser(userID) : return an int
        // switch (int): 
        // if int = 0: start Operator Terminal
        // if int = 1: start Manager Terminal
        // if int = 2: start Provider Terminal
        //      
        //      auto session = make_unique<ProviderTerminal>();
        //      session->setCurrentUserID(userID)   // this will be the ProviderID needed for the report
        //      int memberStatus = session->validateMember()
        //      {
        //          if memberStatus = 0: output [VALIDATED] and continue to menu
        //          if memberStatus = 1: output [SUSPEND] if member id is corrected but balance is due -> end session
        //          if memberStatus = -1: output [INVALID] if member id is not correct -> end session
        //      }
        // if int = -1: end session
    // if false: end session

    cout << "Looping" << endl;
    } while (1);

    return EXIT_SUCCESS;
}