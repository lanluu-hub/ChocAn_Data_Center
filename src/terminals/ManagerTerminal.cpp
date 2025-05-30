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

        2. ChocAnSystem
        member <- Database::getMemberByID(memberID)
        If member == null:
            Output "Member does not exist"
            return

        Output:
            "Member ID: " + member.ID
            "Member Name: " + member.Name
        Prompt: "Is this the correct member? (Y/N)"
        If input != 'Y':
            Output "Try again with another ID"
            return

        currentDate = getCurrentDate()
        bestDate = currentDate - 7 days
        rawFilename = member.Name + "_" + currentDate
        formattedFilename = sanitizeFileName(rawFilename)
        filePath = MEMBER_REPORT_FOLDER + formattedFilename + ".txt"

        Call Database::generateMemberReport(member, bestDate, filePath)

        3. Database::generateMemberReport(member, bestDate, filePath)
        Open file at filePath
        If file not open:
            Output error and return

        Write header:
            Member info (name, address, etc.)
            "Services Provided:"

        Execute SQL query:
            SELECT s.ServiceDate, p.Name, sv.Name
            FROM ServiceLog s
            JOIN Provider p ON s.ProviderID = p.ID
            JOIN Service sv ON s.ServiceCode = sv.Code
            WHERE s.MemberID = member.ID AND s.ServiceDate >= bestDate

        For each row in result:
            Write:
                Provider Name
                Service Name
                Service Date

        Close file
        Return
    */

}

void ManagerTerminal::printProviderReport()
{
}

void ManagerTerminal::printSummaryReport()
{
}

//////////  Helper Function //////////
