#include <iostream>
#include <cassert>
#include "ProviderTerminal.h"

using namespace std;

ProviderTerminal::ProviderTerminal() 
{}

ProviderTerminal::~ProviderTerminal()
{
    memberID = {};
    isMemberValidated = false;
}

int ProviderTerminal::showMenu() 
{
    if (!isMemberValidated) {
        // show menu option
        cout << "[Provider Terminal]" << endl;
        cout << "Possible Operatrion: " << endl;
        cout << "/----------------------\\" << endl;
        cout << "|  1. Start new Service (validateMembership)" << endl;
        cout << "|  0. End Session" << endl;
        cout << "\\______________________/" << endl;
    } else {
        // show menu option
        cout << "[Provider Terminal]" << endl;
        cout << "[VALIDATED]" << endl;
        cout << "Possible Operatrion: " << endl;
        cout << "/--------------------------------\\" << endl;
        cout << "|  1. End Service and output Bill" << endl;
        cout << "|  2. Request Provider Directory" << endl;
        cout << "|  0. End Session" << endl;
        cout << "\\________________________________/" << endl;

    }
    
    return 0;
}

void ProviderTerminal::commandHandler(int input) 
{
    if(!isMemberValidated) {
        // 1. validate Membership     
    } else {
        // 1. End Service, output bill, save record     
        // 2. request Provider Directory     
    }
}

int ProviderTerminal::validateMembership()
{

    return false;
}

float ProviderTerminal::billService()
{
    return 0.0f;
}

void ProviderTerminal::requestProviderDirectory()
{
}
