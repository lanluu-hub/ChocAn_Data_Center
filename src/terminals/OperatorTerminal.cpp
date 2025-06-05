#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
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
    int numOfOption{};

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
    bool confirm{ false };

    cout << "[Add Member]" << endl;

    cout << "Please enter new Member Information" << endl;
    do {
        {   // Scope for user input //
            // member name
            cout << "Enter New Member Name: ";
            do {
                getline(cin, new_name);
                if (new_name.empty()) {
                    cout << "Name cannot be empty. Try again:\n > ";
                }
            } while (new_name.empty());

            if (new_name.length() > 25) {
                new_name = new_name.substr(0, 25);
            }

            transform(new_name.begin(), new_name.end(), new_name.begin(), ::toupper);

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
                clearScreen();
                cout << "Please try again with add new Member" << endl;
            }
        }
    } while (!confirm);

    clearScreen();

    // Called to ChocAn to add new member, a bool is being return, true = successfull, false otherwise
    if (ChocAnSystem::getInstance().addNewMember(new_name, new_address, new_city, new_state, new_zip)) {
        cout << "Member added successfully." << endl;
    }
    else {
        printError("Failed to add new Member.");
    }
    return;
}

void OperatorTerminal::updateMember()
{
    Member memberToUpdate;
    bool confirm{ false };
    string memberID{};
    string new_address{}, new_city{}, new_state{}, new_zip{};
    string chocan_errmsg{};
    bool isValidID{ false };

    cout << "[Update Member]" << endl;

    do {
        getInput(memberID, "Enter member ID for update:\n > ");

        if (!(isValidID = validateIDFormat(memberID))) {
            cout << "Invalid ID format (9-digit), please try again." << endl;
        }
    } while (!isValidID);

    // check if member exist
    if (!(ChocAnSystem::getInstance().searchMember(memberID))) {
        chocan_errmsg = "Member with ID " + memberID + " not found.";
        printError(chocan_errmsg);
        return;
    }

    clearScreen();

    // Actual update input field
    cout << "Please Enter update information here" << endl;
    do {
        {
            // Scope for user input
            getAddressInput(new_address, new_city, new_state, new_zip, "Member");
        } // end of input scope

        clearScreen();

        {   // Member Information confirmation scope
            cout << "Please make sure the following information is correct: " << endl;
            cout << "MemberID: " << memberID << endl
                << "New Address: " << new_address << endl
                << "New City: " << new_city << endl
                << "New State: " << new_state << endl
                << "New Zipcode: " << new_zip << endl;

            if (!(confirm = confirmPrompt("\nIs this information correct?"))) {
                clearScreen();
                cout << "Please try again with new information" << endl;
            }
        }
    } while (!confirm);

    clearScreen();

    // Call actual update function from chocan
    if (ChocAnSystem::getInstance().updateMember(memberID, new_address, new_city, new_state, new_zip)) {
        cout << "Member with MemberID " << memberID << " Updated successfully." << endl;
    }
    else {
        chocan_errmsg = "Update failed for member " + memberID; 
        printError(chocan_errmsg);
    }
}

