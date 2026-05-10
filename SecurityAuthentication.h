#pragma once
#include <string>
#include "Storage.h"
#include "Validator.h"
#include "Admin.h"
#include "Doctor.h"
#include "Patient.h"

enum Result
{
    FAIL,
    ADMIN,
    DOCTOR,
    PATIENT
};

Result loginAdmin(Storage<Admin>& admins, int id, const char* pass);
Result loginDoctor(Storage<Doctor>& doctors, int id, const char* pass);
Result loginPatient(Storage<Patient>& patients, int id, const char* pass);