#include "Service.h"

Service::Service(int s_code, std::string s_name, float s_fee)
{
    serviceCode = s_code;
    serviceName = s_name.substr(0, 20);
    serviceFee = s_fee;
}

Service::~Service()
{
}
