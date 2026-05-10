#include <iostream>
using namespace std;

#include "FrontEnd.h"
#include <SFML/Graphics.hpp>

void Login_Screen(sf::RenderWindow& window, ScreenState& state)
{
    sf::Font font;
    font.loadFromFile("ARIAL.ttf");

    sf::Text title;
    title.setFont(font);
    title.setString("Hospital Management System");
    title.setCharacterSize(38);
    title.setFillColor(sf::Color::Black);
    title.setPosition(120, 40);

    sf::RectangleShape aButton(sf::Vector2f(300, 60));
    aButton.setPosition(250, 150);
    aButton.setFillColor(sf::Color::Green);

    sf::RectangleShape dButton(sf::Vector2f(300, 60));
    dButton.setPosition(250, 230);
    dButton.setFillColor(sf::Color::Red);

    sf::RectangleShape pButton(sf::Vector2f(300, 60));
    pButton.setPosition(250, 310);
    pButton.setFillColor(sf::Color::Blue);

    sf::RectangleShape eButton(sf::Vector2f(300, 60));
    eButton.setPosition(250, 390);
    eButton.setFillColor(sf::Color(80, 80, 80));

    sf::Text aText("Admin Login", font, 22);
    aText.setPosition(330, 165);
    aText.setFillColor(sf::Color::White);

    sf::Text dText("Doctor Login", font, 22);
    dText.setPosition(330, 245);
    dText.setFillColor(sf::Color::White);

    sf::Text pText("Patient Login", font, 22);
    pText.setPosition(330, 325);
    pText.setFillColor(sf::Color::White);

    sf::Text eText("Exit", font, 22);
    eText.setPosition(370, 405);
    eText.setFillColor(sf::Color::White);

    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            state = EXIT;

        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);

            if (aButton.getGlobalBounds().contains(mouse.x, mouse.y))
                state = ADMIN_SECURITY;

            if (dButton.getGlobalBounds().contains(mouse.x, mouse.y))
                state = DOCTOR_SECURITY;

            if (pButton.getGlobalBounds().contains(mouse.x, mouse.y))
                state = PATIENT_SECURITY;

            if (eButton.getGlobalBounds().contains(mouse.x, mouse.y))
                state = EXIT;
        }
    }

    window.clear(sf::Color(200, 200, 200));

    window.draw(title);

    window.draw(aButton);
    window.draw(dButton);
    window.draw(pButton);
    window.draw(eButton);

    window.draw(aText);
    window.draw(dText);
    window.draw(pText);
    window.draw(eText);

    window.display();
}

