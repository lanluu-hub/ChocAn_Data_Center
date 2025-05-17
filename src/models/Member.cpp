#include <iostream>
#include "Member.h"

Member::Member(std::string m_name, int m_ID, std::string m_strAddr, std::string m_cty, std::string m_state, std::string m_zip)
{
    memberName = m_name.substr(0, 25);
    memberID = m_ID;
    memberStreetAddress = m_strAddr.substr(0, 25);
    memberCity = m_cty.substr(0, 14);
    memberState = m_state.substr(0, 2);
    memberZipCode = m_zip.substr(0, 5);
}

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
