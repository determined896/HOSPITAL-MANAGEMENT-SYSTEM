#include <iostream>
using namespace std;

#include "Power.h"

//ADMIN

void addDoctor(Storage<Doctor>& doctors)
{
    Doctor d;
    d.input();

    int newID = 1;
    if (doctors.size() > 0)
    {
        for (int i = 0; i < doctors.size(); i++)
        {
            if (doctors.getData()[i].getID() >= newID)
                newID = doctors.getData()[i].getID() + 1;
        }
    }
    d.setID(newID);

    doctors.add(d);
    FileHandler::append("doctors.txt", d);

    cout << "Doctor added successfully. ID: " << newID << "\n";
}

void addPatient(Storage<Patient>& patients)
{
    Patient p;
    p.input();

    int newID = 1;
    if (patients.size() > 0)
    {
        for (int i = 0; i < patients.size(); i++)
        {
            if (patients.getData()[i].getID() >= newID)
                newID = patients.getData()[i].getID() + 1;
        }
    }
    p.setID(newID);

    patients.add(p);
    FileHandler::append("patients.txt", p);

    cout << "Patient added successfully. ID: " << newID << "\n";
}

void removeDoctor(Storage<Doctor>& doctors, Storage<Appointment>& appointments)
{
    cout << "\n--- ALL DOCTORS ---\n";
    cout << "ID | Name | Specialization | Fee\n";
    for (int i = 0; i < doctors.size(); i++)
    {
        Doctor& d = doctors.getData()[i];
        cout << d.getID() << " | " << d.getName() << " | " << d.getSpecialization() << " | " << d.getFee() << "\n";
    }

    int id;
    cout << "\nEnter Doctor ID to remove: ";
    cin >> id;

    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];
        if (a.getDoctorID() == id && a.getStatus() == PENDING)
        {
            cout << "Cannot remove doctor with pending appointments. Cancel or reassign them first.\n";
            return;
        }
    }

    if (doctors.removeID(id))
    {
        FileHandler::removeID<Doctor>("doctors.txt", id);
        cout << "Doctor removed.\n";
    }
    else
        cout << "Doctor not found.\n";
}

void dischargePatient(Storage<Patient>& patients, Storage<Appointment>& appointments, Storage<Bill>& bills, Storage<Prescription>& prescriptions)
{
    int patientID;

    cout << "Enter Patient ID: ";
    cin >> patientID;

    Patient* p = patients.findID(patientID);
    if (!p)
    {
        cout << "Patient not found.\n";
        return;
    }

    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.getData()[i].getPatientID() == patientID &&
            bills.getData()[i].getStatus() == UNPAID)
        {
            cout << "Cannot discharge patient with unpaid bills.\n";
            return;
        }
    }

    for (int i = 0; i < appointments.size(); i++)
    {
        if (appointments.getData()[i].getPatientID() == patientID &&
            appointments.getData()[i].getStatus() == PENDING)
        {
            cout << "Cannot discharge patient with pending appointments.\n";
            return;
        }
    }

    ofstream archive("discharged.txt", ios::app);
    if (!archive.is_open())
    {
        cout << "Failed to open discharged.txt\n";
        return;
    }

    archive << *p << endl;

    for (int i = 0; i < appointments.size(); i++)
    {
        if (appointments.getData()[i].getPatientID() == patientID)
        {
            archive << appointments.getData()[i] << endl;
            int removeID = appointments.getData()[i].getID();
            appointments.removeID(removeID);
            i--;
        }
    }

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.getData()[i].getPatientID() == patientID)
        {
            archive << prescriptions.getData()[i] << endl;
            int removeID = prescriptions.getData()[i].getID();
            prescriptions.removeID(removeID);
            i--;
        }
    }

    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.getData()[i].getPatientID() == patientID)
        {
            archive << bills.getData()[i] << endl;
            int removeID = bills.getData()[i].getID();
            bills.removeID(removeID);
            i--;
        }
    }

    archive.close();

    patients.removeID(patientID);
    FileHandler::removeID<Patient>("patients.txt", patientID);
    FileHandler::removePatientRecords<Appointment>("appointments.txt", patientID);
    FileHandler::removePatientRecords<Prescription>("prescriptions.txt", patientID);
    FileHandler::removePatientRecords<Bill>("bills.txt", patientID);

    cout << "Patient discharged and archived successfully.\n";
}

