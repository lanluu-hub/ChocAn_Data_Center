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
    int numOfOption {};
    // show menu option
    cout << "\n[Manager Terminal]" << endl;
    cout << "Possible Operatrion: " << endl;
    cout << "/--------------------" << endl;
    cout << "|  1. Print Member Report" << endl;
    cout << "|  2. Print Provider Report" << endl;
    cout << "|  3. Print Summary Report" << endl;
    cout << "|  0. End Session" << endl;
    cout << "\\____________________" << endl;
    
    numOfOption = 3;
    return numOfOption;
}

void ManagerTerminal::commandHandler(int input) 
{
    switch (input) {
    case 1: // Member Report
        printMemberReport();
        break;

    case 2: // Provider Report
        printProviderReport();
        break;

    case 3: // Summary Report
        printSummaryReport();
        break;

    case 0: // exit
        break;
    
    default:
        cerr << "\nError: Unexpect case encounter!" << __FILE__ << __LINE__ << endl;
        exit(EXIT_FAILURE);
        break;
    }
}

void ManagerTerminal::printMemberReport()
{
    /*
        Function: printMemberReport()
        1. ManagerTerminal
        Prompt: "Enter Member ID: "
        memberID <- Input
        isValid <- validateFormat(memberID)
        If not isValid:
            Repeat input
        Else:
            Call ChocAnSystem::generateMemberReport(memberID)
        
    */
   cout << "\n\t[PRINT MEMBER REPORT]" << endl;
   cout << "Enter Member ID: \n > ";

}

void ManagerTerminal::printProviderReport()
{
}

void ManagerTerminal::printSummaryReport()
{
}

//////////  Helper Function //////////
