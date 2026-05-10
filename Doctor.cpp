#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

#include "Doctor.h"

Doctor::Doctor()
{
	specialization = "";
	contact[0] = '\0';
	fee = 0.0;
}

Doctor::Doctor(int id, const char* name, const char* password, string specialization, const char* contact, float fee)
	: Person(id, name, password)
{
	this->specialization = specialization;
	this->fee = fee;
	strcpy_s(this->contact, contact);
}

bool Doctor::operator==(const Doctor& d)
{
	return (_id == d._id);
}

ostream& operator<<(ostream& out, const Doctor& d)
{
	out << d.getID() << ","
		<< d.getName() << ","
		<< d.getSpecialization() << ","
		<< d.getContact() << ","
		<< d.getPassword() << ","
		<< d.getFee();

	return out;
}

istream& operator>>(istream& in, Doctor& d)
{
    string line;
    getline(in, line);

    if (line.empty()) 
        return in;

    stringstream ss(line);
    string temp;

    getline(ss, temp, ',');
    d.setID(stoi(temp));

    getline(ss, temp, ',');
    d.setName(temp.c_str());

    getline(ss, temp, ',');
    d.setSpecialization(temp);

    getline(ss, temp, ',');
    d.setContact(temp.c_str());

    getline(ss, temp, ',');
    d.setPassword(temp.c_str());

    getline(ss, temp, ',');
    d.setFee(stof(temp));

    return in;
}

void Doctor::display() const
{
    cout << "Display: " << _id << " | ";
    cout << name << " | ";

    cout << specialization << " | ";
    cout << contact << " | ";
    cout << fee;
}

void Doctor::input()
{
    string temp;

    cout << "Enter Doctors Name: ";
    getline(cin, temp);

    if (!Validator::isValidString(temp, 50)) 
        temp = temp.substr(0, 50); //Reduce to 50 char max

    setName(temp.c_str());

    cout << "Enter Specialization: ";
    getline(cin, specialization);
    if (!Validator::isValidString(specialization, 50)) 
        specialization = specialization.substr(0, 50);

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
                setPassword(temp.c_str());
                passValid = true;
            } 
            else cout << "Invalid password.\n";
        }
    }

    while (true) {
        cout << "Enter Fee: ";
        string Fee;

        getline(cin, Fee);
        try 
        {
            fee = stof(Fee);
            if (Validator::isPositiveFloat(fee))
                break;
        } 
        catch(...) 
        {}
        cout << "Invalid fee.\n";
    }
}