#include "Service.h"

Service::Service(std::string s_code, std::string s_name, float s_fee)
{
    serviceCode = s_code.substr(0, 6);
    serviceName = s_name.substr(0, 20);
    serviceFee = s_fee;
}

Service::~Service()
{
}
