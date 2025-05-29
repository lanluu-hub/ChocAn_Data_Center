#include <iostream>
#include <cassert>
#include "OperatorTerminal.h"
#include "../ChocAnSystem.h"

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
    cout << "\n[Operator Terminal]" << endl;
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
    switch (input) {
    case 1: // Add member
        addMember();    
        break;
    
    case 2: // Update member
        updateMember();    
        break;

    case 3: // Delete member
        deleteMember();    
        break;

    case 4: // Add Provider
        addProvider();
        break;

    case 5: // Update Provider
        updateProvider(); 
        break;

    case 6: // Delete Provider
        deleteProvider(); 
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
    bool isValidZipcode {false};

    cout << "\n[Add new Member]" << endl;

    {   // Scope for user input //
        // member name
        cout << "Enter New Member Name: ";
        getline(cin, new_name);
        if (new_name.length() > 25) {
            new_name = new_name.substr(0, 25);
        }

        // member address
        cout << "Enter New Member street Address: ";
        getline(cin, new_address);
        if (new_address.length() > 25) {
            new_address = new_address.substr(0, 25);
        }

        // member city
        cout << "Enter New Member city: ";
        getline(cin, new_city);
        if (new_city.length() > 14) {
            new_city = new_city.substr(0, 14);
        }

        // member state
        cout << "Enter New Member State (e.g. OR, WA,...): ";
        getline(cin, new_state);
        if (new_state.length() > 2) {
            new_state = new_state.substr(0, 2);
        }

        // member zipcode
        do {
            getInput(new_zip, "Enter New Member Zipcode: ");
            
            if (!(isValidZipcode = validateZipcodeFormat(new_zip))) {
                cout << "Invalid zipcode format, please try again (5-digit)" << endl;
            } 
        } while(!isValidZipcode);
    }   // End of input scope

    //new_id = ChocAnSystem()::getInstance().getNewMemberID(); // Uncomment this when Database is READY
    new_id = "100001";

    // Put the info user input into a Member class
    Member newMember(new_name, new_id, new_address, new_city, new_state, new_zip);

    // Called to ChocAn to add new member, a bool is being return, true = successfull, false otherwise
    if (ChocAnSystem::getInstance().addNewMember(newMember)) {
        cout << "\nMember added successfully." << endl;
    } else {
        cout << "\nFailed to add new Member." << endl;
    }
}

void OperatorTerminal::updateMember()
{
    /*
    Prompt user for memberID to be update
    memberID <- input
    validate member id in correct format
    if yes:
        call chocan.getMember(memberID) return a Member Obj
        display {
            Member ID: #########
            Member Name: Joe
        }
        loop:
            Prompt: is this correct?
            if no -> loop back to enter ID
        if yes: 
        Prompt: Please enter new address: 
        ...

        ChocAnSystem::getInstance().updateMember(memberID, u_addr, u_city, u_state, u_zip); 
        // name and ID not change, Id for update

        check if update success -> outpu successful
        if fail -> output fail
    */
    // New Member Obj
    char confirm {};
    string memberID{};
    string new_address{}, new_city{}, new_state{}, new_zip {};
    bool isValidID{false};
    bool isMemberExist{false};
    bool isValidZipcode{false};

    cout << "\n[MEMBER UPDATE]" << endl;

    do {
        do {
            getInput(memberID, "\nEnter member Id for update:\n > ");
            if (!(isValidID = validateIDFormat(memberID))) {
                cout << "\nInvalid ID format (9-digit), please try again." << endl;
            } else if (!(isMemberExist = ChocAnSystem::getInstance().searchMember(memberID))) {
                cout << "\nMember with member ID " << memberID << " is not found, please try another ID." 
                     << endl;
            }
        } while (!isValidID || !isMemberExist);
        
        //TODO: call ChocAnSystem::getInstance().getMember(memberID); return a Member Obj
        
        Member memberToUpdate = ChocAnSystem::getInstance().getMember(memberID);

        cout << "\nPlease review the member info:" << endl;
        memberToUpdate.displayMember(); 
        cout << "\nIs this the correct member? (Y/N)\n > ";
        cin >> confirm;
        cin.ignore();
    } while (toupper(confirm) != 'Y');

    // Actual update input field
    {
        // Scope for user input
         // member address
        cout << "Enter New street Address: ";
        getline(cin, new_address);
        if (new_address.length() > 25) {
            new_address = new_address.substr(0, 25);
        }

        // member city
        cout << "Enter New city: ";
        getline(cin, new_city);
        if (new_city.length() > 14) {
            new_city = new_city.substr(0, 14);
        }

        // member state
        cout << "Enter New State (e.g. OR, WA,...): ";
        getline(cin, new_state);
        if (new_state.length() > 2) {
            new_state = new_state.substr(0, 2);
        }

        // member zipcode
        do {
            getInput(new_zip, "Enter New Zipcode: ");
            
            if (!(isValidZipcode = validateZipcodeFormat(new_zip))) {
                cout << "Invalid zipcode format, please try again (5-digit)" << endl;
            } 
        } while(!isValidZipcode); 

        // considering adding a infomation confirmation before calling addMewMember
        
    } // end of input scope

    // Call actual update function from chocan
    if (ChocAnSystem::getInstance().updateMember(memberID, new_address, new_city, new_state, new_zip)) {
        cout << "\nMember with MemberID " << memberID << "Updated successfully." << endl;
    } else {
        cout << "\nFailed to Update Member " << memberID << endl;
    }
}

