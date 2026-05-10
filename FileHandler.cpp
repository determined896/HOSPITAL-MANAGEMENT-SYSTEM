#include <fstream>
#include <iostream>
using namespace std;

#include "FileHandler.h"

void FileHandler::linkAppointments(Storage<Appointment>& apps, Storage<Patient>& patients, Storage<Doctor>& doctors)
{
    for (int i = 0; i < apps.size(); i++)
    {
        Appointment& a = apps.getData()[i];

        int pid = a.getPatientID();
        int did = a.getDoctorID();

        Patient* p = patients.findID(pid);
        Doctor* d = doctors.findID(did);

        a.setPatient(p);
        a.setDoctor(d);
    }
}

void FileHandler::linkBills(Storage<Bill>& bills, Storage<Patient>& patients, Storage<Appointment>& apps)
{
    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.getData()[i];

        int pid = b.getPatientID();
        int aid = b.getAppointmentID();

        Patient* p = patients.findID(pid);
        Appointment* a = apps.findID(aid);

        b.setPatient(p);
        b.setAppointment(a);
    }
}

void FileHandler::linkPrescriptions(Storage<Prescription>& pres, Storage<Appointment>& apps, Storage<Patient>& patients, Storage<Doctor>& doctors)
{
    for (int i = 0; i < pres.size(); i++)
    {
        Prescription& p = pres.getData()[i];

        int aid = p.getAppointmentID();
        int pid = p.getPatientID();
        int did = p.getDoctorID();

        Appointment* a = apps.findID(aid);
        Patient* pat = patients.findID(pid);
        Doctor* doc = doctors.findID(did);

        p.setAppointment(a);
        p.setPatient(pat);
        p.setDoctor(doc);
    }
}

void FileHandler::writeLogs(const string& role, int id, const string& result)
{
    ofstream fout("security_log.txt", ios::app);

    if (!fout.is_open())
        return;

    time_t now = time(0);

    tm localTime;
    localtime_s(&localTime, &now); 

    fout << (1900 + localTime.tm_year) << "-"
        << (1 + localTime.tm_mon) << "-"
        << localTime.tm_mday << " "
        << localTime.tm_hour << ":"
        << localTime.tm_min << ":"
        << localTime.tm_sec << ","
        << role << ","
        << id << ","
        << result << "\n";

    fout.close();
}

void FileHandler::viewSecurityLog()
{
    ifstream fin("security_log.txt");

    if (!fin.is_open())
    {
        cout << "Failed to open security.txt\n";
        return;
    }

    string line;

    cout << "\n--- SECURITY LOG ---\n";

    while (getline(fin, line))
    {
        cout << line << endl;
    }

    fin.close();
}