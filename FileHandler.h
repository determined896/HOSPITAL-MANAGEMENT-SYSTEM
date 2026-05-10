#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#include "Storage.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"

class FileHandler
{
public:
	template <typename T>
	static void load(const string& filename, Storage<T>& storage);

	template <typename T>
	static void save(const string& filename, Storage<T>& storage);

	template <typename T>
	static void append(const string& filename, const T& obj);

	template <typename T>
	static void removeID(const string& filename, int id);

	template <typename T>
	static void update(const string& filename, const T& obj);

    template <typename T>
    static void removePatientRecords(const string& filename, int patientID);

	static void linkAppointments(Storage<Appointment>& apps, Storage<Patient>& patients, Storage<Doctor>& doctors);

	static void linkBills(Storage<Bill>& bills, Storage<Patient>& patients, Storage<Appointment>& apps);

	static void linkPrescriptions(Storage<Prescription>& pres, Storage<Appointment>& apps, Storage<Patient>& patients, Storage<Doctor>& doctors);

    static void writeLogs(const string& role, int id, const string& result);

    static void viewSecurityLog();

};


template <typename T>
void FileHandler::load(const string& filename, Storage<T>& storage)
{
    ifstream fin(filename);

    if (!fin.is_open())
        return;

    string str;
    getline(fin, str);

    T obj;
    while (fin >> obj)
    {
        storage.add(obj);
    }

    fin.close();
}

template <typename T>
void FileHandler::save(const string& filename, Storage<T>& storage)
{
    ofstream fout(filename);

    for (int i = 0; i < storage.size(); i++)
    {
        fout << storage.getData()[i] << "\n";
    }
    fout.close();
}

template <typename T>
void FileHandler::append(const string& filename, const T& obj)
{
    ofstream fout(filename, ios::app);
    fout << obj << "\n";
    fout.close();
}

template <typename T>
void FileHandler::removeID(const string& filename, int id)
{
    ifstream fin(filename);
    ofstream temp("temp.txt");

    if (!fin.is_open())
        return;

    string header;
    getline(fin, header);

    temp << header << "\n";

    T obj;

    while (!fin.eof())
    {
        fin >> obj;

        if (fin.fail())
            break;

        if (obj.getID() != id)
            temp << obj << "\n";
    }

    fin.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

template <typename T>
void FileHandler::update(const string& filename, const T& obj)
{
    ifstream fin(filename);
    ofstream temp("temp.txt");

    if (!fin.is_open())
        return;

    string header;
    getline(fin, header);
    temp << header << "\n";

    T tempObj;
    while (fin >> tempObj)
    {
        if (fin.fail() || fin.eof())
            break;

        if (tempObj.getID() == obj.getID())
            temp << obj << "\n";
        else
            temp << tempObj << "\n";
    }

    fin.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

template <typename T>
void FileHandler::removePatientRecords(const string& filename, int patientID)
{
    ifstream fin(filename);
    ofstream temp("temp.txt");

    if (!fin.is_open())
        return;

    string header;
    getline(fin, header);

    temp << header << "\n";

    T obj;

    while (!fin.eof())
    {
        fin >> obj;

        if (fin.fail())
            break;

        if (obj.getPatientID() != patientID)
            temp << obj << "\n";
    }

    fin.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}
