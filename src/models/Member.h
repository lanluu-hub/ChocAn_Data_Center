/*
 * Created: May 16, 2025
 *----------------------------- 
 * Member.h
 * A class to hold each member attributes.
 *
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef MEMBER_H
#define MEMBER_H
#include <string>


class Member {
    public:
        Member(std::string m_name, int m_ID, std::string m_strAddr, std::string m_cty, std::string m_state, std::string m_zip);
        ~Member();
        void displayMember() const;

    protected:
        std::string memberName;             // 25 Characters
        int         memberID;               // 9 digits
        std::string memberStreetAddress;    // 25 characters
        std::string memberCity;             // 14 characters
        std::string memberState;            // 2 letters
        std::string memberZipCode;          // 5 digits
};

#endif