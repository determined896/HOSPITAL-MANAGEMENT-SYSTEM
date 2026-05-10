#pragma once
#include "Time.h"
#include "Person.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Bill.h"
#include "Appointment.h"
#include "Date.h"
#include "FileHandler.h"
#include "Prescription.h"
#include "FrontEnd.h"
#include "ScreenState.h"
#include <SFML/Graphics.hpp>

//ADMIN  

void addDoctor(Storage<Doctor>& doctors);

void addPatient(Storage<Patient>& patients);

void removeDoctor(Storage<Doctor>& doctors, Storage<Appointment>& appointments);

void dischargePatient(Storage<Patient>& patients, Storage<Appointment>& appointments, Storage<Bill>& bills, Storage<Prescription>& prescriptions);

void viewAllPatients(Storage<Patient>& patients, Storage<Bill>& bills);

void viewAllDoctors(Storage<Doctor>& doctors);

void viewAllAppointments(Storage<Appointment>& appointments);

void viewUnpaidBills(Storage<Bill>& bills, Storage<Patient>& patients);

void generateDailyReport(Storage<Patient>& patients, Storage<Doctor>& doctors, Storage<Appointment>& appointments, Storage<Bill>& bills);

//PATIENT

void bookAppointment(Storage<Patient>& patients, Storage<Doctor>& doctors, Storage<Appointment>& appointments, Storage<Bill>& bills, int patientID);

void cancelAppointment(Storage<Appointment>& appointments, Storage<Patient>& patients, Storage<Bill>& bills, int patientID);

void viewMyAppointments(Storage<Appointment>& appointments, int patientID);

void viewMyMedicalRecords(Storage<Prescription>& prescriptions, int patientID);

void viewMyBills(Storage<Bill>& bills, int patientID);

void payBill(Storage<Bill>& bills, Storage<Patient>& patients, int billID, int patientID);

void topUpBalance(Storage<Patient>& patients, int patientID);

//DOCTOR
void viewTodaysAppointments(Storage<Appointment>& appointments, int doctorID);

void markAppointmentComplete(Storage<Appointment>& appointments, int doctorID, int appointmentID);

void markAppointmentNoShow(Storage<Appointment>& appointments, int doctorID, int appointmentID);

void writePrescription(Storage<Prescription>& prescriptions, Storage<Appointment>& appointments,
    Storage<Patient>& patients, Storage<Doctor>& doctors, int doctorID, int appointmentID);

void viewPatientMedicalHistory(Storage<Prescription>& prescriptions, int patientID);