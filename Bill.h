#pragma once
#include <string>

#include "Patient.h";
#include "Date.h";
#include "Appointment.h";

enum Status_Bill
{
	PAID,
	UNPAID,
    CANCELLED_BILL
};

class Bill
{
    friend istream& operator>>(istream& in, Bill& b);
    friend ostream& operator<<(ostream& out, const Bill& b);
private:
	int bills_id;
	Patient* patient;
	Appointment* appoint;
	float amount;
	Status_Bill status;
	Date date;

    int patientID;
    int appointmentID;
public:
    Bill();
    Bill(int id, Patient* p, Appointment* a, float amt, Status_Bill s, const Date& d, int Pid, int Aid);

    void setID(int id) { bills_id = id; }
    void setPatient(Patient* p) { patient = p; }
    void setAppointment(Appointment* a) { appoint = a; }
    void setAmount(float amt) { amount = amt; }
    void setStatus(Status_Bill s) { status = s; }
    void setDate(const Date& d) { date = d; }
    void setPatientID(int _id) { patientID = _id; }
    void setAppointmentID(int _id) { appointmentID = _id; }

    int getID() const { return bills_id; }
    Patient* getPatient() const { return patient; }
    Appointment* getAppointment() const { return appoint; }
    float getAmount() const { return amount; }
    Status_Bill getStatus() const { return status; }
    Date getDate() const { return date; }
    int getPatientID() const { return patientID; }
    int getAppointmentID() const { return appointmentID; }

    void display(const char* patientName) const;
    void input();
};