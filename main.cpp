

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

// Patient structure to hold patient details
struct Patient {
    int patientId{};
    string name;
    string dob;
    string gender;
};

// Doctor structure to hold doctor details

struct Doctor {
    int doctorId{};
    string name;
    string specialization;
};

// Appointment structure to hold appointment details

struct Appointment {

    int appointmentId{};
    int patientId{};
    int doctorId{};
    string appointmentDate;
};


// Linked list to store patients
list<Patient> patientsLL;

// Linked list to store doctors
list<Doctor> doctorsLL;

// Linked list to store appointments
list<Appointment> appointmentsLL;


// Function to check if a patient id already exists

bool isPatientIdExists(int patientId) {
    for (const Patient& patient : patientsLL) {
        if (patient.patientId == patientId) {
            return true;
        }
    }
    return false;
}

// Function to check if a doctor id already exists

bool isDoctorIdExists(int doctorId) {
    for (const Doctor& doctor : doctorsLL) {
        if (doctor.doctorId == doctorId) {
            return true;
        }
    }
    return false;
}


// Function to check if an appointment id already exists

bool isAppointmentIdExists(int appointmentId) {
    for (const Appointment& appointment : appointmentsLL) {
        if (appointment.appointmentId == appointmentId) {
            return true;
        }
    }
    return false;
}


// Function to get patient details from the user

bool getPatientDetails(Patient& patient) {
    cout << "*****PATIENT REGISTRATION*****" << endl;

    cout << "ID: ";
    cin >> patient.patientId;

    if (isPatientIdExists(patient.patientId)) {
        cout << "Error: Patient with ID " << patient.patientId << " already exists." << endl;
        return false;
    }

    cout << "NAME: ";
    cin.ignore();
    getline(cin, patient.name);

    cout << "DOB: ";
    getline(cin, patient.dob);

    cout << "GENDER: ";
    getline(cin, patient.gender);
}


// Function to get doctor details from the user

bool getDoctorDetails(Doctor& doctor) {
    cout << "*****DOCTOR REGISTRATION*****" << endl;

    cout << "ID: ";
    cin >> doctor.doctorId;

    if (isDoctorIdExists(doctor.doctorId)) {
        cout << "Error: Doctor with ID " << doctor.doctorId << " already exists." << endl;
        return false;
    }

    cout << "NAME: ";
    cin.ignore();
    getline(cin, doctor.name);

    cout << "SPECIALIZATION: ";
    getline(cin, doctor.specialization);
}


// Function to get appointment details from the user

bool getAppointmentDetails(Appointment& appointment) {
    cout << "*****APPOINTMENT REGISTRATION*****" << endl;

    cout << "ID: ";
    cin >> appointment.appointmentId;

    if (isAppointmentIdExists(appointment.appointmentId)) {
        cout << "Error: Appointment with ID " << appointment.appointmentId << " already exists." << endl;
        return false;
    }

    cout << "PATIENT ID: ";
    cin >> appointment.patientId;

    if (!isPatientIdExists(appointment.patientId)) {
        cout << "Error: Patient with ID " << appointment.patientId << " does not exist." << endl;
        return false;
    }

    cout << "DOCTOR ID: ";
    cin >> appointment.doctorId;

    if (!isDoctorIdExists(appointment.doctorId)) {
        cout << "Error: Doctor with ID " << appointment.doctorId << " does not exist." << endl;
        return false;
    }

    cout << "APPOINTMENT DATE: ";
    cin.ignore();
    getline(cin, appointment.appointmentDate);
}


// Function to display the patients


void displayPatients() {
    cout << "*****PATIENTS*****" << endl;
    for (const Patient& patient : patientsLL) {
        cout << "ID: " << patient.patientId << endl;
        cout << "NAME: " << patient.name << endl;
        cout << "DOB: " << patient.dob << endl;
        cout << "GENDER: " << patient.gender <<endl;
    }
}


// Function to display the doctors

void displayDoctors() {
    cout << "*****DOCTORS*****" << endl;
    for (const Doctor& doctor : doctorsLL) {
        cout << "ID: " << doctor.doctorId << endl;
        cout << "NAME: " << doctor.name << endl;
        cout << "SPECIALIZATION: " << doctor.specialization << endl;
    }
}


//function to display the appointments

void displayAppointments() {
    cout << "*****APPOINTMENTS*****" << endl;
    for (const Appointment& appointment : appointmentsLL) {
        cout << "ID: " << appointment.appointmentId << endl;
        cout << "PATIENT ID: " << appointment.patientId << endl;
        cout << "DOCTOR ID: " << appointment.doctorId << endl;
        cout << "APPOINTMENT DATE: " << appointment.appointmentDate << endl;
    }
}

//function to exist
void exit() {
    cout << "Exiting the program..." << endl;
    cout << "Thank you for using the hospital management system." << endl;
}

//function to return to the menu

void returnToMenu() {
    cout << "Returning to the menu..." << endl;
}


int main () {

    // Menu
    cout << "************************************\n";
    cout << "* WELCOME TO THE RUHENGERI HOSPITAL MANAGEMENT SYSTEM! *\n";
    cout << "************************************\n";
    cout << "Please enter a command:\n";

    //continue to display the menu
    char command;
    cout<<"Menu\n";
    cout<<"1. REGISTER A PATIENT\n";
    cout<<"2. REGISTER A DOCTOR\n";
    cout<<"3. REGISTER AN APPOINTMENT\n";
    cout<<"4. DISPLAY PATIENTS \n";
    cout<<"5. DISPLAY DOCTORS\n";
    cout<<"6. DISPLAY APPOINTMENTS\n";
    cout<<"7. EXIT\n";

    cin>>command;
    cin.ignore();


    switch (command) {

        case '1': {
            Patient patient;
            //if getPatientDetails become successful send this message "Successfully registered patient."
            getPatientDetails(patient);
            patientsLL.push_back(patient);


            break;
        }

        case '2': {
            Doctor doctor;
            getDoctorDetails(doctor);
            doctorsLL.push_back(doctor);
            break;
        }

        case '3': {
            Appointment appointment;
            getAppointmentDetails(appointment);
            appointmentsLL.push_back(appointment);
            break;
        }

        case '4': {

            displayPatients();
            break;

        }

        case '5': {

            displayDoctors();
            break;
        }

        case '6': {

            displayAppointments();
            break;
        }

        case '7': {
            exit();
            break;
        }

        //default case
        default: {
            cout << "Invalid command. Please enter a valid command." << endl;
        }
    }

    return 0;



}





















