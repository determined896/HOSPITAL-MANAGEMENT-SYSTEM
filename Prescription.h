#pragma once

#include "Doctor.h";
#include "Patient.h";
#include "Date.h";
#include "Appointment.h"

class Prescription
{
    friend ostream& operator<<(ostream& out, const Prescription& p);
    friend istream& operator>>(istream& in, Prescription& p);

	int pres_id;
	Appointment* appoint;
	Patient* patient;
	Doctor* doctor;
	Date date;
	string medicine;
	string notes;

    int patientID;
    int doctorID;
    int appointmentID;
public:
    Prescription();
    Prescription(int id, Appointment* a, Patient* p, Doctor* d, const Date& dt, const std::string& med, const std::string& n
        , int Aid, int Pid, int Did);

    void setID(int id) { pres_id = id; }
    void setAppointment(Appointment* a) { appoint = a; }
    void setPatient(Patient* p) { patient = p; }
    void setDoctor(Doctor* d) { doctor = d; }
    void setDate(const Date& dt) { date = dt; }
    void setMedicine(const string& med) { medicine = med; }
    void setNotes(const string& n) { notes = n; }
    void setPatientID(int _id) { patientID = _id; }
    void setDoctorID(int _id) { doctorID = _id; }
    void setAppointmentID(int _id) { appointmentID = _id; }

    int getID() const { return pres_id; }
    Appointment* getAppointment() const { return appoint; }
    Patient* getPatient() const { return patient; }
    Doctor* getDoctor() const { return doctor; }
    Date getDate() const { return date; }
    string getMedicine() const { return medicine; }
    string getNotes() const { return notes; }
    int getPatientID() const { return patientID; }
    int getDoctorID() const { return doctorID; }
    int getAppointmentID() const { return appointmentID; }

    void display() const;
    void input();
};