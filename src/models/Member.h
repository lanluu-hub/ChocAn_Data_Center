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
        Member(const std::string& m_name = "Unkown", const std::string& m_ID = "000000000"
                , const std::string& m_strAddr = "N/A", const std::string& m_cty = "N/A"
                , const std::string& m_state = "N/A", const std::string& m_zip = "00000");
        ~Member();
        void displayMember() const;
        bool isEmpty() const;

    protected:
        std::string memberName;             // 25 Characters
        std::string memberID;               // 9 digits
        std::string memberStreetAddress;    // 25 characters
        std::string memberCity;             // 14 characters
        std::string memberState;            // 2 letters
        std::string memberZipCode;          // 5 digits

        friend class ChocAnSystem;
        friend class Database;
};

#endif