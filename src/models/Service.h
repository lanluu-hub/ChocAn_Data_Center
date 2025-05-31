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
#include "../ChocAnSystem.h"

class Service {
    public:
        Service(const std::string& s_code = "000000", const std::string& s_name = "DEFAULT_SERVICE", const float s_fee = 0.00);
        ~Service();

        bool isEmpty() const;

    protected:
        std::string serviceCode;    // 6 digits code
        std::string serviceName;
        float serviceFee;

    // Friend
    friend class ChocAnSystem;
};

#endif