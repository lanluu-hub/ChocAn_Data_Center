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