void viewAllPatients(Storage<Patient>& patients, Storage<Bill>& bills)
{
    cout << "\n--- ALL PATIENTS ---\n";

    for (int i = 0; i < patients.size(); i++)
    {
        patients.getData()[i].display();

        int unpaidCount = 0;
        for (int j = 0; j < bills.size(); j++)
        {
            if (bills.getData()[j].getPatientID() == patients.getData()[i].getID() &&
                bills.getData()[j].getStatus() == UNPAID)
                unpaidCount++;
        }

        cout << "Unpaid Bills: " << unpaidCount << "\n";
    }
}

void viewAllDoctors(Storage<Doctor>& doctors)
{
    cout << "\n--- ALL DOCTORS ---\n";

    for (int i = 0; i < doctors.size(); i++)
    {
        doctors.getData()[i].display();
        cout << endl;
    }
}

void viewAllAppointments(Storage<Appointment>& appointments)
{
    cout << "\n--- ALL APPOINTMENTS ---\n";

    for (int i = 0; i < appointments.size(); i++)
    {
        appointments.getData()[i].display();
        cout << endl;
    }
}

void viewUnpaidBills(Storage<Bill>& bills, Storage<Patient>& patients)
{
    cout << "\n--- UNPAID BILLS ---\n";
    cout << "Bill ID | Patient Name | Amount (PKR) | Date\n";

    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.getData()[i];

        if (b.getStatus() != UNPAID)
            continue;

        Patient* p = patients.findID(b.getPatientID());
        const char* name = p ? p->getName() : "Unknown";

        b.display(name);
    }
}

void generateDailyReport(Storage<Patient>& patients, Storage<Doctor>& doctors, Storage<Appointment>& appointments, Storage<Bill>& bills)
{
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);

    int today_d = local.tm_mday;
    int today_m = 1 + local.tm_mon;
    int today_y = 1900 + local.tm_year;

    cout << "\n--- DAILY REPORT (" << today_d << "/" << today_m << "/" << today_y << ") ---\n";

    int totalAppts = 0;
    int pending = 0, completed = 0, noshow = 0, cancelled = 0;

    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];
        if (a.getDate().getDay() == today_d &&
            a.getDate().getMonth() == today_m &&
            a.getDate().getYear() == today_y)
        {
            totalAppts++;
            if (a.getStatus() == PENDING) pending++;
            else if (a.getStatus() == COMPLETED) completed++;
            else if (a.getStatus() == NO_SHOW) noshow++;
            else if (a.getStatus() == CANCELLED) cancelled++;
        }
    }

    cout << "Total appointments today: " << totalAppts 
         << " (Pending: " << pending 
         << " Completed: " << completed 
         << " No-show: " << noshow 
         << " Cancelled: " << cancelled << ")\n";

    float revenue = 0.0f;
    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.getData()[i];
        if (b.getDate().getDay() == today_d &&
            b.getDate().getMonth() == today_m &&
            b.getDate().getYear() == today_y &&
            b.getStatus() == PAID)
        {
            revenue += b.getAmount();
        }
    }

    cout << "Revenue collected today (paid bills): PKR " << revenue << "\n";

    cout << "Patients with outstanding unpaid bills:\n";
    cout << "Patient Name | Total Owed\n";
    for (int i = 0; i < patients.size(); i++)
    {
        Patient& p = patients.getData()[i];
        float totalOwed = 0.0f;
        for (int j = 0; j < bills.size(); j++)
        {
            Bill& b = bills.getData()[j];
            if (b.getPatientID() == p.getID() && b.getStatus() == UNPAID)
            {
                totalOwed += b.getAmount();
            }
        }
        if (totalOwed > 0)
        {
            cout << p.getName() << " | PKR " << totalOwed << "\n";
        }
    }

    cout << "\nDoctor-wise summary for today:\n";
    cout << "Doctor Name | Completed | Pending | No-show\n";
    for (int i = 0; i < doctors.size(); i++)
    {
        Doctor& d = doctors.getData()[i];
        int dComp = 0, dPend = 0, dNoShow = 0;

        for (int j = 0; j < appointments.size(); j++)
        {
            Appointment& a = appointments.getData()[j];
            if (a.getDoctorID() == d.getID() &&
                a.getDate().getDay() == today_d &&
                a.getDate().getMonth() == today_m &&
                a.getDate().getYear() == today_y)
            {
                if (a.getStatus() == COMPLETED) dComp++;
                else if (a.getStatus() == PENDING) dPend++;
                else if (a.getStatus() == NO_SHOW) dNoShow++;
            }
        }

        cout << d.getName() << " | " << dComp << " | " << dPend << " | " << dNoShow << "\n";
    }
}

