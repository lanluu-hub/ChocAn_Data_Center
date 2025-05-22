#include <iostream>
#include <string>
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
    int numOfOption {};

    cout << "\n[Provider Terminal]" << endl;
    if (!isMemberValidated) {
        // show menu option
        cout << "Possible Operatrion: " << endl;
        cout << "/--------------------" << endl;
        cout << "|  1. Start new Service (validateMembership)" << endl;
        numOfOption = 1;
    } else {
        // show menu option
        cout << "[VALIDATED]" << endl;
        cout << "Possible Operatrion: " << endl;
        cout << "/--------------------" << endl;
        cout << "|  1. End Service and output Bill" << endl;
        cout << "|  2. Request Provider Directory" << endl;
        numOfOption = 2;
    }
    cout << "|  0. End Session" << endl;
    cout << "\\______________________" << endl;
    
    return numOfOption;
}

void ProviderTerminal::commandHandler(int input) 
{
    if(!isMemberValidated) {
        // 1. validate Membership     
        if (input == 1) {
            // call helper function
            validateMembership();
        } else {
            cout << "Invalid Option!" << endl;
        }
    } else {
        // 1. End Service, output bill, save record     
        // 2. request Provider Directory     
        switch (input) {
        case 1:
            billService();
            break;
        case 2:
            requestProviderDirectory();
            break;

        case 0: // exit
            break;
        default:
            cout << "Invalid Option!" << endl;
            break;
        }
    }
}

int ProviderTerminal::validateMembership()
{
    int membershipStatus {-1};
    string ID {};

    do {
        getMemberID(ID, "\nPlease Scan/key-in member id card number to continues. . .\n > ");
    } while (!(validateMemberIdFormat(ID)));

    membershipStatus = ChocAnSystem::getInstance().validateMembership(ID);
    
    switch (membershipStatus)
    {
    case 0: // VALIDATED
        isMemberValidated = true;
        memberID = ID;
        break;

    case 1:

        break;

    default:
        break;
    }

    return membershipStatus;
}

float ProviderTerminal::billService()
{
    return 0.0f;
}

void ProviderTerminal::requestProviderDirectory()
{
    ChocAnSystem::getInstance().getProviderDirectory();
}

void ProviderTerminal::getMemberID(string &input, const string &prompt)
{
    cout << prompt;
    //cin >> input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(1024, '\n');

        cout << "Invalid input format. please try again.\n > ";
    }
}

bool ProviderTerminal::validateMemberIdFormat(const string ID)
{
    bool validated {false};

    if (is_digits(userID)) {
        if (ID.length() == 9) {
            validated = true;
        }
    }

    return validated;
}

bool ProviderTerminal::is_digits(const string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}
