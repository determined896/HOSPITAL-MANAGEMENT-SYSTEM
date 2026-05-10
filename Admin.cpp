#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

#include "Admin.h"

ostream& operator<<(ostream& out, const Admin& a)
{
    out << a.getID() << ","
        << a.getName() << ","
        << a.getPassword();

    return out;
}

istream& operator>>(istream& in, Admin& a)
{
    string line;
    getline(in, line);

    if (line.empty()) return in;

    stringstream ss(line);
    string temp;

    getline(ss, temp, ',');
    a.setID(stoi(temp));

    getline(ss, temp, ',');
    a.setName(temp.c_str());

    getline(ss, temp, ',');
    a.setPassword(temp.c_str());

    return in;
}

void Admin::display() const
{
    cout << "Admin ID: " << _id << endl;
    cout << "Name: " << name << endl;

    cout << endl;
}

void Admin::input()
{
    string temp;

    cout << "Enter Admins ID: ";
    cin >> _id;

    cin.ignore();

    cout << "Enter Admins Name: ";
    getline(cin, temp);
    setName(temp.c_str());

    cout << "Enter Password: ";
    getline(cin, temp);
    setPassword(temp.c_str());
}