void Security_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Admin>& admins, Storage<Doctor>& doctors, Storage<Patient>& patients, int& I)
{
    sf::Font font;
    if (!font.loadFromFile("ARIAL.ttf"))
    {
        cout << "Font not loaded!\n";
        return;
    }

    sf::RectangleShape box(sf::Vector2f(400, 300));
    box.setFillColor(sf::Color(240, 240, 240));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);
    box.setPosition(200, 150);

    sf::Text title("SECURITY LOGIN", font, 28);
    title.setFillColor(sf::Color::Black);
    title.setPosition(260, 170);

    sf::Text idLabel("ID:", font, 20);
    idLabel.setFillColor(sf::Color::Black);
    idLabel.setPosition(230, 230);

    sf::Text passLabel("Password:", font, 20);
    passLabel.setFillColor(sf::Color::Black);
    passLabel.setPosition(230, 280);

    sf::RectangleShape idBox(sf::Vector2f(200, 25));
    idBox.setFillColor(sf::Color::White);
    idBox.setPosition(320, 230);

    sf::RectangleShape passBox(sf::Vector2f(200, 25));
    passBox.setFillColor(sf::Color::White);
    passBox.setPosition(320, 280);

    sf::RectangleShape button(sf::Vector2f(150, 40));
    button.setFillColor(sf::Color(100, 100, 100));
    button.setPosition(325, 340);

    sf::Text buttonText("CONTINUE", font, 18);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(350, 350);

    string idInput = "";
    string passInput = "";

    sf::Text errorMsg;
    errorMsg.setFont(font);
    errorMsg.setCharacterSize(16);
    errorMsg.setFillColor(sf::Color::Red);
    errorMsg.setPosition(260, 410);
    errorMsg.setString("");
    
    bool typingID = true;
    bool working = true;

    while (working && window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                if (idBox.getGlobalBounds().contains(mouse.x, mouse.y))
                    typingID = true;

                if (passBox.getGlobalBounds().contains(mouse.x, mouse.y))
                    typingID = false;

                
                if (button.getGlobalBounds().contains(mouse.x, mouse.y))
                {
                    if (idInput.empty() || passInput.empty())
                    {
                        errorMsg.setString("Please fill all fields!");
                        continue;
                    }

                    int id;
                    try
                    {
                        id = Validator::isIDNumeric(idInput);
                    }
                    catch (HospitalException& e)
                    {
                        errorMsg.setString(e.what());
                        continue;
                    }

                    Result r1 = loginAdmin(admins, id, passInput.c_str());
                    Result r2 = loginDoctor(doctors, id, passInput.c_str());
                    Result r3 = loginPatient(patients, id, passInput.c_str());

                    ScreenState role = state;

                    if (role == ADMIN_SECURITY && r1 == ADMIN)
                    {
                        FileHandler::writeLogs("ADMIN", id, "SUCCESS");
                        state = ADMIN_LOGIN;
                        working = false;
                    }
                    else if (role == DOCTOR_SECURITY && r2 == DOCTOR)
                    {
                        FileHandler::writeLogs("DOCTOR", id, "SUCCESS");
                        state = DOCTOR_LOGIN;
                        working = false;
                        I = id;
                    }
                    else if (role == PATIENT_SECURITY && r3 == PATIENT)
                    {
                        FileHandler::writeLogs("PATIENT", id, "SUCCESS");
                        state = PATIENT_LOGIN;
                        working = false;
                        I = id;
                    }
                    else
                    {
                        FileHandler::writeLogs("UNKNOWN", id, "FAILED");
                        errorMsg.setString("Invalid ID or Password!");
                    }

                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if (typingID && !idInput.empty())
                        idInput.pop_back();
                    else if (!typingID && !passInput.empty())
                        passInput.pop_back();
                }
                else if (event.text.unicode < 128)
                {
                    char c = static_cast<char>(event.text.unicode);

                    if (typingID)
                        idInput += c;
                    else
                        passInput += c;
                }
            }
        }

        window.clear(sf::Color(200, 200, 200));

        window.draw(box);
        window.draw(title);

        window.draw(idLabel);
        window.draw(passLabel);

        window.draw(idBox);
        window.draw(passBox);

        window.draw(button);
        window.draw(buttonText);
        
        window.draw(errorMsg);

        sf::Text idText(idInput, font, 18);
        idText.setFillColor(sf::Color::Black);
        idText.setPosition(idBox.getPosition().x + 5, idBox.getPosition().y);

        string hidden(passInput.size(), '*');

        sf::Text passText(hidden, font, 18);
        passText.setFillColor(sf::Color::Black);
        passText.setPosition(passBox.getPosition().x + 5, passBox.getPosition().y);

        window.draw(idText);
        window.draw(passText);

        window.display();
    }
}

