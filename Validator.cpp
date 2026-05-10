#include <iostream>
using namespace std;

#include "Validator.h"

bool Validator::isValidID(int id) 
{
    return id > 0;
}

bool Validator::isPositiveFloat(float value) 
{
    return value > 0.0f;
}

bool Validator::isMenuChoice(int choice) 
{
    return (choice >= 1 && choice <= 5);
}

bool Validator::isValidNumber(const string& number)
{
    if (number.length() != 11)
        return false;

    if (!(number[0] == '0' && number[1] == '3'))
        return false;
    for (int i = 2; i < 11; i++)
        if (number[i] < '0' || number[i] > '9')
            return false;

    return true;
}

bool Validator::isValidTime(int h, int m, int s)
{
    return (h >= 0 && h < 24 &&
        m >= 0 && m < 60 &&
        s >= 0 && s < 60);
}

bool Validator::isLeapYear(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool Validator::isValidDate(int d, int m, int y)
{
    if (y < 0) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;

    int days = 0;

    if (m == 1 || m == 3 || m == 5 || m == 7 ||
        m == 8 || m == 10 || m == 12)
        days = 31;
    else if (m == 4 || m == 6 || m == 9 || m == 11)
        days = 30;

    else if (m == 2)
        if (isLeapYear(y))
            days = 29;
        else
            days = 28;

    else
        return false;


    return d <= days;
}

bool Validator::isValidPassword(const string& pass)
{
    if (pass.length() < 6)
        return false;

    bool Letter = false;
    bool Digit = false;

    for (int i = 0; i < pass.length(); i++)
    {
        char character = pass[i];

        if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
            Letter = true;

        if (character >= '0' && character <= '9')
            Digit = true;
    }

    return Letter && Digit;
}

bool Validator::isValidPasswordMatch(const char* input, const char* stored)
{
    if (!input || !stored)
        return false;

    return strcmp(input, stored) == 0;
}

int Validator::isIDNumeric(const string& input)
{
    if (input.empty())
        throw HospitalException("ID cannot be empty");

    for (int i = 0; i < strlen(input.c_str()); i++)
    {
        if (!isdigit(input[i]))
            throw HospitalException("ID must be numeric only");
    }

    return stoi(input);
}

bool Validator::isValidString(const string& str, int maxLen)
{
    return !str.empty() && str.length() <= maxLen;
}

bool Validator::isValidAge(int age)
{
    return age > 0 && age <= 100;
}

bool Validator::isValidGender(const string& g)
{
    return g == "M" || g == "m" || g == "F" || g == "f";
}