/*
 * Created: May 17, 2025
 *----------------------------- 
 * ChocAnSystem.h
 * 
 * This file defines the ChocAnSystem class, which serves as the core controller
 * for the ChocAn Data Processing System. It provides centralized access to 
 * business logic and system operations such as member validation, service logging, 
 * report generation, and coordination with the Database subsystem.
 *
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef CHOCAN_SYSTEM_H
#define CHOCAN_SYSTEM_H
#include <iostream>

class ChocAnSystem {
    public:
        // delete Copy constructor to prevent copy
        ChocAnSystem(const ChocAnSystem& obj) = delete;
        
        // Returns the thread-safe, lazily-initialized Singleton instance.
        // This ensures only one shared ChocAnSystem exists across the application. 
        // Usage:
        //     ChocAnSystem::getInstance().validateMember(...);
        //     ChocAnSystem::getInstance().billService(...);
        // Syntax: ChocAnSystem::getInstance().[Public_Function_Here]();
        static ChocAnSystem& getInstance();

        // Other Public Fucntion here: 

        // Test function, use ChocAnSystem::getIntance().test_output() in main, or any function to check it work
        void test_output() {std::cout << "Hello World!" << std::endl;}  

    private:
        // Private Constructor
        ChocAnSystem();
        ~ChocAnSystem();
};

#endif