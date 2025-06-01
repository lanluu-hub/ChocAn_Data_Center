#include <iostream>
#include <cassert>
#include "OperatorTerminal.h"
#include "../ChocAnSystem.h"
#include "../Utils.h"

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
    switch (input) {
    case 1: // Add member
        addMember();
        pressEnterToContinue();
        break;
    
    case 2: // Update member
        updateMember();    
        pressEnterToContinue();
        break;

    case 3: // Delete member
        deleteMember();
        pressEnterToContinue();
        break;

    case 4: // Add Provider
        addProvider();
        pressEnterToContinue();
        break;

    case 5: // Update Provider
        updateProvider();
        pressEnterToContinue();
        break;

    case 6: // Delete Provider
        deleteProvider();
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

void OperatorTerminal::addMember()
{
    string  new_id{}
            , new_name{}
            , new_address{}
            , new_city{}
            , new_state{}
            , new_zip{};
    bool confirm{false};

    cout << "[Add Member]" << endl;

    cout << "\nPlease enter new Member Information" << endl;
    do {
        {   // Scope for user input //
            // member name
            cout << "Enter New Member Name: ";
            getline(cin, new_name);
            if (new_name.length() > 25) {
                new_name = new_name.substr(0, 25);
            }
            
            getAddressInput(new_address, new_city, new_state, new_zip, "Member");
        }   // End of input scope

        clearScreen();

        {   // Confirm block
            cout << "Please confirm if this is the correct information: " << endl;
            cout << "Member Name: " << new_name << endl
                << "Member Adress: " << new_address << endl
                << "Member City: " << new_city << endl
                << "Member State: " << new_state << endl
                << "Member Zipcode: " << new_zip << endl;

            if (!(confirm = confirmPrompt("\nIs this information correct?"))) {
                cout << "\nPlease try again with add new Member" << endl;
                return;
            }
        }
    } while (!confirm); 

    // Called to ChocAn to add new member, a bool is being return, true = successfull, false otherwise
    if (ChocAnSystem::getInstance().addNewMember(new_name, new_address, new_city, new_state, new_zip)) {
        cout << "\nMember added successfully." << endl;
    } else {
        cout << "\nFailed to add new Member." << endl;
    }
    return;
}

void OperatorTerminal::updateMember()
{
    Member memberToUpdate;
    bool confirm {false};
    string memberID{};
    string new_address{}, new_city{}, new_state{}, new_zip {};
    bool isValidID{false};

    cout << "[Update Member]" << endl;

    do {
        getInput(memberID, "\nEnter member ID for update:\n > ");

        if (!(isValidID = validateIDFormat(memberID))) {
            cout << "\nInvalid ID format (9-digit), please try again." << endl;
        }
    } while (!isValidID);

    // check if member exist
    if (!(ChocAnSystem::getInstance().searchMember(memberID))) {
        cerr << "No Member with memberID " << memberID << " exist." << endl;
        return;
    }

    // Actual update input field
    cout << "\nPlease Enter update information here" << endl;
    do {
        {
            // Scope for user input
            getAddressInput(new_address, new_city, new_state, new_zip, "Member");
        } // end of input scope

        {   // Member Information confirmation scope
            cout << "\nPlease make sure the following information is correct: " << endl;
            cout << "MemberID: " << memberID << endl
                << "New Address: " << new_address << endl
                << "New City: " << new_city << endl
                << "New State: " << new_state << endl
                << "New Zipcode: " << new_zip << endl; 

            if (!(confirm = confirmPrompt("\nIs this information correct?"))) {
                cout << "\nPlease try again with new information" << endl;
            }
        }
    } while (!confirm);

    // Call actual update function from chocan
    if (ChocAnSystem::getInstance().updateMember(memberID, new_address, new_city, new_state, new_zip)) {
        cout << "\nMember with MemberID " << memberID << " Updated successfully." << endl;
    } else {
        cout << "\nFailed to Update Member " << memberID << endl;
    }
}

void OperatorTerminal::deleteMember()
{
    string memberID{};
    bool isValidMemberID{false};
   
    cout << "[Delete Member]" << endl;
    do {
        getInput(memberID, "\nEnter member id: ");
        if (!(isValidMemberID = validateIDFormat(memberID))){
            cout << "Invalid member id format (9-digit), please try again." << endl;
        }
    } while(!isValidMemberID);

    // Check if memberID is in database
    if (!(ChocAnSystem::getInstance().searchMember(memberID))) {
        cout << "\nCannot delete member: No such member exist" << endl;
    } else {
        if ((ChocAnSystem::getInstance().deleteMember(memberID))) {
            cout << "\nMember is deleted successfully" << endl;
        } else {
            cout << "\nCannot deleted Member with MemberID: " << memberID << endl;
        }
    }
}

void OperatorTerminal::addProvider()
{
    string  new_id{}
          , new_name{}
          , new_address{}
          , new_city{}
          , new_state{}
          , new_zip{};
    bool confirm {false};

    cout << "[Add Provider]" << endl;
        
    cout << "\nPlease enter new Provider Information" << endl;

    do {
        {   // Scope for user input //
            // Provider name
            cout << "Enter New Provider Name: ";
            getline(cin, new_name);
            if (new_name.length() > 25) {
                new_name = new_name.substr(0, 25);
            }
            
            // get Provider Address
            getAddressInput(new_address, new_city, new_state, new_zip, "Provider");
        }

        {   // Confirm block
            cout << "\nPlease confirm if this is the correct information: " << endl;
            cout << "Provider Name: " << new_name << endl
                << "Provider Adress: " << new_address << endl
                << "Provider City: " << new_city << endl
                << "Provider State: " << new_state << endl
                << "Provider Zipcode: " << new_zip << endl;

            if (!(confirm = confirmPrompt("\nIs this information correct?"))) {
                cout << "\nPlease try again with new information" << endl;
            }
        }
    } while (!confirm); 


    // Call to ChocAnSystem to add the new provider
    if (ChocAnSystem::getInstance().addNewProvider(new_name, new_address, new_city, new_state, new_zip)) {
        cout << "\nProvider added successfully." << endl;
    } else {
        cout << "\nFailed to add new Provider." << endl;
    }
}

void OperatorTerminal::updateProvider()
{
    Provider providerToUpdate;
    bool confirm {false};
    string providerID{};
    string new_address{}, new_city{}, new_state{}, new_zip {};
    bool isValidID{false};

    cout << "[Update Provider]" << endl;

    do {
        getInput(providerID, "\nEnter provider Id for update:\n > ");
        if (!(isValidID = validateIDFormat(providerID))) {
            cout << "\nInvalid ID format (9-digit), please try again." << endl;
        } 
    } while (!isValidID);
    
    // check if provider exist
    if (!(ChocAnSystem::getInstance().searchProvider(providerID))) {
        cerr << "No Provider with providerID " << providerID << " exist." << endl;
        return;
    }

    cout << "\nPlease Enter update information here" << endl;

    do {
        {
            cout << "\nPlease Enter update information here" << endl;
            // input scope, get Provider input
            getAddressInput(new_address, new_city, new_state, new_zip, "Provider");
        }

        {   // Member Information confirmation scope
            cout << "\nPlease make sure the following information is correct: " << endl;
            cout << "ProviderID: " << providerID << endl
                << "New Address: " << new_address << endl
                << "New City: " << new_city << endl
                << "New State: " << new_state << endl
                << "New Zipcode: " << new_zip << endl; 

            if (!(confirm = confirmPrompt("\nIs this information correct?"))) {
                cout << "\nPlease try again with new information" << endl;
            }
        }
    } while (!confirm);

    // Update provider info in system
    if (ChocAnSystem::getInstance().updateProvider(providerID, new_address, new_city, new_state, new_zip)) {
        cout << "\nProvider with ID " << providerID << " updated successfully." << endl;
    } else {
        cout << "\nFailed to update provider with ID " << providerID << endl;
    }
}

void OperatorTerminal::deleteProvider()
{
    string providerID{};
    bool isValidProviderID{false};

    cout << "[Delete Provider]" << endl;
    do {
        getInput(providerID, "\nEnter provider id: ");
        if (!(isValidProviderID = validateIDFormat(providerID))) {
            cout << "Invalid provider id format (9-digit), please try again." << endl;
        }
    } while (!isValidProviderID);

    // Check if providerID is in database
    if (!(ChocAnSystem::getInstance().searchProvider(providerID))) {
        cout << "\nCannot delete provider: No such provider exists" << endl;
    } else {
        if ((ChocAnSystem::getInstance().deleteProvider(providerID))) {
            cout << "\nProvider is deleted successfully" << endl;
        } else {
            cout << "\nCannot delete Provider with ProviderID: " << providerID << endl;
        }
    }
}

////////// HELPER FUNCTION //////////

bool OperatorTerminal::validateZipcodeFormat(const std::string &str)
{
    return is_digits(str) && str.length() == 5;
}

void OperatorTerminal::getAddressInput(std::string &address, std::string &city, std::string &state
                                      , std::string &zip, const std::string &role)
{
    bool isValidZipcode{false};

    // Input new address
    cout << "Enter " << role << " street Address: ";
    getline(cin, address);
    if (address.length() > 25) {
        address = address.substr(0, 25);
    }

    // New city
    cout << "Enter " << role << " city: ";
    getline(cin, city);
    if (city.length() > 14) {
        city = city.substr(0, 14);
    }

    // New state
    cout << "Enter " << role << " State (e.g. OR, WA,...): ";
    getline(cin, state);
    if (state.length() > 2) {
        state = state.substr(0, 2);
    }

    // New zip code
    do {
        getInput(zip, "Enter " + role + " Zipcode: ");
        if (!(isValidZipcode = validateZipcodeFormat(zip))) {
            cout << "Invalid zipcode format, please try again (5-digit)" << endl;
        } 
    } while (!isValidZipcode); 
}

bool OperatorTerminal::confirmPrompt(const std::string &message)
{
    char confirm {};
    cout << message << " (Y/N)\n > ";
    cin >> confirm;
    cin.ignore();
    return toupper(confirm) == 'Y';
}