void Admin_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Admin>& admins, Storage<Doctor>& doctors, Storage<Patient>& patients,
    Storage<Appointment>& appoint, Storage<Bill>& bills, Storage<Prescription>& pres)
{
    sf::Font font;

    if (!font.loadFromFile("ARIAL.ttf"))
    {
        cout << "Font failed to load\n";
        return;
    }

    sf::Color bgColor(220, 220, 220);

    sf::Text title("Admin Panel - MediCore", font, 28);
    title.setFillColor(sf::Color::Black);
    title.setPosition(190, 12);

    string options[11] =
    {
        "1. Add Doctor",
        "2. Remove Doctor",
        "3. Add Patient",
        "4. View All Patients",
        "5. View All Doctors",
        "6. View All Appointments",
        "7. View Unpaid Bills",
        "8. Discharge Patient",
        "9. View Security Log",
        "10. Generate Daily Report",
        "11. Logout"
    };

    sf::RectangleShape buttons[11];
    sf::Text labels[11];

    for (int i = 0; i < 11; i++)
    {
        buttons[i].setSize(sf::Vector2f(420, 38));
        buttons[i].setPosition(190, 55 + (i * 47));

        if (i == 0)
            buttons[i].setFillColor(sf::Color(70, 130, 180));
        else if (i == 1)
            buttons[i].setFillColor(sf::Color(180, 70, 70));
        else if (i == 2)
            buttons[i].setFillColor(sf::Color(80, 120, 90));   // pseudo - greyed teal
        else if (i == 10)
            buttons[i].setFillColor(sf::Color(80, 80, 80));
        else
            buttons[i].setFillColor(sf::Color(100, 100, 100));

        buttons[i].setOutlineThickness(2);
        buttons[i].setOutlineColor(sf::Color::Black);

        labels[i].setFont(font);
        labels[i].setString(options[i]);
        labels[i].setCharacterSize(18);
        labels[i].setFillColor(sf::Color::White);

        labels[i].setPosition(210, 63 + (i * 47));
    }

    bool running = true;

    while (running && window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                for (int i = 0; i < 11; i++)
                {
                    if (buttons[i].getGlobalBounds().contains(mouse.x, mouse.y))
                    {
                        switch (i)
                        {
                        case 0:
                            addDoctor(doctors);
                            break;

                        case 1:
                            removeDoctor(doctors, appoint);
                            break;

                        // case 2: Add Patient
                        case 2:
                            addPatient(patients);
                            break;

                        case 3:
                            viewAllPatients(patients, bills);
                            break;

                        case 4:
                            viewAllDoctors(doctors);
                            break;

                        case 5:
                            viewAllAppointments(appoint);
                            break;

                        case 6:
                            viewUnpaidBills(bills, patients);
                            break;

                        case 7:
                            dischargePatient(patients, appoint, bills, pres);
                            break;

                        case 8:
                            FileHandler::viewSecurityLog();
                            break;

                        case 9:
                            generateDailyReport(patients, doctors, appoint, bills);
                            break;

                        case 10:
                            state = MAIN_MENU;
                            running = false;
                            break;
                        }

                    }
                }
            }
        }

        window.clear(bgColor);

        window.draw(title);

        for (int i = 0; i < 11; i++)
        {
            window.draw(buttons[i]);
            window.draw(labels[i]);
        }

        window.display();
    }
}


void Patient_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Admin>& admins, Storage<Doctor>& doctors, Storage<Patient>& patients,
    Storage<Appointment>& appoint, Storage<Bill>& bills, Storage<Prescription>& pres, int patientID)
{
    sf::Font font;

    if (!font.loadFromFile("ARIAL.ttf"))
    {
        cout << "Font failed\n";
        return;
    }

    sf::Color bg(230, 230, 230);

    Patient* currentPatient = patients.findID(patientID);

    if (!currentPatient)
    {
        cout << "Patient not found\n";
        state = MAIN_MENU;
        return;
    }

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(28);
    title.setFillColor(sf::Color::Black);
    title.setString("Welcome, Patient");
    title.setPosition(180, 20);

    sf::Text balanceText;
    balanceText.setFont(font);
    balanceText.setCharacterSize(20);
    balanceText.setFillColor(sf::Color::Black);

    balanceText.setString("Balance: PKR " + to_string(currentPatient->getBalance()));
    balanceText.setPosition(180, 60);

    string options[8] =
    {
        "1. Book Appointment",
        "2. Cancel Appointment",
        "3. View My Appointments",
        "4. View My Medical Records",
        "5. View My Bills",
        "6. Pay Bill",
        "7. Top Up Balance",
        "8. Logout"
    };

    sf::RectangleShape buttons[8];
    sf::Text labels[8];

    for (int i = 0; i < 8; i++)
    {
        buttons[i].setSize(sf::Vector2f(420, 45));
        buttons[i].setPosition(200, 120 + i * 55);

        buttons[i].setFillColor(sf::Color(100, 100, 100));
        buttons[i].setOutlineThickness(2);
        buttons[i].setOutlineColor(sf::Color::Black);

        labels[i].setFont(font);
        labels[i].setCharacterSize(20);
        labels[i].setFillColor(sf::Color::White);
        labels[i].setString(options[i]);
        labels[i].setPosition(220, 130 + i * 55);
    }

    bool running = true;

    while (running && window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                for (int i = 0; i < 8; i++)
                {
                    if (buttons[i].getGlobalBounds().contains(mouse.x, mouse.y))
                    {
                        switch (i)
                        {
                        case 0:
                            bookAppointment(patients, doctors, appoint, bills, patientID);
                            break;

                        case 1:
                            cancelAppointment(appoint, patients, bills, patientID);
                            break;

                        case 2:
                            viewMyAppointments(appoint, patientID);
                            break;

                        case 3:
                            viewMyMedicalRecords(pres, patientID);
                            break;

                        case 4:
                            viewMyBills(bills, patientID);
                            break;

                        case 5:
                            payBill(bills, patients, 0, patientID); // billID prompt will happen inside
                            break;

                        case 6:
                            topUpBalance(patients, patientID);
                            break;

                        case 7:
                            running = false;
                            state = MAIN_MENU;
                            break;
                        }
                    }
                }
            }
        }

        currentPatient = patients.findID(patientID);

        window.clear(bg);

        title.setFont(font);
        balanceText.setString("Balance: PKR " + to_string(currentPatient->getBalance()));

        window.draw(title);
        window.draw(balanceText);

        for (int i = 0; i < 8; i++)
        {
            window.draw(buttons[i]);
            window.draw(labels[i]);
        }

        window.display();
    }
}

