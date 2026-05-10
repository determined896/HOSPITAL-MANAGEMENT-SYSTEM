#include <iostream>
using namespace std;

#include "Date.h"
#include "Validator.h"

Date::Date()
{
    day = 1;
    month = 1;
    year = 2000;
}

Date::Date(int d, int m, int y)
{
    if (Validator::isValidDate(d, m, y))
    {
        day = d;
        month = m;
        year = y;
    }
    else 
    {
        day = 1;
        month = 1;
        year = 2000;
        cout << "Invalid date! Set to 01/01/2000\n";
    }
}

bool Date::setDate(int d, int m, int y) 
{
    if (Validator::isValidDate(d, m, y))
    {
        day = d;
        month = m;
        year = y;
        return true;
    }
    return false;
}

void Date::display() const
{
    cout << (day < 10 ? "0" : "") << day << "/"
        << (month < 10 ? "0" : "") << month << "/"
        << year;
}

bool Date::setDay(int d) 
{
    if (Validator::isValidDate(d, month, year))
    {
        day = d;
        return true;
    }
    return false;
}

bool Date::setMonth(int m) 
{
    if (Validator::isValidDate(day, m, year))
    {
        month = m;
        return true;
    }
    return false;
}

bool Date::setYear(int y) 
{
    if (Validator::isValidDate(day, month, y)) 
    {
        year = y;
        return true;
    }
    return false;
}