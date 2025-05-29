#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "ChocAnSystem.h"

using namespace std;

const string PROVIDDER_DIRECTORY_PATH = "src/reports/Provider_Directory.txt";

ChocAnSystem::ChocAnSystem()
{}

ChocAnSystem::~ChocAnSystem()
{}

ChocAnSystem& ChocAnSystem::getInstance()
{
    static ChocAnSystem instance;
    return instance;
}

int ChocAnSystem::authenticateUser(const string& userID)
{
    return Database::getInstance().authenticateUser(userID);
}

// ---------- Provider Terminal ---------- //

int ChocAnSystem::validateMembership(string& memberID)
{
    return Database::getInstance().validateMembership(memberID);
}

float ChocAnSystem::getServiceFee(const string& servCode)
{
    // make new Service Obj
    Service service;

    // Call to Database::getInstance().getService(servCode); Return a Service Obj assignt to ServObj
    // service = Database::getInstance().getService(servCode);
    /*
        if service.serviceName == "DEFAULT_SERVICE"
    */
    cout << "\nService Name: " << service.serviceName << endl;
    cout << "Is it Correct? (Y/N) \n > ";
    
    return service.serviceFee;
}

bool ChocAnSystem::serviceLog(string &providerID, string &memberID
                             , string &serviceCode, string &serviceDate, string &serviceComment)
{
    // Get the current time point
    const string format = "%m-%d-%Y %H:%M:%S";
    auto now = std::chrono::system_clock::now();
    string formattedTime = dateTime(now, format);

    // Temporary output
    cout << "\nSave this service:" << endl;
    cout << "Current date and time: " << formattedTime << endl;
    cout << "Date service was provided: " << serviceDate << endl;
    cout << "Provider number: " << providerID << endl;
    cout << "Member number: " << memberID << endl;
    cout << "Service code: " << serviceCode << endl;
    cout << "Comments: " << serviceComment << endl; 
    // Delete this section or comment it after database is work.

    // Call to Database::getInstance().serviceLog(providerID, memberID, serviceCode
    //                                            , serviceDate, currentDate, serviceComment);
    // return a bool: result of the service Log
    return false;
}

void ChocAnSystem::getProviderDirectory()
{
    // call to vector<service> list = Database::getInstance().getProviderDirectory()

    vector<Service> providerDirectory = Database::getInstance().getProviderDirectory();  

    // Output the vector here (Provider Directory)
    displayProviderDirectory(providerDirectory);
    
    // Save Provider Directory to file
    if (writeProviderDirectoryToFile(providerDirectory, PROVIDDER_DIRECTORY_PATH)) {
        cout << "Provider Directory saved, file path: " << PROVIDDER_DIRECTORY_PATH << endl;
    } else {
        cerr << "Failed to saved Provider Directory." << endl;
    }
}


// Operator Terminal //
bool ChocAnSystem::addNewMember(const Member &newMember)
{
    // return a bool, true if successfully added new member
    //return Database::getInstance().addNewMeber(newMember);   // UNCOMMENT WHEN DATABASE IS READY
    return false;
}

bool ChocAnSystem::searchMember(const std::string &memberID)
{
    // Return a bool, true if member with "memberID" exist
    //return Database::getInstance().searchMember(memberID); // UNCOMMENTS WHEN DATABASE IS READY
    return true;
}

