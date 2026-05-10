#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

#include "Patient.h"
#include "Person.h"
#include "Validator.h"

Patient::Patient()
{
	age = 0;
	gender = 'X';
	contact[0] = '\0';
	balance = 0.0;
}

Patient::Patient(int id, const char* name, int age, char gender, const char* contact, const char* password, float balance)
	: Person(id, name, password)
{
	this->age = age;
	this->balance = balance;
	this->gender = gender;
	strcpy_s(this->contact, contact);
}

Patient& Patient::operator+=(int amount)
{
	balance += amount;
	return *this;
}
Patient& Patient::operator-=(int amount)
{
    if (balance >= amount)
        balance -= amount;
	return *this;
}
bool Patient::operator==(const Patient& p) const
{
	return (_id == p._id);
}

ostream& operator<<(ostream& out, const Patient& p)
{
    out << p._id << ","
        << p.name << ","
        << p.age << ","
        << p.gender << ","
        << p.contact << ","
        << p.password << ","
        << p.balance;

	return out;
}

istream& operator>>(istream& in, Patient& p)
{
    string line;
    getline(in, line);

    if (line.empty()) 
        return in;

    stringstream ss(line);
    string temp;

    getline(ss, temp, ',');
    p.setID(stoi(temp));

    getline(ss, temp, ',');
    p.setName(temp.c_str());

    getline(ss, temp, ',');
    p.setAge(stoi(temp));

    getline(ss, temp, ',');
    p.setGender(temp[0]);

    getline(ss, temp, ',');
    strcpy_s(p.contact, 12, temp.c_str());
    p.contact[11] = '\0';

    getline(ss, temp, ',');
    p.setPassword(temp.c_str());

    getline(ss, temp, ',');
    p.setBalance(stof(temp));

    return in;
}

void Patient::display() const
{

    cout << "Display: " << _id << " | ";
    cout << name << " | ";

    cout << age << " | ";
    cout << gender << " | ";
    cout << contact << " | ";
    cout << balance << " | ";
}

void Patient::input()
{
    string temp;

    cout << "Enter Patient Name: ";
    getline(cin, temp);
    if (!Validator::isValidString(temp, 50))
        temp = temp.substr(0, 50);
    setName(temp.c_str());

    int ageVal = 0;

    while (!Validator::isValidAge(ageVal))
    {
        cout << "Enter Age: ";
        string ageStr;
        getline(cin, ageStr);
        try 
        { 
            ageVal = stoi(ageStr);
         }
        catch (...) 
        { 
            ageVal = 0; 
        }

        if (!Validator::isValidAge(ageVal))
            cout << "Invalid age.\n";
    }
    age = ageVal;

    while (true)
    {
        cout << "Enter Gender (M/F): ";
        getline(cin, temp);
        if (Validator::isValidGender(temp))
        {
            gender = toupper(temp[0]);
            break;
        }
        cout << "Invalid gender.\n";
    }

    bool contactValid = false, passValid = false;
    while (!contactValid || !passValid)
    {
        if (!contactValid)
        {
            cout << "Enter Contact: ";
            getline(cin, temp);
            if (Validator::isValidNumber(temp)) 
            {
                 setContact(temp.c_str()); 
                 contactValid = true; 
            }
            else cout << "Invalid contact.\n";
        }
        else if (!passValid)
        {
            cout << "Enter Password: ";
            getline(cin, temp);
            if (Validator::isValidPassword(temp))
            { 
                setPassword(temp.c_str()); passValid = true; 
            }
            else cout << "Invalid password.\n";
        }
    }

    balance = 0.0f;
}