//PATIENT
void bookAppointment(Storage<Patient>& patients, Storage<Doctor>& doctors, Storage<Appointment>& appointments, Storage<Bill>& bills, int patientID)
{
    string spec;
    cout << "Enter specialization to search";
    cin.ignore();
    getline(cin, spec);

    bool anyFound = false;
    for (int i = 0; i < doctors.size(); i++)
    {
        string docSpec = doctors.getData()[i].getSpecialization();
        bool match = (spec.size() == docSpec.size());
        if (match)
        {
            for (int j = 0; j < (int)spec.size(); j++)
            {
                if (tolower(spec[j]) != tolower(docSpec[j]))
                {
                    match = false;
                    break;
                }
            }
        }
        if (match)
        {
            cout << doctors.getData()[i].getID() << " | "
                 << doctors.getData()[i].getName() << " | Fee: PKR "
                 << doctors.getData()[i].getFee() << "\n";
            anyFound = true;
        }
    }
    if (!anyFound)
    {
        cout << "No doctors available for that specialization.\n";
        return;
    }

    int docID;
    cout << "Enter Doctor ID: ";
    cin >> docID;
    cin.ignore();

    Doctor* chosenDoc = doctors.findID(docID);
    if (!chosenDoc)
    {
        cout << "Doctor not found.\n";
        return;
    }

    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);
    int currYear = 1900 + local.tm_year;

    int dd = 0, mm = 0, yy = 0;
    bool dateOk = false;
    int attempts = 0;

    while (attempts < 3 && !dateOk)
    {
        cout << "Enter date (DD MM YYYY): ";
        cin >> dd >> mm >> yy;

        if (Validator::isValidDate(dd, mm, yy) && yy >= currYear)
            dateOk = true;
        else
        {
            cout << "Invalid date.\n";
            attempts++;
        }
    }
    if (!dateOk)
    {
        cout << "Too many invalid attempts. Returning to menu.\n";
        return;
    }
    Date chosenDate(dd, mm, yy);

    int slotHours[8] = { 9, 10, 11, 12, 13, 14, 15, 16 };
    int chosenHour = -1;

    while (chosenHour == -1)
    {
        bool isTaken[24] = { false };
        for (int j = 0; j < appointments.size(); j++)
        {
            Appointment& a = appointments.getData()[j];
            if (a.getDoctorID() == docID &&
                a.getDate().getDay() == dd && 
                a.getDate().getMonth() == mm && 
                a.getDate().getYear() == yy &&
                a.getStatus() != CANCELLED)
            {
                int h = a.getTime().getHours();
                if (h >= 0 && h < 24) isTaken[h] = true;
            }
        }

        cout << "\nAvailable time slots:\n";
        for (int i = 0; i < 8; i++)
        {
            int h = slotHours[i];
            cout << h << ":00 " << (isTaken[h] ? "[TAKEN]" : "[AVAILABLE]") << endl;
        }

        int hr;
        cout << "\nEnter hour (9-16): ";
        cin >> hr;

        if (hr < 9 || hr > 16)
        {
            cout << "Invalid slot. Choose from 9-16.\n";
            continue;
        }

        try
        {
            if (isTaken[hr])
                throw SlotUnavailableException("That slot is already taken. Choose another.");
            
            chosenHour = hr;
        }
        catch (SlotUnavailableException& e)
        {
            cout << e.what() << endl;
        }
    }

    Patient* pat = patients.findID(patientID);
    try
    {
        if (pat->getBalance() < chosenDoc->getFee())
            throw InsufficientFundsException("Insufficient balance to book this appointment.");
    }
    catch (InsufficientFundsException& e)
    {
        cout << e.what() << "\n";
        return;
    }

    *pat -= (int)chosenDoc->getFee();

    int newApptID = 1;
    for (int i = 0; i < appointments.size(); i++)
        if (appointments.getData()[i].getID() >= newApptID)
            newApptID = appointments.getData()[i].getID() + 1;

    Time chosenTime(chosenHour, 0, 0);
    Appointment newAppt(newApptID, pat, chosenDoc, chosenTime, chosenDate, PENDING, patientID, docID);
    appointments.add(newAppt);
    FileHandler::append("appointments.txt", newAppt);

    int newBillID = 1;
    for (int i = 0; i < bills.size(); i++)
        if (bills.getData()[i].getID() >= newBillID)
            newBillID = bills.getData()[i].getID() + 1;

    Bill newBill(newBillID, pat, &appointments.getData()[appointments.size()-1],
                 chosenDoc->getFee(), UNPAID, chosenDate, patientID, newApptID);
    bills.add(newBill);
    FileHandler::append("bills.txt", newBill);
    FileHandler::update("patients.txt", *pat);

    cout << "Appointment booked successfully. Appointment ID: " << newApptID << "\n";
}

