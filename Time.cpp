#include <iostream>
using namespace std;

#include "Time.h"
#include "Validator.h"

Time::Time() 
{
    hours = 0;
    minutes = 0;
    seconds = 0;
}

Time::Time(int h, int m, int s) 
{
    if (Validator::isValidTime(h, m, s)) 
    {
        hours = h;
        minutes = m;
        seconds = s;
    }
    else 
    {
        hours = minutes = seconds = 0;
        cout << "Invalid time! Set to 00:00:00\n";
    }
}

bool Time::setTime(int h, int m, int s)
{
    if (Validator::isValidTime(h, m, s)) 
    {
        hours = h;
        minutes = m;
        seconds = s;
        return true;
    }
    return false;
}

void Time::display() const
{
    cout << (hours < 10 ? "0" : "") << hours << ":"
        << (minutes < 10 ? "0" : "") << minutes << ":"
        << (seconds < 10 ? "0" : "") << seconds;
}

bool Time::setHours(int h) 
{
    if (h >= 0 && h < 24) 
    {
        hours = h;
        return true;
    }
    return false;
}

bool Time::setMinutes(int m) 
{
    if (m >= 0 && m < 60) 
    {
        minutes = m;
        return true;
    }
    return false;
}

bool Time::setSeconds(int s) 
{
    if (s >= 0 && s < 60)
    {
        seconds = s;
        return true;
    }
    return false;
}