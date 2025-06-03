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
const string SUMMARY_REPORT_FOLDER = "src/reports/summaries/";

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
    Service service;

    service = Database::getInstance().getService(servCode);

    
    
    return service.serviceFee;
}

string ChocAnSystem::getServiceName(const string& servCode) {
    Service service;

    service = Database::getInstance().getService(servCode);

    return service.serviceName;
}

Service ChocAnSystem::getService(const std::string &servCode)
{
    return Database::getInstance().getService(servCode);
}

bool ChocAnSystem::serviceLog(string &providerID, string &memberID
                             , string &serviceCode, string &serviceDate, string &serviceComment)
{
    // Get the current time point
    const string format = "%m-%d-%Y %H:%M:%S";
    auto now = std::chrono::system_clock::now();
    string formattedTime = dateTime(now, format);

    return Database::getInstance().serviceLog(providerID, memberID, serviceCode
                                             , serviceDate, formattedTime, serviceComment);
}

void ChocAnSystem::getProviderDirectory()
{
    vector<Service> providerDirectory = Database::getInstance().getProviderDirectory();  

    // Output the vector here (Provider Directory)
    displayProviderDirectory(providerDirectory);
    
    // Save Provider Directory to file
    if (writeProviderDirectoryToFile(providerDirectory, PROVIDDER_DIRECTORY_PATH)) {
        cout << "\n>> Provider Directory saved, file path: " << PROVIDDER_DIRECTORY_PATH << endl;
    } else {
        cerr << "Failed to saved Provider Directory." << endl;
    }
}

// ---------- Manager Terminal ---------- //

void ChocAnSystem::generateMemberReport(const std::string &memberID)
{
    Member member = getMember(memberID);
    char confirm {};
    string  currentDate {}, // hold current date
            bestDate {},    // hold the earliest day the report will be generate
            rawFilename {}, // hold the raw file name with whitespace and special character
            formattedFilename {},   // hold clean filename e.g first_last_2025_05_31.txt
            filePath {};    // file path to the report file src/reports/members/first_last_2025_05_31.txt

    const string format = "%Y-%m-%d";   // Date format for fileName

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

    /// @brief Generates and writes a weekly member service report to the specified file.
    ///        This function queries all services provided to the member within the last 7 days,
    ///        then formats and saves the results into a human-readable report file.
    /// @param memberID The unique 9-digit ID of the member whose report is being generated. Used to query ServiceLog.
    /// @param bestDate The lower bound (7 days ago) in YYYY-MM-DD format. Only services on or after this date are included.
    /// @param filePath The full path (e.g., "reports/members/John_Doe_2025-05-26.txt") where the report file will be written.
    ///        The file should be opened and written inside this function. 
    //Database::getInstance().generateMemberReport(memberID, bestDate, filePath);   // UNCOMMENTS THIS WHEN DATABASE READY
    printReport(filePath);
    return;
}

void ChocAnSystem::printReport(const std::string &filePath)
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
    Provider provider = getProvider(providerID);
    char confirm {};
    string  currentDate {}, // hold current date
            bestDate {},    // hold the earliest day the report will be generate
            rawFilename {}, // hold the raw file name with whitespace and special character
            formattedFilename {},   // hold clean filename e.g first_last_2025_05_31.txt
            filePath {};    // file path to the report file src/reports/members/first_last_2025_05_31.txt

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

    /// @brief Generates and writes a weekly provider service report to the specified file.
    ///        This function queries all services provided by the given provider within the last 7 days,
    ///        and formats the results into a detailed report suitable for accounts payable.
    /// @param providerID The unique 9-digit ID of the provider. Used to retrieve service logs from the database.
    /// @param bestDate The lower bound (7 days ago) in YYYY-MM-DD format. Only services on or after this date are included.
    /// @param filePath The full file path (e.g., "reports/providers/Jane_Smith_2025-05-26.txt") where the report will be saved.
    ///        The function should open and write to this file.
    //Database::getInstance().generateProviderReport(providerID, bestDate, filePath);   // UNCOMMENTS THIS WHEN DATABASE READY
    printReport(filePath);
    return;
}