void cancelAppointment(Storage<Appointment>& appointments, Storage<Patient>& patients, Storage<Bill>& bills, int patientID)
{
    cout << "\n--- PENDING APPOINTMENTS ---\n";
    bool foundPending = false;
    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];
        if (a.getPatientID() == patientID && a.getStatus() == PENDING)
        {
            cout << "App ID: " << a.getID() << " | Doctor: " << (a.getDoctor() ? a.getDoctor()->getName() : "Unknown") << " | Date: ";
            a.getDate().display();
            cout << " | Slot: " << a.getTime().getHours() << ":00\n";
            foundPending = true;
        }
    }

    if (!foundPending)
    {
        cout << "You have no pending appointments.\n";
        return;
    }

    int appID;
    cout << "\nEnter Appointment ID to cancel: ";
    cin >> appID;

    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];
        if (a.getID() == appID && a.getPatientID() == patientID && a.getStatus() == PENDING)
        {
            a.setStatus(CANCELLED);
            FileHandler::update("appointments.txt", a);

            Patient* pat = patients.findID(patientID);
            float fee = 0;
            if (a.getDoctor()) 
                fee = a.getDoctor()->getFee();
            
            if (pat)
            {
                *pat += (int)fee;
                FileHandler::update("patients.txt", *pat);
            }

            for (int j = 0; j < bills.size(); j++)
            {
                if (bills.getData()[j].getAppointmentID() == appID)
                {
                    bills.getData()[j].setStatus(CANCELLED_BILL);
                    FileHandler::update("bills.txt", bills.getData()[j]);
                }
            }
            
            cout << "Appointment cancelled. PKR " << fee << " refunded to your balance.\n";
            return;
        }
    }

    cout << "Invalid appointment ID.\n";
}

