#pragma once
#include <cstring>


class HospitalException
{
protected:
    char message[200];

public:
    HospitalException(const char* msg = "Hospital Exception");

    virtual const char* what() const;
    virtual ~HospitalException() {}
};

class FileNotFoundException : public HospitalException
{
public:
    FileNotFoundException(const char* msg = "File not found")
        : HospitalException(msg)
    { }
};

class InvalidInputException : public HospitalException
{
public:
    InvalidInputException(const char* msg = "Invalid input")
        : HospitalException(msg)
    { }
};

class InsufficientFundsException : public HospitalException
{
public:
    InsufficientFundsException(const char* msg = "Insufficient funds")
        : HospitalException(msg)
    { }
};

class SlotUnavailableException : public HospitalException
{
public:
    SlotUnavailableException(const char* msg = "Slot unavailable")
        : HospitalException(msg)
    {}
};