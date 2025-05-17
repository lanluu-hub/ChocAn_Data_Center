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
        Provider(std::string p_name, int p_ID, std::string p_strAddr, std::string p_cty, std::string p_state, std::string p_zip);
        ~Provider();
        void displayProvider() const;

    protected:
        std::string providerName;             // 25 Characters
        int         providerID;               // 9 digits
        std::string providerStreetAddress;    // 25 characters
        std::string providerCity;             // 14 characters
        std::string providerState;            // 2 letters
        std::string providerZipCode;          // 5 digits
};

#endif