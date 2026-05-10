#include <iostream>
#include <cstring>
using namespace std;

#include "HospitalException.h"

HospitalException::HospitalException(const char* msg)
{
    strcpy_s(message, msg);
    message[199] = '\0';
}

const char* HospitalException::what() const
{
    return message;
}