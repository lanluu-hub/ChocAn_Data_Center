#include <iostream>
#include <cassert>
#include "ManagerTerminal.h"
#include "../ChocAnSystem.h"
#include "../Utils.h"

using namespace std;

ManagerTerminal::ManagerTerminal()
{}

ManagerTerminal::~ManagerTerminal()
{}

int ManagerTerminal::showMenu() 
{
    int numOfOption {};
    // show menu option
    cout << "[Manager Terminal]" << endl;
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
        pressEnterToContinue();
        break;

    case 2: // Provider Report
        printProviderReport();
        pressEnterToContinue();
        break;

    case 3: // Summary Report
        printSummaryReport();
        pressEnterToContinue();
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
    string  memberID{};
    bool isValidateID {false};

    cout << "\n\t[PRINT MEMBER REPORT]" << endl;
    do {
        getInput(memberID, "Enter member ID:\n > ");

        if (!(isValidateID = validateIDFormat(memberID))) {
            cout << "Invalid Member ID format (9-digit), please try again." << endl;
        }
    } while (!isValidateID);

    ChocAnSystem::getInstance().generateMemberReport(memberID);
}

void ManagerTerminal::printProviderReport()
{
    string  providerID{};
    bool isValidateID {false};

    cout << "\n\t[PRINT PROVIDER REPORT]" << endl;
    do {
        getInput(providerID, "Enter Provider ID:\n > ");

        if (!(isValidateID = validateIDFormat(providerID))) {
            cout << "Invalid Provider ID format (9-digit), please try again." << endl;
        }
    } while (!isValidateID);

    ChocAnSystem::getInstance().generateProviderReport(providerID);
}

void ManagerTerminal::printSummaryReport()
{
    cout << "\n\t[PRINT SUMMARY REPORT]" << endl;

    ChocAnSystem::getInstance().generateSummaryReport();
}

//////////  Helper Function //////////
