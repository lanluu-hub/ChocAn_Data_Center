#include <iostream>
#include <cassert>
#include "OperatorTerminal.h"

using namespace std;

OperatorTerminal::OperatorTerminal()
{
}

OperatorTerminal::~OperatorTerminal()
{
}

int OperatorTerminal::showMenu() 
{
    int numOfOption {};

    // show menu option
    cout << "[Operator Terminal]" << endl;
    cout << "Possible Operatrion: " << endl;
    cout << "/--------------------" << endl;
    cout << "|  1. Add Member" << endl;
    cout << "|  2. Update Member" << endl;
    cout << "|  3. Delete Member" << endl;
    cout << "|  4. Add Provider" << endl;
    cout << "|  5. Update Provider" << endl;
    cout << "|  6. Delete Provider" << endl;
    cout << "|  0. End Session" << endl;
    cout << "\\___________________" << endl;
    
    numOfOption = 6;
    return numOfOption;
}

void OperatorTerminal::commandHandler(int input) 
{

}