#pragma once


class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time();
    Time(int h, int m, int s);

    bool setHours(int h);
    bool setMinutes(int m);
    bool setSeconds(int s);
    bool setTime(int h, int m, int s);

    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    void display() const;
};