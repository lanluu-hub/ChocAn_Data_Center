#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include "ChocAnSystem.h"

using namespace std;

const string MEMBER_REPORT_FOLDER = "src/reports/members/";
const string PROVIDER_REPORT_FOLDER = "src/reports/providers/";

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
    service = Database::getInstance().getService(servCode);

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
    //                                            , serviceDate, formattedTime, serviceComment);
    // return a bool: result of the service Log
    return false;
}

void ChocAnSystem::getProviderDirectory()
{
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

void ChocAnSystem::generateMemberReport(const std::string &memberID)
{
    /*
        workflow
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

        call printMemberReport(filepath);
    */

    Member member = getMember(memberID);
    char confirm {};
    string  currentDate {},
            bestDate {},
            rawFilename {},
            formattedFilename {},
            filePath {};

    const string format = "%Y-%m-%d";

    if (member.isEmpty()) {
        cout << "\nMember does not exist" << endl;
        return;
    }

    // Confirmation
    cout << "\nConfirmation:" << endl;
    cout << "Member ID: " << member.memberID << endl
         << "Member Name: " << member.memberName << endl;
    cout << "\nIs this the correct member? (Y/N)\n > ";
    cin >> confirm;

    if (toupper(confirm) != 'Y') {
        cout << "\nTry again with another ID" << endl;
        return;
    }

    currentDate = getCurrentDate();

    // Get the bestDate //
    // parse the date
    chrono::system_clock::time_point parsedDate = parseDate(currentDate, format);

    // subtract 7 days
    chrono::system_clock::time_point cutoffDate = parsedDate - chrono::hours(24 * 7);

    // Format the date back to string
    bestDate = dateTime(cutoffDate, format);
    // End of get bestDate //

    // Get Clean filePath for generated report //
    rawFilename = member.memberName + "_" + currentDate;
    formattedFilename = formatFileName(rawFilename);
    filePath = MEMBER_REPORT_FOLDER + formattedFilename + ".txt";
    // End of filePath //

    // Temporary Ouput - Delete this when database ready
    cout << "\nTemporary output" << endl
         << "Member Name: " << member.memberName << endl
         << "Member Number: " << memberID << endl
         << "Member street address: " << member.memberStreetAddress << endl
         << "Member city: " << member.memberCity << endl
         << "Member State: " << member.memberState << endl
         << "Memeber Zip code: " << member.memberZipCode << endl;
    
    cout << "Current Date: " << currentDate << endl;
    cout << "Best date: " << bestDate << endl;
    cout << "fileName: " << formattedFilename << endl;
    cout << "FilePath: " << filePath << endl;
    // End of temporary output - delete this when database is ready 

    //Database::getInstance().generateMemberReport(member, bestDate, filePath);   // UNCOMMENTS THIS WHEN DATABASE READY
    printMemberReport(filePath);
    return;
}

void ChocAnSystem::printMemberReport(const std::string &filePath)
{
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "\nFailed to open file " << filePath << endl;
        return;
    }
    
    string line;

    while(getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void ChocAnSystem::generateProviderReport(const std::string &providerID)
{
    /*
        providerObj <- Database::getInstance().getProviderByID(providerID)
        if (providerObj is null):
            Output: "Provider not found."
            return

        Output:
            "Provider ID: " + providerObj.ID
            "Provider Name: " + providerObj.Name
        Prompt: "Is this the correct provider? (Y/N) >"
        if input != 'Y':
            Output: "Please try again with another ID"
            return

        currentDate <- getCurrentDate()                      // YYYY-MM-DD
        cutoffDate <- currentDate - 7 days                   // for weekly report

        rawFileName <- providerObj.Name + "_" + currentDate
        formattedFileName <- sanitizeFileName(rawFileName)
        filePath <- PROVIDER_REPORT_FOLDER + formattedFileName + ".txt"

        Call Database::generateProviderReport(providerObj, cutoffDate, filePath)

        Call ManagerTerminal::printReport(filePath)
    */
    
    Provider provider = getProvider(providerID);
    char confirm {};
    string  currentDate {},
            bestDate {},
            rawFilename {},
            formattedFilename {},
            filePath {};

    const string format = "%Y-%m-%d";

    if (provider.isEmpty()) {
        cout << "\nProvider does not exist" << endl;
        return;
    }

    // Confirmation
    cout << "\nConfirmation:" << endl;
    cout << "Provider ID: " << provider.providerID << endl
         << "Provider Name: " << provider.providerName << endl;
    cout << "\nIs this the correct Provider? (Y/N)\n > ";
    cin >> confirm;

    if (toupper(confirm) != 'Y') {
        cout << "\nTry again with another ID" << endl;
        return;
    }

    currentDate = getCurrentDate();

    // Get the bestDate //
    // parse the date
    chrono::system_clock::time_point parsedDate = parseDate(currentDate, format);

    // subtract 7 days
    chrono::system_clock::time_point cutoffDate = parsedDate - chrono::hours(24 * 7);

    // Format the date back to string
    bestDate = dateTime(cutoffDate, format);
    // End of get bestDate //

    // Get Clean filePath for generated report //
    rawFilename = provider.providerName + "_" + currentDate;
    formattedFilename = formatFileName(rawFilename);
    filePath = PROVIDER_REPORT_FOLDER + formattedFilename + ".txt";
    // End of filePath //

    // Temporary Ouput - Delete this when database ready
    cout << "\nTemporary output" << endl
         << "Provider Name: " << provider.providerName << endl
         << "Provider Number: " << providerID << endl
         << "Provider street address: " << provider.providerStreetAddress << endl
         << "Provider city: " << provider.providerCity << endl
         << "Provider State: " << provider.providerState << endl
         << "Provider Zip code: " << provider.providerZipCode << endl;
    
    cout << "Current Date: " << currentDate << endl;
    cout << "Best date: " << bestDate << endl;
    cout << "fileName: " << formattedFilename << endl;
    cout << "FilePath: " << filePath << endl;
    // End of temporary output - delete this when database is ready 

    //Database::getInstance().generateProviderReport(provider, bestDate, filePath);   // UNCOMMENTS THIS WHEN DATABASE READY
    printProviderReport(filePath);
    return;
}

void ChocAnSystem::printProviderReport(const std::string &filePath)
{
    /// @todo need display
}

/////////// Operator Terminal //////////

bool ChocAnSystem::addNewMember(const std::string & newName, const std::string & newAddr
                                , const std::string & newCity, const std::string & newState, const std::string & newZip)
{
    // return a bool, true if successfully added new member
    //return Database::getInstance().addNewMeber(newName, newAddr, newCity, newState, newZip);   // UNCOMMENT WHEN DATABASE IS READY
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

bool ChocAnSystem::addNewProvider(const std::string &newName, const std::string &newAddr
                                 , const std::string &newCity, const std::string &newState, const std::string &newZip)
{
    // return bool, True if Added successfully
    //return Database::getInstance().addNewProvider(newName, newAddr, newCity, newState, newZip);    // UNCOMMENT WHEN DATABASE IS READY
    return false;
}

bool ChocAnSystem::searchProvider(const std::string &ProviderID)
{
    // Return a bool, true if provider with "ProviderID" exist
    //return Database::getInstance().searchProvider(ProviderID); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

Provider ChocAnSystem::getProvider(const std::string &ProviderID)
{
    Provider updateProvider;
    // return a Provider obj base on Provider id
    //updateProvider = Database::getInstance().getProvider(ProviderID);   // UNCOMMENT WHEN DATABASE IS READY
    return updateProvider;
}

bool ChocAnSystem::updateProvider(const std::string &providerID, const std::string &newAddrss
                                 , const std::string &newCty, const std::string &newState, const std::string &newZip)
{
    // return bool, true if successful update.
    //return Databse::getInstance().updateMember(providerID, newAddrss, newCty, newState, newZip); // UNCOMMENTS WHEN DATABASE IS READY
    return false;
}

Member ChocAnSystem::getMember(const std::string & memberID)
{
    Member updateMember;
    // return a member obj base on Member id
    //updateMember = Database::getInstance().getMember(memberID);   // UNCOMMENT WHEN DATABASE IS READY
    return updateMember;
}

bool ChocAnSystem::updateMember(const std::string &memberID, const std::string &newAddrss
                                , const std::string &newCty, const std::string &newState, const std::string &newZip)
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

chrono::system_clock::time_point ChocAnSystem::parseDate(const string &dateString, const string &format)
{
    tm tmStruct = {};
    istringstream ss(dateString);
    ss >> get_time(&tmStruct, format.c_str());
    return chrono::system_clock::from_time_t(mktime(&tmStruct));
}

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
    const string format = "%Y-%m-%d";
    auto now = std::chrono::system_clock::now();
    string formattedTime = dateTime(now, format);

    return formattedTime; 
}

string ChocAnSystem::formatFileName(const std::string &fileName)
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
