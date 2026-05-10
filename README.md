# HOSPITAL-MANAGEMENT-SYSTEM
A desktop-based Hospital Management System developed in C++ using SFML for graphical interface design. The system helps manage hospital operations efficiently by providing separate modules for admins, doctors, and patients.

# Hospital Management System (OOP Project)
This is a comprehensive, Object-Oriented Hospital Management System built using **C++** and **SFML** (Simple and Fast Multimedia Library). This project provides a robust interface for hospital administrators, doctors, and patients to manage healthcare operations efficiently.

## Project Overview
This application manages the daily operations of a hospital, including patient registration, doctor scheduling, appointment booking, billing, and medical prescriptions. It emphasizes on Object-Oriented Programmings concepts such as inheritance, polymorphism, templates, and encapsulation as a modular and scalable approach.

## Key Features
### Multi-Role Authentication
- **Admin Login**: Full access to system management.
- **Doctor Login**: Access to patient lists, appointments, and prescriptions including some functionalities.
- **Patient Login**: Access to personal records, appointments, and billing including some functionalities.
- **Security Logging**: All login attempts are recorded.

### Administrator Module
- **Resource Management**: Add or remove doctors and patients from the system.
- **Discharge System**: Handles the final billing and record archiving for discharged patients.
- **Global Overview**: View all active appointments and unpaid bills across the hospital.
- **Reporting**: Generate daily hospital reports summarizing patient and doctor activity.

### Doctor Module
- **Schedule Management**: View today's appointments and manage patient queues.
- **Clinical Records**: Complete appointments, mark no-shows, and view patient medical history.
- **Prescription Writing**: Digitally issue prescriptions linked to specific appointments.

### Patient Module
- **Appointment Booking**: View available doctors and book time slots.
- **Financial Management**: View personal bills, top up account balance, and pay outstanding dues.
- **Medical Records**: View personal medical history and prescriptions issued by doctors.

## Technical Architecture
### Technology Stack
- **Language**: C++
- **Graphics**: SFML (for the Graphical User Interface)
- **Data Persistence**: Flat-file storage (`.txt`) with custom linking logic.

### Core Components
- **`Person` (Base Class)**: Abstract base class defining common attributes (ID, Name, Password).
- **Derived Classes**: `Admin`, `Doctor`, and `Patient` extend `Person` with role-specific functionality.
- **`Storage<T>`**: A custom template container that manages collections of objects with CRUD capabilities.
- **`FileHandler`**: Manages data persistence, loading, saving, and linking relational data (e.g., linking an appointment to a specific patient and doctor).
- **`Validator`**: Ensures data integrity by validating user inputs (IDs, dates, names).

## How It Works

1.  **Initialization**: On startup, `Main.cpp` triggers `FileHandler` to load all data from text files into the `Storage` containers.
2.  **Linking**: Relationships between objects (like which Bill belongs to which Patient) are established using ID-based linking logic.
3.  **Main Loop**: The SFML window opens, and the system enters a state-based loop (`MAIN_MENU`, `ADMIN_LOGIN`, etc.).
4.  **Interaction**: Users interact with the GUI. Each action (booking an appointment, paying a bill) triggers business logic that updates the in-memory `Storage` and synchronizes changes back to the text files.
5.  **Persistence**: The `FileHandler` ensures that all additions, deletions, and updates are mirrored in the `.txt` files in real-time or upon closing.

## Setup and Installation

### Prerequisites
- Visual Studio (recommended)
- SFML Library (2.5.1 or later)

### Installation Steps
1.  Clone the repository.
2.  Configure your IDE to include the **SFML** headers and link against the **SFML** libraries (`window`, `graphics`, `system`).
3.  Ensure `ARIAL.TTF` and all `.txt` data files are in the same directory as the executable.
4.  Build and run the project.

## License
This project was developed as part of an Object-Oriented Programming course.
