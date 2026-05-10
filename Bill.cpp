#include <iostream>
#include <sstream>
using namespace std;

#include "Bill.h"

Bill::Bill()
{
    bills_id = 0;
    patient = nullptr;
    appoint = nullptr;
    amount = 0.0;
    status = UNPAID;
    patientID = 0;
    appointmentID = 0;
}

Bill::Bill(int id, Patient* p, Appointment* a, float amt, Status_Bill s, const Date& d, int Pid = 0, int Aid = 0)
{
    bills_id = id;
    patient = p;
    appoint = a;
    amount = amt;
    status = s;
    date = d;
    patientID = Pid;
    appointmentID = Aid;
}

void Bill::display(const char* patientName) const
{
    tm billDate = {};
    billDate.tm_mday = date.getDay();
    billDate.tm_mon = date.getMonth() - 1;
    billDate.tm_year = date.getYear() - 1900;
    time_t billTime = mktime(&billDate);

    time_t now = time(0);
    double days = difftime(now, billTime) / (60 * 60 * 24);

    cout << bills_id << " | "
        << patientName << " | "
        << amount << " PKR | ";

    date.display();  // uses your existing Date::display()

    if (days > 7)
        cout << " [OVERDUE]";

    cout << "\n";
}

istream& operator>>(istream& in, Bill& b)
{
    string line;
    getline(in, line);

    if (line.empty()) 
        return in;

    stringstream ss(line);
    string temp;

    getline(ss, temp, ',');
    b.setID(stoi(temp));

    getline(ss, temp, ',');
    b.setPatientID(stoi(temp));

    getline(ss, temp, ',');
    b.setAppointmentID(stoi(temp));

    getline(ss, temp, ',');
    b.setAmount(stof(temp));

    getline(ss, temp, ',');

    if (temp == "paid")
        b.setStatus(PAID);
    else if (temp == "cancelled")
        b.setStatus(CANCELLED_BILL);
    else
        b.setStatus(UNPAID);
    
    getline(ss, temp, '-');
    int d = stoi(temp);
    getline(ss, temp, '-');
    int m = stoi(temp);
    getline(ss, temp, ',');
    int y = stoi(temp);
    b.date.setDate(d, m, y);


    return in;
}

ostream& operator<<(ostream& out, const Bill& b)
{
    out << b.getID() << ","
        << b.getPatientID() << ","
        << b.getAppointmentID() << ","
        << b.getAmount() << ",";

    if (b.getStatus() == PAID)
        out << "paid";
    else if (b.getStatus() == CANCELLED_BILL)
        out << "cancelled";
    else
        out << "unpaid";

    out << ",";

    out << b.date.getDay() << "-"
        << b.date.getMonth() << "-"
        << b.date.getYear();

    return out;
}

void Bill::input()
{
    int d, m, y;
    int statusChoice;

    cout << "Enter Bill ID: ";
    cin >> bills_id;

    cout << "Enter Patient ID: ";
    cin >> patientID;

    cout << "Enter Appointment ID: ";
    cin >> appointmentID;

    cout << "Enter Amount: ";
    cin >> amount;

    cout << "1. Paid\n";
    cout << "2. Unpaid\n";

    cin >> statusChoice;

    if (statusChoice == 1)
        status = PAID;
    else
        status = UNPAID;

    cout << "Enter Date (DD MM YYYY): ";
    cin >> d >> m >> y;

    date.setDate(d, m, y);
}