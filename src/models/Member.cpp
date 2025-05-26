#include <iostream>
#include "Member.h"

Member::Member(const std::string &m_name
              , const std::string &m_ID
              , const std::string &m_strAddr
              , const std::string &m_cty
              , const std::string &m_state
              , const std::string &m_zip):
                memberName(m_name.substr(0, 25)), memberID(m_ID.substr(0, 9))
                , memberStreetAddress(m_strAddr.substr(0, 25)), memberCity(m_cty.substr(0, 14))
                , memberState(m_state.substr(0, 2)), memberZipCode(m_zip.substr(0, 5))
{}

Member::~Member()
{
}

void Member::displayMember() const
{
    std::cout << "Member name: " << memberName << std::endl;
    std::cout << "Member number: " << memberID << std::endl;
    std::cout << "Member street address: " << memberStreetAddress << std::endl;
    std::cout << "Member city: " << memberCity << std::endl;
    std::cout << "Member state: " << memberState << std::endl;
    std::cout << "Member zip code: " << memberZipCode << std::endl;
}
