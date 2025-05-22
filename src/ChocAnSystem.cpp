#include <iostream>
#include "ChocAnSystem.h"

using namespace std;

ChocAnSystem::ChocAnSystem()
{}

ChocAnSystem::~ChocAnSystem()
{}

ChocAnSystem& ChocAnSystem::getInstance()
{
    static ChocAnSystem instance;
    return instance;
}

int ChocAnSystem::authenticateUser(const std::string userID)
{
    // Call to Database::getInstance().authenticateUser(userID)
    return Database::getInstance().authenticateUser(userID);
}

int ChocAnSystem::validateMembership(std::string memberID)
{
    // Uncomment this when database ready
    //Database::getInstance().validateMembership(memberID);
    return 0;
}

void ChocAnSystem::getProviderDirectory()
{
    // call to vector<service> list = Database::getInstance().getProviderDirectory()
    // Output the vector here (Provider Directory)
    cout << "\nPROVIDER DIRECTORY" << endl;
    // display here
}