void viewMyAppointments(Storage<Appointment>& appointments, int patientID)
{
    int count = 0;
    for (int i = 0; i < appointments.size(); i++)
        if (appointments.getData()[i].getPatientID() == patientID) count++;

    if (count == 0)
    {
        cout << "No appointments found.\n";
        return;
    }

    cout << "\nID | Doctor Name | Specialization | Date | Time Slot | Status\n";
    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];
        if (a.getPatientID() == patientID)
        {
            cout << a.getID() << " | "
                 << (a.getDoctor() ? a.getDoctor()->getName() : "Unknown") << " | "
                 << (a.getDoctor() ? a.getDoctor()->getSpecialization() : "Unknown") << " | ";
            a.getDate().display();
            cout << " | " << a.getTime().getHours() << ":00 | ";

            Status s = a.getStatus();
            if (s == PENDING) cout << "PENDING";
            else if (s == COMPLETED) cout << "COMPLETED";
            else if (s == CANCELLED) cout << "CANCELLED";
            else if (s == NO_SHOW) cout << "NO_SHOW";
            cout << "\n";
        }
    }
}

void viewMyMedicalRecords(Storage<Prescription>& prescriptions, int patientID)
{
    int count = 0;
    for (int i = 0; i < prescriptions.size(); i++)
        if (prescriptions.getData()[i].getPatientID() == patientID) count++;

    if (count == 0)
    {
        cout << "No medical records found.\n";
        return;
    }

    cout << "\n--- MEDICAL RECORDS ---\n";
    cout << "Date | Doctor Name | Medicines | Notes\n";
    for (int i = 0; i < prescriptions.size(); i++)
    {
        Prescription& p = prescriptions.getData()[i];
        if (p.getPatientID() == patientID)
        {
            p.display();
        }
    }
}

void viewMyBills(Storage<Bill>& bills, int patientID)
{
    cout << "\n--- YOUR BILLS ---\n";
    cout << "Bill ID | App ID | Amount (PKR) | Status | Date\n";
    
    float totalUnpaid = 0;
    bool found = false;

    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.getData()[i];
        if (b.getPatientID() == patientID)
        {
            cout << b.getID() << " | " << b.getAppointmentID() << " | " << b.getAmount() << " | ";
            if (b.getStatus() == PAID) cout << "PAID";
            else if (b.getStatus() == CANCELLED_BILL) cout << "CANCELLED";
            else
            {
                cout << "UNPAID";
                totalUnpaid += b.getAmount();
            }
            cout << " | ";
            b.getDate().display();
            cout << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No bills found.\n";
    }
    else
    {
        cout << "Total outstanding unpaid amount: PKR " << totalUnpaid << "\n";
    }
}

void payBill(Storage<Bill>& bills, Storage<Patient>& patients, int _unused, int patientID)
{
    cout << "\n--- UNPAID BILLS ---\n";
    bool foundUnpaid = false;
    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.getData()[i];
        if (b.getPatientID() == patientID && b.getStatus() == UNPAID)
        {
            cout << "Bill ID: " << b.getID() << " | Amount: " << b.getAmount() << " | Date: ";
            b.getDate().display();
            cout << "\n";
            foundUnpaid = true;
        }
    }

    if (!foundUnpaid)
    {
        cout << "No unpaid bills.\n";
        return;
    }

    int billID;
    cout << "Enter Bill ID to pay: ";
    cin >> billID;

    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.getData()[i];
        if (b.getID() == billID && b.getPatientID() == patientID && b.getStatus() == UNPAID)
        {
            Patient* pat = patients.findID(patientID);
            if (pat)
            {
                try
                {
                    if (pat->getBalance() < b.getAmount())
                        throw InsufficientFundsException("Insufficient funds to pay this bill.");
                    
                    *pat -= (int)b.getAmount();
                    b.setStatus(PAID);
                    
                    FileHandler::update("bills.txt", b);
                    FileHandler::update("patients.txt", *pat);
                    
                    cout << "Bill paid successfully. Remaining balance: PKR " << pat->getBalance() << "\n";
                }
                catch (InsufficientFundsException& e)
                {
                    cout << e.what() << "\n";
                }
            }
            return;
        }
    }

    cout << "Invalid Bill ID.\n";
}

