#include <iostream>
#include <cassert>
#include "ProviderTerminal.h"

ProviderTerminal::ProviderTerminal() 
{}

ProviderTerminal::~ProviderTerminal()
{
    memberID = {};
    isMemberValidated = false;
}

int ProviderTerminal::showMenu() 
{
    if (isMemberValidated) {
        // show menu option
        // Prompt: Please scan/input memberID to continue. . . 
        // >

    } else {
        // show menu option
        // [VALIDATED]
        // [Provider]
        // 1. bill
        // 2. Request Provider Directory
        // > choice

    }

    assert(isMemberValidated);  // prcondition isMemberValidate == true
    
    return 0;
}

void ProviderTerminal::commandHandler(int input) 
{
    assert(input);
    assert(input > 0 && input < 3);

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
