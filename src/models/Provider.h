/*
 * Created: May 16, 2025
 *----------------------------- 
 * Provider.h
 * A class to hold each Provider attributes.
 *
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef PROVIDER_H
#define PROVIDER_H
#include <string>


class Provider {
    public:
        Provider(const std::string& p_name = "Unkown"
                 , const std::string& p_ID = "000000000"
                 , const std::string& p_strAddr = "N/A"
                 , const std::string& p_cty = "N/A"
                 , const std::string& p_state = "N/A"
                 , const std::string& p_zip = "00000");
        ~Provider();
        void displayProvider() const;
        bool isEmpty() const;

    protected:
        std::string providerName;             // 25 Characters
        std::string providerID;               // 9 digits
        std::string providerStreetAddress;    // 25 characters
        std::string providerCity;             // 14 characters
        std::string providerState;            // 2 letters
        std::string providerZipCode;          // 5 digits

        friend class ChocAnSystem;
        friend class Database;
};

#endif