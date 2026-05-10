#include <iostream>
#include <sstream>
using namespace std;

#include "Prescription.h"

Prescription::Prescription()
{
    pres_id = 0;
    appoint = nullptr;
    patient = nullptr;
    doctor = nullptr;
    medicine = "";
    notes = "";
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
}

Prescription::Prescription(int id, Appointment* a, Patient* p, Doctor* d,
    const Date& dt, const string& med, const string& n, int Aid = 0, int Pid = 0, int Did = 0)
    : pres_id(id), appoint(a), patient(p), doctor(d),
    date(dt), medicine(med), notes(n), appointmentID(Aid), patientID(Pid), doctorID(Did)
{ }

void Prescription::display() const
{
    date.display();
    cout << " | " << (doctor ? doctor->getName() : "Unknown") << " | "
         << medicine << " | " << notes << endl;
}

ostream& operator<<(ostream& out, const Prescription& p)
{
    out << p.getID() << ","
        << p.getAppointmentID() << ","
        << p.getPatientID() << ","
        << p.getDoctorID() << ",";

    out << p.date.getDay() << "-"
        << p.date.getMonth() << "-"
        << p.date.getYear() << ",";

    out << p.getMedicine() << ","
        << p.getNotes();

    return out;
}

istream& operator>>(istream& in, Prescription& p)
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
    p.setAppointmentID(stoi(temp));;

    getline(ss, temp, ',');
    p.setPatientID(stoi(temp));;

    getline(ss, temp, ',');
    p.setDoctorID(stoi(temp));

    getline(ss, temp, '-');
    int d = stoi(temp);
    getline(ss, temp, '-');
    int m = stoi(temp);
    getline(ss, temp, ',');
    int y = stoi(temp);
    p.date.setDate(d, m, y);
    
    getline(ss, temp, ',');
    p.setMedicine(temp);

    getline(ss, temp, ',');
    p.setNotes(temp);

    return in;
}

void Prescription::input()
{
    int d, m, y;

    cout << "Enter Prescription ID: ";
    cin >> pres_id;

    cout << "Enter Appointment ID: ";
    cin >> appointmentID;

    cout << "Enter Patient ID: ";
    cin >> patientID;

    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    cout << "Enter Date (DD MM YYYY): ";
    cin >> d >> m >> y;

    date.setDate(d, m, y);

    cin.ignore();

    cout << "Enter Medicine: ";
    getline(cin, medicine);

    cout << "Enter Notes: ";
    getline(cin, notes);
}