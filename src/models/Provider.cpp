#include <iostream>
#include "Provider.h"

Provider::Provider(const std::string& p_name
                   , const std::string& p_ID
                   , const std::string& p_strAddr
                   , const std::string& p_cty
                   , const std::string& p_state
                   , const std::string& p_zip): 
                        providerName(p_name.substr(0, 25)), providerID(p_ID.substr(0, 9))
                        , providerStreetAddress(p_strAddr.substr(0, 25)), providerCity(p_cty.substr(0, 14))
                        , providerState(p_state.substr(0, 2)), providerZipCode(p_zip.substr(0, 5))
{}

Provider::~Provider()
{
}

void Provider::displayProvider() const
{
    std::cout << "Provider name: " << providerName << std::endl;
    std::cout << "Provider number: " << providerID << std::endl;
    std::cout << "Provider street address: " << providerStreetAddress << std::endl;
    std::cout << "Provider city: " << providerCity << std::endl;
    std::cout << "Provider state: " << providerState << std::endl;
    std::cout << "Provider zip code: " << providerZipCode << std::endl;
}
