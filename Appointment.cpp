#include <iostream>
#include <sstream>
using namespace std;

#include "Appointment.h"
#include "Patient.h"
#include "Doctor.h"

Appointment::Appointment()
{
    appointment_id = 0;
    patient = nullptr;
    doctor = nullptr;
    state = PENDING;
    patientID = 0;
    doctorID = 0;
}

Appointment::Appointment(int id, Patient* p, Doctor* d, const Time& t, const Date& dt, Status s, int Pid = 0, int Did = 0)
{
    appointment_id = id;
    patient = p;
    doctor = d;
    time = t;
    date = dt;
    state = s;
    patientID = Pid;
    doctorID = Did;
}

void Appointment::display() const
{
    cout << "Display: " << appointment_id << " | ";

    if (patient)
        cout << patientID << " | ";

    if (doctor)
        cout << doctorID << " | ";

    date.display();
    cout << " | ";

    time.display();
    cout << " | ";

    if (state == PENDING) cout << "Pending";
    else if (state == COMPLETED) cout << "Confirmed";
    else if (state == CANCELLED) cout << "Cancelled";
    else if (state == NO_SHOW) cout << "No_Show";

}

ostream& operator<<(ostream& out, const Appointment& a)
{
    out << a.getID() << ","
        << a.getPatientID() << ","
        << a.getDoctorID() << ",";

    out << a.getDate().getDay() << "-"
        << a.getDate().getMonth() << "-"
        << a.getDate().getYear() << ",";

    out << a.getTime().getHours() << ":"
        << a.getTime().getMinutes() << ":"
        << a.getTime().getSeconds() << ",";

    if (a.getStatus() == COMPLETED)
        out << "completed";
    else if (a.getStatus() == CANCELLED)
        out << "cancelled";
    else if (a.getStatus() == NO_SHOW)
        out << "no_show";
    else
        out << "pending";

    return out;
}

istream& operator>>(istream& in, Appointment& a)
{
    string line;
    getline(in, line);

    if (line.empty()) 
        return in;

    stringstream ss(line);
    string temp;

    int patient_id, doctor_id;

    getline(ss, temp, ',');
    a.setID(stoi(temp));

    getline(ss, temp, ',');
    a.setPatientID(stoi(temp));

    getline(ss, temp, ',');
    a.setDoctorID(stoi(temp));

    getline(ss, temp, '-');
    int d = stoi(temp);
    getline(ss, temp, '-');
    int m = stoi(temp);
    getline(ss, temp, ',');
    int y = stoi(temp);
    a.date.setDate(d, m, y);
    
    getline(ss, temp, ':');
    int hr = stoi(temp);
    getline(ss, temp, ':');
    int min = stoi(temp);
    getline(ss, temp, ',');
    int sec = stoi(temp);
    a.time.setTime(hr, min, sec);
    
    getline(ss, temp, ',');

    if (temp == "completed")
        a.state = COMPLETED;
    else if (temp == "cancelled")
        a.state = CANCELLED;
    else if (temp == "pending")
        a.state = PENDING;
    else
        a.state = NO_SHOW;

    return in;
}

bool Appointment::operator==(const Appointment& other) const
{
    if (state == CANCELLED|| other.state == CANCELLED || state == NO_SHOW || other.state == NO_SHOW)
        return false;

    return (doctorID == other.doctorID &&
        date.getDay() == other.date.getDay() &&
        date.getMonth() == other.date.getMonth() &&
        date.getYear() == other.date.getYear() &&
        time.getHours() == other.time.getHours() &&
        time.getMinutes() == other.time.getMinutes() &&
        time.getSeconds() == other.time.getSeconds());
}


void Appointment::input()
{
    int d, m, y;
    int hr, min, sec;
    int statusChoice;

    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    cout << "Enter Date (DD MM YYYY): ";
    cin >> d >> m >> y;
    date.setDate(d, m, y);

    cout << "Enter Time (HH MM SS): ";
    cin >> hr >> min >> sec;
    time.setTime(hr, min, sec);

    cout << "Select Status:\n";
    cout << "1. Pending\n";
    cout << "2. Completed\n";
    cout << "3. Cancelled\n";
    cout << "4. No Show\n";

    cin >> statusChoice;

    if (statusChoice == 1)
        state = PENDING;
    else if (statusChoice == 2)
        state = COMPLETED;
    else if (statusChoice == 3)
        state = CANCELLED;
    else
        state = NO_SHOW;
}