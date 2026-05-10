#include <iostream>
#include <fstream>
#include <cstring>
#include <SFML/Graphics.hpp>
using namespace std;

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

int main()
{
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin> admins;

    Storage<Appointment> appointments;
    Storage<Bill> bills;
    Storage<Prescription> prescriptions;

    FileHandler::load("patients.txt", patients);
    FileHandler::load("doctors.txt", doctors);
    FileHandler::load("admin.txt", admins);

    FileHandler::load("appointments.txt", appointments);
    FileHandler::load("bills.txt", bills);
    FileHandler::load("prescriptions.txt", prescriptions);

    FileHandler::linkAppointments(appointments, patients, doctors);
    FileHandler::linkBills(bills, patients, appointments);
    FileHandler::linkPrescriptions(prescriptions, appointments, patients, doctors);


    sf::RenderWindow window(sf::VideoMode(800, 600), "Hospital System");
    ScreenState state = MAIN_MENU;

    int logged = 0;

    while (window.isOpen())
    {
        switch (state)
        {
        case MAIN_MENU:
            Login_Screen(window, state);
            break;

        case ADMIN_SECURITY:
        case DOCTOR_SECURITY:
        case PATIENT_SECURITY:
            Security_Screen(window, state, admins, doctors, patients, logged);
            break;

        case ADMIN_LOGIN:
            Admin_Screen(window, state, admins, doctors, patients, appointments, bills, prescriptions);
            break;

        case DOCTOR_LOGIN:
            Doctor_Screen(window, state, doctors, patients, appointments, prescriptions, logged);
            break;

        case PATIENT_LOGIN:
            Patient_Screen(window, state, admins, doctors, patients, appointments, bills, prescriptions, logged);
            break;

        case EXIT:
            window.close();
            break;
        }
    }

}