void ChocAnSystem::generateSummaryReport()
{
    string  currentDate{},
            cutoffDate {},
            rawFilename {},
            formattedFilename{},
            filePath{};
    
    const string format {"%Y-%m-%d"};

    currentDate = getCurrentDate();

    // Get the cutoffDate //
    // parse the date
    chrono::system_clock::time_point parsedDate = parseDate(currentDate, format);

    // subtract 7 days
    chrono::system_clock::time_point lastDate = parsedDate - chrono::hours(24 * 7);

    // Format the date back to string
    cutoffDate = dateTime(lastDate, format);
    // End of cutoffDate //

    // Get Clean filePath for generated report //
    rawFilename = "Summary_Report_" + currentDate;
    formattedFilename = formatFileName(rawFilename);
    filePath = SUMMARY_REPORT_FOLDER + formattedFilename + ".txt";
    // End of filePath //

    /// @brief Generates and writes a weekly summary report for accounts payable to the specified file.
    ///        The report includes all providers who rendered services during the past 7 days,
    ///        along with their total number of consultations and total fees.
    ///        It also includes overall totals at the end of the report.
    /// @param cutoffDate The lower bound (7 days ago) in YYYY-MM-DD format. Only services on or after this date are included.
    /// @param filePath The full file path (e.g., "reports/SummaryReport_2025-05-26.txt") where the summary report will be written.
    ///        The file should be created and written inside this function.
    //Database::generateSummaryReport(cutoffDate, filePath); // UNCOMMENT THIS WHEN DATABASE IS READY

    printReport(filePath);
}

/////////// Operator Terminal //////////

bool ChocAnSystem::addNewMember(const std::string & newName, const std::string & newAddr
                                , const std::string & newCity, const std::string & newState, const std::string & newZip)
{
    // return a bool, true if successfully added new member
    return Database::getInstance().add("Members", newName, newAddr, newCity, newState, newZip);   // UNCOMMENT WHEN DATABASE IS READY
    //return false;
}

bool ChocAnSystem::searchMember(const std::string &memberID)
{
    // Return a bool, true if member with "memberID" exist
    return Database::getInstance().searchMember(memberID); // UNCOMMENTS WHEN DATABASE IS READY
    //return true;
}

bool ChocAnSystem::updateMember(const std::string &memberID, const std::string &newAddrss
                                , const std::string &newCty, const std::string &newState, const std::string &newZip)
{
    // return bool, true if successful update.
    return Database::getInstance().update(memberID, "Members", newAddrss, newCty, newState, newZip); // UNCOMMENTS WHEN DATABASE IS READY
    //return false;
}

bool ChocAnSystem::deleteMember(const std::string &memberID)
{
    // Return a bool, true if successfully delete
    return Database::getInstance().deleteUser("Members",memberID); // UNCOMMENTS WHEN DATABASE IS READY
    //return false;
}

bool ChocAnSystem::addNewProvider(const std::string &newName, const std::string &newAddr
                                 , const std::string &newCity, const std::string &newState, const std::string &newZip)
{
    // return bool, True if Added successfully
    return Database::getInstance().add("Users", newName, newAddr, newCity, newState, newZip);    // UNCOMMENT WHEN DATABASE IS READY
    //return false;
}

bool ChocAnSystem::searchProvider(const std::string &ProviderID)
{
    // Return a bool, true if provider with "ProviderID" exist
    return Database::getInstance().searchProvider(ProviderID); // UNCOMMENTS WHEN DATABASE IS READY
    //return false;
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
    return Database::getInstance().update(providerID, "Users", newAddrss, newCty, newState, newZip); // UNCOMMENTS WHEN DATABASE IS READY
    //return false;
}

Member ChocAnSystem::getMember(const std::string & memberID)
{
    Member updateMember;
    // return a member obj base on Member id
    //updateMember = Database::getInstance().getMember(memberID);   // UNCOMMENT WHEN DATABASE IS READY
    return updateMember;
}


bool ChocAnSystem::deleteProvider(const std::string &ProviderID)
{
    // Return a bool
    return Database::getInstance().deleteUser("Users", ProviderID); // UNCOMMENTS WHEN DATABASE IS READY
    //return false;
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