void topUpBalance(Storage<Patient>& patients, int patientID)
{
    int attempts = 0;
    while (attempts < 3)
    {
        try
        {
            float amount;
            cout << "Enter amount to add (PKR): ";
            cin >> amount;

            if (amount <= 0)
                throw InvalidInputException("Amount must be greater than 0.");

            Patient* pat = patients.findID(patientID);
            if (pat)
            {
                *pat += (int)amount;
                FileHandler::update("patients.txt", *pat);
                cout << "Balance updated. New balance: PKR " << pat->getBalance() << "\n";
                return;
            }
        }
        catch (InvalidInputException& e)
        {
            cout << e.what() << "\n";
            attempts++;
        }
    }
    cout << "Too many failed attempts. Returning to menu.\n";
}

//DOCTOR
void viewTodaysAppointments(Storage<Appointment>& appointments, int doctorID)
{
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);

    int today_d = local.tm_mday;
    int today_m = 1 + local.tm_mon;
    int today_y = 1900 + local.tm_year;

    cout << "\n--- TODAY'S APPOINTMENTS ---\n";

    bool found = false;

    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];

        if (a.getDoctorID() == doctorID &&
            a.getDate().getDay() == today_d &&
            a.getDate().getMonth() == today_m &&
            a.getDate().getYear() == today_y &&
            a.getStatus() == PENDING)
        {
            a.display();
            found = true;
        }
    }

    if (!found)
        cout << "No appointments for today.\n";
}

void markAppointmentComplete(Storage<Appointment>& appointments, int doctorID, int appointmentID)
{
    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];

        if (a.getID() == appointmentID && a.getDoctorID() == doctorID)
        {
            if (a.getStatus() != PENDING)
            {
                cout << "Appointment is not pending.\n";
                return;
            }

            a.setStatus(COMPLETED);
            FileHandler::update("appointments.txt", a);

            cout << "Appointment marked as complete.\n";
            return;
        }
    }

    cout << "Appointment not found.\n";
}

void markAppointmentNoShow(Storage<Appointment>& appointments, int doctorID, int appointmentID)
{
    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.getData()[i];

        if (a.getID() == appointmentID && a.getDoctorID() == doctorID)
        {
            if (a.getStatus() != PENDING)
            {
                cout << "Appointment is not pending.\n";
                return;
            }

            a.setStatus(NO_SHOW);
            FileHandler::update("appointments.txt", a);

            cout << "Appointment marked as no-show.\n";
            return;
        }
    }

    cout << "Appointment not found.\n";
}

void writePrescription(Storage<Prescription>& prescriptions, Storage<Appointment>& appointments,
    Storage<Patient>& patients, Storage<Doctor>& doctors, int doctorID, int appointmentID)
{
    Appointment* a = appointments.findID(appointmentID);

    if (!a)
    {
        cout << "Appointment not found.\n";
        return;
    }

    if (a->getDoctorID() != doctorID)
    {
        cout << "This is not your appointment.\n";
        return;
    }

    if (a->getStatus() != COMPLETED)
    {
        cout << "Appointment must be completed before writing prescription.\n";
        return;
    }

    Prescription p;
    p.input();

    p.setDoctorID(doctorID);
    p.setAppointmentID(appointmentID);
    p.setPatientID(a->getPatientID());

    prescriptions.add(p);
    FileHandler::append("prescriptions.txt", p);

    FileHandler::linkPrescriptions(prescriptions, appointments, patients, doctors);

    cout << "Prescription written successfully.\n";
}

void viewPatientMedicalHistory(Storage<Prescription>& prescriptions, int patientID)
{
    cout << "\n--- PATIENT MEDICAL HISTORY ---\n";

    bool found = false;

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.getData()[i].getPatientID() == patientID)
        {
            prescriptions.getData()[i].display();
            found = true;
        }
    }

    if (!found)
        cout << "No medical history found for this patient.\n";
}

