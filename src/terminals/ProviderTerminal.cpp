#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <cassert>
#include "ProviderTerminal.h"
#include "../Utils.h"

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

    cout << "[Provider Terminal]" << endl;
    if (!isMemberValidated) {
        // show menu option
        cout << "[NOT VALIDATED]" << endl;
        cout << "/--------------------" << endl;
        cout << "|  1. Start new Service (validateMembership)" << endl;
        numOfOption = 1;
    } else {
        // show menu option
        cout << "[VALIDATED]" << endl;
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
            exit(EXIT_FAILURE);
            break;
        }
    }
}

int ProviderTerminal::validateMembership()
{
    int membershipStatus {-1};
    bool isIdValidate {false};
    string ID {};

    cout << "[Validate Membership System]\n";
    cout << "----------------------------\n";

    do {

        getInput(ID, "\nPlease Scan/key-in member id card number to continues. . .\n > ");
        clearScreen();

        if (!(isIdValidate = validateIDFormat(ID)))
        {
            cout << "Invalid Member ID format (9-digits ID), please try again." << endl;
        }
    } while (!isIdValidate);

    membershipStatus = ChocAnSystem::getInstance().validateMembership(ID);
    
    switch (membershipStatus)
    {
    case 0: // VALIDATED
        cout << "\nMember Status: [VALIDATED]" << endl;
        isMemberValidated = true;
        memberID = ID;
        pressEnterToContinue();
        break;

    case 1:
        cout << "\nMember Status: [SUSPEND]" << endl;
        pressEnterToContinue();
        break;

    case (-1):
        cout << "\nMember Status: [INVALID]" << endl;
        pressEnterToContinue();
        break;

    default:
        cerr << "\nError: Unexpect case encounter!" << __FILE__ << __LINE__ << endl;
        pressEnterToContinue();
        break;
    }

    return membershipStatus;
}

float ProviderTerminal::billService()
{
    cout << "[Bill Services System]" << endl;

    string ID{"000000000"};
    string servCode {};
    string servDate {};
    string servComment{};
    string inputLog = "";
    float fee {};
    char userConfirm {};
    bool isIdValid {false};
    bool isServCodeValid {false};
    bool isDateValid{false};

    // re-enter member id
    do {
        getInput(ID, "\nEnter Member ID:\n > ");

        if (!(isIdValid = validateIDFormat(ID)))
        {
            clearScreen();
            cout << "Invalid Member ID format (9-digits ID), please try again." << endl;
        } else if (ID != memberID && ID != ("000000000"))
        {
            clearScreen();
            cout << "Member ID does not match current session member ID." << endl;
        }
    } while (!(isIdValid) || ID != memberID);

    if (ID == memberID) {
        cout << "\nMember status: VALIDATED" << endl;
    }

    inputLog = "Enter Member ID:\n > " + ID + "\n\n";
    inputLog += "Member status: VALIDATED\n\n";

    // End member id //

    // Enter Service Code, and confirmation //
    do {
        userConfirm = 'N';

        // get Service Code
        do {
            getInput(servCode, "\nEnter Service Code:\n > ");

            if (!(isServCodeValid = validateServiceCodeFormat(servCode))) {
                clearScreen();
                cout << "Invalid Service code, please try again (6-digits code)" << endl;
                cout << inputLog;
            }
        } while (!isServCodeValid);

        // Get Service Fee
        fee = ChocAnSystem::getInstance().getServiceFee(servCode);
        cin >> userConfirm;
        cin.ignore(1024, '\n');
        //clearScreen();
        //cout << inputLog;
    } while (toupper(userConfirm) != 'Y');

    string serviceName = ChocAnSystem::getInstance().getServiceName(servCode);
    ostringstream roundedFee;
    roundedFee << fixed << setprecision(2) << fee;
    inputLog += "Enter Service Code:\n > " + servCode + "\n\n";
    inputLog += "Service Name: " + serviceName + "\n";
    inputLog += "Service Fee: $" + roundedFee.str() + "\n";
    inputLog += "Is this correct? (Y/N)\n > " + string(1, toupper(userConfirm)) + "\n\n";
    // End Service code //
   
    // get Service day
    do {
        getInput(servDate, "\nEnter Date of Service (MM-DD-YYYY):\n > ");
        
        if (!(isDateValid = validateServiceDateFormat(servDate))) {
            clearScreen();
            cout << "Invalid Service Date, Please try again (MM-DD-YYYY)" << endl;
            cout << inputLog;
        }
    } while (!isDateValid);
    // End Service day //

    // Provider Comment //
    cout << "\nEnter Comment here(100 Words - Optional):\n > ";
    getline(cin, servComment);
    if (servComment.size() > 100) {
        servComment = servComment.substr(0, 100);
    }

    if (ChocAnSystem::getInstance().serviceLog(userID, memberID, servCode, servDate, servComment)) {
        // If true: output "Service Logged Successfully!"
        cout << "\nService Logged Successfully" << endl;
    } else {
        // If false: output "Error: Failed to Log current service!"
        cerr << "\nFailed to log current service" << endl;
        //exit(EXIT_FAILURE);
    }

    cout << "\nAmount of Fee: " << fee << endl;
    pressEnterToContinue();
    // End current session with member ID
    // clear memberID
    memberID.clear();

    // set isMemberValidated = false
    isMemberValidated = false;
    return fee;
}

void ProviderTerminal::requestProviderDirectory()
{
    clearScreen();
    cout << "\n[Request Provider Directory System]";
    ChocAnSystem::getInstance().getProviderDirectory();
    pressEnterToContinue();
}


////////// HELPER FUNCTION //////////   

bool ProviderTerminal::validateServiceCodeFormat(const std::string& servCode)
{
    bool validated {false};

    if (is_digits(servCode)) {
        if (servCode.length() == 6) {
            validated = true;
        }
    }
    return validated;
}

bool ProviderTerminal::validateServiceDateFormat(const std::string &servDate)
{
    // Regular expression to match MM/DD/YYYY format
    regex datePattern(R"(^\d{2}-\d{2}-\d{4}$)");
    
    if (!std::regex_match(servDate, datePattern)) {
        return false; // Doesn't match the format
    }

    // Extract month, day, and year
    string str_month = servDate.substr(0, 2);
    string str_day = servDate.substr(3, 2);
    string str_year = servDate.substr(6, 4);

    if (!is_digits(str_month) 
        || !is_digits(str_day) 
        || !is_digits(str_year)) {
            return false;
    } 

    // Convert to int
    int month = std::stoi(str_month);
    int day = std::stoi(str_day);
    int year = std::stoi(str_year);

    // Check valid ranges for month and day
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Days in each month
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Adjust for leap year
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }

    // Check if the day is valid for the given month
    if (day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}

