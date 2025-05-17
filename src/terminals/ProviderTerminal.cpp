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
    // show menu option
    // [VALIDATED]
    // [Provider]
    // 1. bill
    // 2. Request Provider Directory
    // > choice

    assert(isMemberValidated);  // prcondition isMemberValidate == true
    
    return 0;
}

void ProviderTerminal::commandHandler(int input) 
{

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