bool ChocAnSystem::deleteMember(const std::string &memberID)
{
    // Return a bool, true if successfully delete
    //return Database::getInstance().deleteMember(memberID); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

bool ChocAnSystem::addNewProvider(const Provider &newProvider)
{
    // return bool, True if Added successfully
    //return Database::getInstance().addNewProvider(newProvider);   // UNCOMMENT WHEN DATABASE IS READY
    return false;
}

bool ChocAnSystem::searchProvider(const std::string &ProviderID)
{
    // Return a bool, true if provider with "ProviderID" exist
    //return Database::getInstance().searchProvider(ProviderID); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

Provider ChocAnSystem::getProvider(const std::string ProviderID)
{
    Provider updateProvider;
    // return a Provider obj base on Provider id
    //updateProvider = Database::getInstance().getProvider(ProviderID);   // UNCOMMENT WHEN DATABASE IS READY
    return updateProvider;
}

bool ChocAnSystem::updateProvider(const std::string providerID, const std::string newAddrss, const std::string newCty, const std::string newState, const std::string newZip)
{
    // return bool, true if successful update.
    //return Databse::getInstance().updateMember(providerID, newAddrss, newCty, newState, newZip); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

Member ChocAnSystem::getMember(const std::string memberID)
{
    Member updateMember;
    // return a member obj base on Member id
    //updateMember = Database::getInstance().getMember(memberID);   // UNCOMMENT WHEN DATABASE IS READY
    return updateMember;
}

bool ChocAnSystem::updateMember(const std::string memberID, const std::string newAddrss, const std::string newCty, const std::string newState, const std::string newZip)
{
    // return bool, true if successful update.
    //return Databse::getInstance().updateMember(memberID, newAddrss, newCty, newState, newZip); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

bool ChocAnSystem::deleteProvider(const std::string &ProviderID)
{
    // Return a bool
    //return Database::getInstance().deleteProvider(ProviderID); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

////////// Helper function /////////
string ChocAnSystem::dateTime(const chrono::system_clock::time_point &timePoint, const string &format)
{
    time_t time = chrono::system_clock::to_time_t(timePoint);
    tm* timeinfo = localtime(&time);
    char buffer[70];
    strftime(buffer, sizeof(buffer), format.c_str(),
            timeinfo);
    return buffer;
}

string ChocAnSystem::getCurrentDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y", ltm);
    return std::string(buffer);
}

string ChocAnSystem::formatFileName(const std::string fileName)
{
    string result{};
    for (char c : fileName) {
        if (isalnum(c) || c == '_') {
            result += c;
        } else if (c == ' ') {
            result += '_';
        }
    }
    return result;
}

void ChocAnSystem::displayProviderDirectory(std::vector<Service> &providerDirectory)
{
    cout << endl << string(56, '-') << endl;
    cout << "\t\t   PROVIDER DIRECTORY" << endl;
    
    // Header
    cout << endl << string(56, '-') << endl;
    cout << left 
         << setw(20) << "Service Code"
         << setw(25) << "Service Name"
         << "Service Fee" << endl;

    // Data row
    for (const auto& entry : providerDirectory) {
        cout << left
             << setw(20) << entry.serviceCode
             << setw(25) << entry.serviceName
             << "$" << fixed << setprecision(2) << entry.serviceFee
             << endl;
    }

    // Footer 
    cout << endl << string(56, '=') << endl;
    cout << "\t     Copyright @ ChocAn Data Center" << endl;
    cout << string(56, '=') << endl;
}

bool ChocAnSystem::writeProviderDirectoryToFile(vector<Service> &services, const string & filePath)
{
    ofstream writeToFile(filePath);

    if (!writeToFile.is_open()) {
        cerr << "Error: Could Open file " << filePath << endl;
        return false;
    }

    writeToFile << string(56, '-') << "\n";
    writeToFile << "\t\t   PROVIDER DIRECTORY\n";
    writeToFile << string(56, '-') << "\n";
    writeToFile << left 
                << setw(20) << "Service Code"
                << setw(25) << "Service Name"
                << "Service Fee" << "\n";

    for (const auto& entry : services) {
        writeToFile << left
                    << setw(20) << entry.serviceCode
                    << setw(25) << entry.serviceName
                    << "$" << fixed << setprecision(2) << entry.serviceFee
                    << "\n";
    }

    writeToFile << string(56, '=') << "\n";
    writeToFile << "\t     Copyright @ ChocAn Data Center\n";
    writeToFile << string(56, '=') << "\n";

    writeToFile.close();
    return true;
}
