#include "SecurityAuthentication.h"

Result loginAdmin(Storage<Admin>& admins, int id, const char* pass)
{
    Admin* a = admins.findID(id);

    if (a && Validator::isValidPasswordMatch(pass, a->getPassword()))
        return ADMIN;

    return FAIL;
}

Result loginDoctor(Storage<Doctor>& doctors, int id, const char* pass)
{
    Doctor* d = doctors.findID(id);

    if (d && Validator::isValidPasswordMatch(pass, d->getPassword()))
        return DOCTOR;

    return FAIL;
}

Result loginPatient(Storage<Patient>& patients, int id, const char* pass)
{
    Patient* p = patients.findID(id);

    if (p && Validator::isValidPasswordMatch(pass, p->getPassword()))
        return PATIENT;

    return FAIL;
}