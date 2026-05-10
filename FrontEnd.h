#pragma once

#include "Storage.h"
#include "FileHandler.h"
#include "ScreenState.h"
#include "SecurityAuthentication.h"
#include <SFML/Graphics.hpp>
#include "Power.h"

void Login_Screen(sf::RenderWindow& window, ScreenState& state);

void Security_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Admin>& admins, Storage<Doctor>& doctors, Storage<Patient>& patients, int& I);

void Admin_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Admin>& admins, Storage<Doctor>& doctors, Storage<Patient>& patients,
    Storage<Appointment>& appoint, Storage<Bill>& bills, Storage<Prescription>& pres);

void Patient_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Admin>& admins, Storage<Doctor>& doctors, Storage<Patient>& patients,
    Storage<Appointment>& appoint, Storage<Bill>& bills, Storage<Prescription>& pres, int patientID);

void Doctor_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Doctor>& doctors, Storage<Patient>& patients, Storage<Appointment>& appointments,
    Storage<Prescription>& prescriptions, int doctorID);