#include <iostream>
#include <cassert>
#include "ManagerTerminal.h"

using namespace std;

ManagerTerminal::ManagerTerminal()
{}

ManagerTerminal::~ManagerTerminal()
{}

int ManagerTerminal::showMenu() 
{
    // show menu option
    cout << "[Manager Terminal]" << endl;
    cout << "Possible Operatrion: " << endl;
    cout << "/-------------------------\\" << endl;
    cout << "|  1. Print Member Report" << endl;
    cout << "|  2. Print Provider Report" << endl;
    cout << "|  3. Print Summary Report" << endl;
    cout << "|  0. End Session" << endl;
    cout << "\\_________________________/" << endl;
    
    return 0;
}

void ManagerTerminal::commandHandler(int input) 
{

}