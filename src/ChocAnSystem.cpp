#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include "ChocAnSystem.h"


using namespace std;

ChocAnSystem::ChocAnSystem()
{}

ChocAnSystem::~ChocAnSystem()
{}

string ChocAnSystem::dateTime(const chrono::system_clock::time_point &timePoint, const string &format)
{
    time_t time = chrono::system_clock::to_time_t(timePoint);
    tm* timeinfo = localtime(&time);
    char buffer[70];
    strftime(buffer, sizeof(buffer), format.c_str(),
            timeinfo);
    return buffer;
}

ChocAnSystem& ChocAnSystem::getInstance()
{
    static ChocAnSystem instance;
    return instance;
}

int ChocAnSystem::authenticateUser(const string& userID)
{
    // Call to Database::getInstance().authenticateUser(userID)
    return Database::getInstance().authenticateUser(userID);
}

int ChocAnSystem::validateMembership(string& memberID)
{
    // Uncomment this when database ready
    //Database::getInstance().validateMembership(memberID);
    return 0;
}

float ChocAnSystem::getServiceFee(const string& servCode)
{
    // make new Service Obj
    Service service;

    // Call to Database::getInstance().getService(servCode); Return a Service Obj assignt to ServObj
    // Database::getInstance().getService(servCode);
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

    // Call to Database::getInstance().serviceLog(providerID, memberID, serviceCode
    //                                            , serviceDate, currentDate, serviceComment);
    // return a bool: result of the service Log
    return false;
}

void ChocAnSystem::getProviderDirectory()
{
    // call to vector<service> list = Database::getInstance().getProviderDirectory()
    vector<Service> providerDirectory = Database::getInstance().getProviderDirectory();  // Uncomment this when Database is ready
    //vector<Service> providerDirectory; 

    // Output the vector here (Provider Directory)
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

////////// Helper function /////////