void OperatorTerminal::deleteMember()
{
    string memberID{};
    string chocan_errmsg{};
    bool isValidMemberID{ false };

    cout << "[Delete Member]" << endl;
    do {
        getInput(memberID, "Enter member id: ");
        if (!(isValidMemberID = validateIDFormat(memberID))) {
            cout << "Invalid member id format (9-digit), please try again." << endl;
        }
    } while (!isValidMemberID);

    clearScreen();

    // Check if memberID is in database
    if (!(ChocAnSystem::getInstance().searchMember(memberID))) {
        chocan_errmsg = "Deletion failed: Member not found.";
        printError(chocan_errmsg);
    }
    else {
        if ((ChocAnSystem::getInstance().deleteMember(memberID))) {
            cout << "Member is deleted successfully" << endl;
        }
        else {
            chocan_errmsg = "Deletion failed: database error. Cannot delete member with Member ID " + memberID; 
            printError(chocan_errmsg);
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
    bool confirm{ false };

    cout << "[Add Provider]" << endl;

    cout << "Please enter new Provider Information" << endl;

    do {
        {   // Scope for user input //
            cout << "Enter New Provider Name: ";
            do {
                getline(cin, new_name);
                if (new_name.empty()) {
                    cout << "Name cannot be empty. Try again:\n > ";
                }
            } while (new_name.empty());

            if (new_name.length() > 25) {
                new_name = new_name.substr(0, 25);
            }

            transform(new_name.begin(), new_name.end(), new_name.begin(), ::toupper);

            // get Provider Address
            getAddressInput(new_address, new_city, new_state, new_zip, "Provider");
        }

        clearScreen();

        {   // Confirm block
            cout << "\nPlease confirm if this is the correct information: " << endl;
            cout << "Provider Name: " << new_name << endl
                << "Provider Adress: " << new_address << endl
                << "Provider City: " << new_city << endl
                << "Provider State: " << new_state << endl
                << "Provider Zipcode: " << new_zip << endl;

            if (!(confirm = confirmPrompt("\nIs this information correct?"))) {
                clearScreen();
                cout << "Please try again with new information" << endl;
            }
        }
    } while (!confirm);

    clearScreen();

    // Call to ChocAnSystem to add the new provider
    if (ChocAnSystem::getInstance().addNewProvider(new_name, new_address, new_city, new_state, new_zip)) {
        cout << "Provider added successfully." << endl;
    }
    else {
        printError("Failed to add new provider.");
    }
}

void OperatorTerminal::updateProvider()
{
    Provider providerToUpdate;
    bool confirm{ false };
    string providerID{};
    string new_address{}, new_city{}, new_state{}, new_zip{};
    string chocan_errmsg{};
    bool isValidID{ false };

    cout << "[Update Provider]" << endl;

    do {
        getInput(providerID, "\nEnter provider Id for update:\n > ");
        if (!(isValidID = validateIDFormat(providerID))) {
            cout << "Invalid ID format (9-digit), please try again." << endl;
        }
    } while (!isValidID);

    // check if provider exist
    if (!(ChocAnSystem::getInstance().searchProvider(providerID))) {
        chocan_errmsg = "Provider with ID " + providerID + " not found."; 
        printError(chocan_errmsg);
        return;
    }

    clearScreen();

    cout << "Please Enter update information here" << endl;

    do {
        {
            // input scope, get Provider input
            getAddressInput(new_address, new_city, new_state, new_zip, "Provider");
        }

        clearScreen();

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

    clearScreen();

    // Update provider info in system
    if (ChocAnSystem::getInstance().updateProvider(providerID, new_address, new_city, new_state, new_zip)) {
        cout << "Provider with ID " << providerID << " updated successfully." << endl;
    }
    else {
        chocan_errmsg = "Failed to update provider with ID " + providerID;
        printError(chocan_errmsg);
    }
}

void OperatorTerminal::deleteProvider()
{
    string providerID{};
    string Chocan_errmsg{};
    bool isValidProviderID{ false };

    cout << "[Delete Provider]" << endl;
    do {
        getInput(providerID, "\nEnter provider id: ");
        if (!(isValidProviderID = validateIDFormat(providerID))) {
            cout << "Invalid provider id format (9-digit), please try again." << endl;
        }
    } while (!isValidProviderID);

    clearScreen();

    // Check if providerID is in database
    if (!(ChocAnSystem::getInstance().searchProvider(providerID))) {
        Chocan_errmsg = "Deletion failed: Provider not found.";
        printError(Chocan_errmsg);
    }
    else {
        if ((ChocAnSystem::getInstance().deleteProvider(providerID))) {
            cout << "Provider is deleted successfully" << endl;
        }
        else {
            Chocan_errmsg = "Failed to delete provider with ProviderID: " + providerID + " due to database error.";
            printError(Chocan_errmsg);
        }
    }
}

////////// HELPER FUNCTION //////////

bool OperatorTerminal::validateZipcodeFormat(const std::string& str)
{
    return is_digits(str) && str.length() == 5;
}

void OperatorTerminal::getAddressInput(std::string& address, std::string& city, std::string& state
    , std::string& zip, const std::string& role)
{
    vector<string> validStates =
    {
        "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA",
        "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
        "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
        "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
        "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY",
        "ALABAMA",       "ALASKA",         "ARIZONA",       "ARKANSAS",
        "CALIFORNIA",    "COLORADO",       "CONNECTICUT",   "DELAWARE",
        "FLORIDA",       "GEORGIA",        "HAWAII",        "IDAHO",
        "ILLINOIS",      "INDIANA",        "IOWA",          "KANSAS",
        "KENTUCKY",      "LOUISIANA",      "MAINE",         "MARYLAND",
        "MASSACHUSETTS", "MICHIGAN",       "MINNESOTA",     "MISSISSIPPI",
        "MISSOURI",      "MONTANA",        "NEBRASKA",      "NEVADA",
        "NEW HAMPSHIRE", "NEW JERSEY",     "NEW MEXICO",    "NEW YORK",
        "NORTH CAROLINA","NORTH DAKOTA",   "OHIO",          "OKLAHOMA",
        "OREGON",        "PENNSYLVANIA",   "RHODE ISLAND",  "SOUTH CAROLINA",
        "SOUTH DAKOTA",  "TENNESSEE",      "TEXAS",         "UTAH",
        "VERMONT",       "VIRGINIA",       "WASHINGTON",    "WEST VIRGINIA",
        "WISCONSIN",     "WYOMING"
    };
    bool isValidState = false;
    bool isValidZipcode{ false };

    // Input new address
    cout << "Enter " << role << " street Address: ";
    do {
        getline(cin, address);
        if (address.empty()) {
            cout << "Adress cannot be empty. Try again:\n > ";
        }
    } while (address.empty());

    if (address.length() > 25) {
        address = address.substr(0, 25);
    }
    transform(address.begin(), address.end(), address.begin(), ::toupper);
    // End of Adress input

    // New city
    cout << "Enter " << role << " city: ";
    do {
        getline(cin, city);
        if (city.empty()) {
            cout << "City cannot be empty. Try again:\n > ";
        }
    } while (city.empty());

    if (city.length() > 14) {
        city = city.substr(0, 14);
    }
    transform(city.begin(), city.end(), city.begin(), ::toupper);

    // New state
    cout << "Enter " << role << " State (e.g. OR, WA,...): ";
    do
    {
        do {
            getline(cin, state);
            if (state.empty()) {
                cout << "State cannot be empty. Try again:\n > ";
            }
        } while (state.empty());

        transform(state.begin(), state.end(), state.begin(), ::toupper);

        isValidState = false;   //set false first before compare
        for (const auto& valid : validStates)
        {
            if (state == valid)
            {
                isValidState = true;
                break;
            }
        }

        if (!isValidState) {
            cout << "Invalid State, Try again:\n > ";
        }
    } while (!isValidState);

    if (state.length() > 2)
    {
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


bool OperatorTerminal::confirmPrompt(const std::string& message)
{
    char confirm{};
    cout << message << " (Y/N)\n > ";
    cin >> confirm;
    cin.ignore(1024, '\n');
    return toupper(confirm) == 'Y';
}

