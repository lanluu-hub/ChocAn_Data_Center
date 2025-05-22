#include "ChocAnSystem.h"

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