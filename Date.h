#pragma once

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);

    bool setDay(int d);
    bool setMonth(int m);
    bool setYear(int y);
    bool setDate(int d, int m, int y);

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    void display() const;
};