void OperatorTerminal::deleteMember()
{
    string memberID{};
    bool isValidMemberID{false};
   
    cout << "\n[Delete Member]" << endl;
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
        if (!(ChocAnSystem::getInstance().deleteMember(memberID))) {
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
    bool isValidZipcode {false};

    cout << "\n[Add new Provider]" << endl;

    {   // Scope for user input //
        // Provider name
        cout << "Enter New Provider Name: ";
        getline(cin, new_name);
        if (new_name.length() > 25) {
            new_name = new_name.substr(0, 25);
        }

        // Provider address
        cout << "Enter New Provider street Address: ";
        getline(cin, new_address);
        if (new_address.length() > 25) {
            new_address = new_address.substr(0, 25);
        }

        // Provider city
        cout << "Enter New Provider city: ";
        getline(cin, new_city);
        if (new_city.length() > 14) {
            new_city = new_city.substr(0, 14);
        }

        // Provider state
        cout << "Enter New Provider State (e.g. OR, WA,...): ";
        getline(cin, new_state);
        if (new_state.length() > 2) {
            new_state = new_state.substr(0, 2);
        }

        // Provider zipcode
        do {
            getInput(new_zip, "Enter New Provider Zipcode: ");
            
            if (!(isValidZipcode = validateZipcodeFormat(new_zip))) {
                cout << "Invalid zipcode format, please try again (5-digit)" << endl;
            } 
        } while(!isValidZipcode);
    }

    //new_id = ChocAnSystem::getInstance().getNewProviderID(); // Uncomment when database ID system is ready
    new_id = "200001";

    // Put the input into a Provider class
    Provider newProvider(new_name, new_id, new_address, new_city, new_state, new_zip);

    // Call to ChocAnSystem to add the new provider
    if (ChocAnSystem::getInstance().addNewProvider(newProvider)) {
        cout << "\nProvider added successfully." << endl;
    } else {
        cout << "\nFailed to add new Provider." << endl;
    }
}

void OperatorTerminal::updateProvider()
{
    char confirm {};
    string providerID{};
    string new_address{}, new_city{}, new_state{}, new_zip {};
    bool isValidID{false};
    bool isProviderExist{false};
    bool isValidZipcode{false};

    cout << "\n[PROVIDER UPDATE]" << endl;

    do {
        do {
            getInput(providerID, "\nEnter provider Id for update:\n > ");
            if (!(isValidID = validateIDFormat(providerID))) {
                cout << "\nInvalid ID format (9-digit), please try again." << endl;
            } else if (!(isProviderExist = ChocAnSystem::getInstance().searchProvider(providerID))) {
                cout << "\nProvider with ID " << providerID << " not found, please try another ID." << endl;
            }
        } while (!isValidID || !isProviderExist);
        
        Provider providerToUpdate = ChocAnSystem::getInstance().getProvider(providerID);

        cout << "\nPlease review the provider info:" << endl;
        providerToUpdate.displayProvider(); 
        cout << "\nIs this the correct provider? (Y/N)\n > ";
        cin >> confirm;
        cin.ignore();
    } while (toupper(confirm) != 'Y');

    {
        // Input new address
        cout << "Enter New street Address: ";
        getline(cin, new_address);
        if (new_address.length() > 25) {
            new_address = new_address.substr(0, 25);
        }

        // New city
        cout << "Enter New city: ";
        getline(cin, new_city);
        if (new_city.length() > 14) {
            new_city = new_city.substr(0, 14);
        }

        // New state
        cout << "Enter New State (e.g. OR, WA,...): ";
        getline(cin, new_state);
        if (new_state.length() > 2) {
            new_state = new_state.substr(0, 2);
        }

        // New zip code
        do {
            getInput(new_zip, "Enter New Zipcode: ");
            if (!(isValidZipcode = validateZipcodeFormat(new_zip))) {
                cout << "Invalid zipcode format, please try again (5-digit)" << endl;
            } 
        } while (!isValidZipcode); 
    }

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

    cout << "\n[Delete Provider]" << endl;
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
        if (!(ChocAnSystem::getInstance().deleteProvider(providerID))) {
            cout << "\nProvider is deleted successfully" << endl;
        } else {
            cout << "\nCannot delete Provider with ProviderID: " << providerID << endl;
        }
    }
}

////////// HELPER FUNCTION //////////
void OperatorTerminal::getInput(string &input, const string &prompt)
{
    cout << prompt;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(1024, '\n');

        cout << "\nInvalid input format. please try again.\n > ";
    }
    cin.ignore(1024, '\n');
}

bool OperatorTerminal::validateZipcodeFormat(const std::string &str)
{
    bool validated {false};

    if (is_digits(str)) {
        if (str.length() == 5) {
            validated = true;
        }
    }
    return validated;
}

bool OperatorTerminal::validateIDFormat(const std::string &str)
{
    bool validated {false};

    if (is_digits(str)) {
        if (str.length() == 9) {
            validated = true;
        }
    }
    return validated;
}

bool OperatorTerminal::is_digits(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;;
}
