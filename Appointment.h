#pragma once
#include <string>

#include "Doctor.h";
#include "Patient.h";
#include "Time.h";
#include "Date.h";

enum Status 
{
	PENDING,
	COMPLETED,
	CANCELLED,
    NO_SHOW
};

class Appointment
{
    friend ostream& operator<<(ostream& out, const Appointment& a);
    friend istream& operator>>(istream& in, Appointment& a);
private:
	int appointment_id;
	Patient* patient;
	Doctor* doctor;
	Time time;
	Date date;
	Status state;

    int patientID;
    int doctorID;

public:
    Appointment();
    Appointment(int id, Patient* p, Doctor* d, const Time& t, const Date& dt, Status s, int Pid, int Did);

    void setID(int id) { appointment_id = id; }
    void setPatient(Patient* p) { patient = p; }
    void setDoctor(Doctor* d) { doctor = d; }
    void setTime(const Time& t) { time = t; }
    void setDate(const Date& d) { date = d; }
    void setStatus(Status s) { state = s; }
    void setPatientID(int _id) { patientID = _id; }
    void setDoctorID(int _id) { doctorID = _id; }

    int getID() const { return appointment_id; }
    Patient* getPatient() const { return patient; }
    Doctor* getDoctor() const { return doctor; }
    Time getTime() const { return time; }
    Date getDate() const { return date; }
    Status getStatus() const { return state; }
    int getPatientID() const { return patientID; }
    int getDoctorID() const { return doctorID; }

    void display() const;
    bool operator==(const Appointment& other) const;

    void input();
};
