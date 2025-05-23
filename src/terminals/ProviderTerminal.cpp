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
        } else if (input != 0) {
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
            cerr << "\nError: Unexpect case encounter!" << __FILE__ << __LINE__ << endl;
            break;
        }
    }
}

int ProviderTerminal::validateMembership()
{
    int membershipStatus {-1};
    string ID {};

    cout << "\n[Validate Membership System]" << endl;

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
        cout << "\n[SUSPEND]" << endl;
        break;

    case (-1):
        cout << "\n[INVALID]" << endl;
        break;

    default:
        cerr << "\nError: Unexpect case encounter!" << __FILE__ << __LINE__ << endl;
        break;
    }

    return membershipStatus;
}

float ProviderTerminal::billService()
{
    cout << "\n[Bill Services System]" << endl;

    string ID{"000000000"};

    do {
        getMemberID(ID, "\nPlease Scan/key-in member id card number to continues. . .\n > ");

        if (ID != memberID && ID != ("000000000"))
        {
            cout << "Member ID does not match current session member ID." << endl;
        }
    } while (!(validateMemberIdFormat(ID)) || ID != memberID);

    // Call to ChocAnSystem::getInstance().billService(str memberID); Return a float for fee


    // clear memberID
    memberID.clear();

    // set isMemberValidated = false
    isMemberValidated = false;
    return 0.0f;
}

void ProviderTerminal::requestProviderDirectory()
{
    cout << "\n[Request Provider Directory System]";
    ChocAnSystem::getInstance().getProviderDirectory();
}


////////// HELPER FUNCTION //////////   

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