void Doctor_Screen(sf::RenderWindow& window, ScreenState& state, Storage<Doctor>& doctors, Storage<Patient>& patients, Storage<Appointment>& appointments,
    Storage<Prescription>& prescriptions, int doctorID)
{
    sf::Font font;

    if (!font.loadFromFile("ARIAL.ttf"))
    {
        cout << "Font failed\n";
        return;
    }

    Doctor* currentDoctor = doctors.findID(doctorID);

    string doctorName = "Unknown";
    string specialization = "Unknown";

    if (currentDoctor)
    {
        doctorName = currentDoctor->getName();
        specialization = currentDoctor->getSpecialization();
    }

    sf::Color bg(230, 230, 230);

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(26);
    title.setFillColor(sf::Color::Black);

    title.setString(
        "Welcome, Dr. " + doctorName +
        " | Specialization: " + specialization
    );

    title.setPosition(40, 20);

    string options[6] =
    {
        "1. View Today's Appointments",
        "2. Mark Appointment Complete",
        "3. Mark Appointment No-Show",
        "4. Write Prescription",
        "5. View Patient Medical History",
        "6. Logout"
    };

    sf::RectangleShape buttons[6];
    sf::Text labels[6];

    for (int i = 0; i < 6; i++)
    {
        buttons[i].setSize(sf::Vector2f(450, 50));
        buttons[i].setPosition(180, 110 + i * 65);

        if (i == 5)
            buttons[i].setFillColor(sf::Color(80, 80, 80));
        else
            buttons[i].setFillColor(sf::Color(70, 120, 180));

        buttons[i].setOutlineThickness(2);
        buttons[i].setOutlineColor(sf::Color::Black);

        labels[i].setFont(font);
        labels[i].setCharacterSize(20);
        labels[i].setFillColor(sf::Color::White);

        labels[i].setString(options[i]);
        labels[i].setPosition(200, 122 + i * 65);
    }

    bool running = true;

    while (running && window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                for (int i = 0; i < 6; i++)
                {
                    if (buttons[i].getGlobalBounds().contains(mouse.x, mouse.y))
                    {
                        switch (i)
                        {
                        case 0:
                            viewTodaysAppointments(appointments, doctorID);
                            break;

                        case 1:
                            int appointmentID;
                            cout << "Enter Appointment ID: ";
                            cin >> appointmentID;

                            markAppointmentComplete(appointments, doctorID, appointmentID);
                            break;

                        case 2:
                    
                            cout << "Enter Appointment ID: ";
                            cin >> appointmentID;

                            markAppointmentNoShow(appointments, doctorID, appointmentID);
                            break;

                        case 3:
                           
                            cout << "Enter Appointment ID: ";
                            cin >> appointmentID;

                            writePrescription(prescriptions, appointments, patients, doctors, doctorID, appointmentID);
                            break;

                        case 4:
                            int patientID;
                            cout << "Enter Patient ID: ";
                            cin >> patientID;

                            viewPatientMedicalHistory(prescriptions, patientID);
                            break;

                        case 5:
                            running = false;
                            state = MAIN_MENU;
                            break;
                        }
                    }
                }
            }
        }

        window.clear(bg);

        window.draw(title);

        for (int i = 0; i < 6; i++)
        {
            window.draw(buttons[i]);
            window.draw(labels[i]);
        }

        window.display();
    }
}