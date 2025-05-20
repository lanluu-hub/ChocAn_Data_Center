/*
 * Created: May 16, 2025
 *----------------------------- 
 * Service.h
 * A class to hold service attribute
 *
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */
#ifndef SERVICE_H
#define SERVICE_H
#include <string>

class Service {
    public:
        Service(std::string s_code, std::string s_name, float s_fee);
        ~Service();

    protected:
        std::string serviceCode;    // 6 digits code
        std::string serviceName;
        float serviceFee;
};

#endif