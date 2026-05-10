#pragma once
#include <string>
#include <cstring>

#include "Date.h";
#include "Time.h";
#include "HospitalException.h"

class Validator
{
public:
    static bool isValidID(int id);
    static bool isValidNumber(const string& number);
    static bool isLeapYear(int y);
    static bool isValidTime(int h, int m, int s);
    static bool isValidDate(int d, int m, int y);
    static bool isValidPassword(const string& pass);
    static bool isPositiveFloat(float value);
    static bool isMenuChoice(int choice);
    static bool isValidPasswordMatch(const char* input, const char* stored);
    static int isIDNumeric(const string& input);
    static bool isValidString(const string& str, int maxLen);
    static bool isValidAge(int age);
    static bool isValidGender(const string& g);
};

