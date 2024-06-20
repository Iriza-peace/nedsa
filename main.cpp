#include <iostream>
#include <limits>

bool isValidDate(const std::string &dob) {
    // Check if the date is in the correct format
    if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/') {
        return false;
    }

    int day = std::stoi(dob.substr(0, 2));
    int month = std::stoi(dob.substr(3, 2));
    int year = std::stoi(dob.substr(6, 4));

    // Check if the date components are valid
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        return false;
    }

    // Check if the date is not in the future
    time_t t = time(nullptr); // get time now
    struct tm *now = localtime(&t);
    if (year > (now->tm_year + 1900) || (year == (now->tm_year + 1900) && month > (now->tm_mon + 1)) || (
            year == (now->tm_year + 1900) && month == (now->tm_mon + 1) && day > now->tm_mday)) {
        return false;
    }

    return true;
}

class PatientsLL {
public:
    int patient_id;
    std::string name;
    std::string dob;
    std::string gender;
    PatientsLL *next;

    PatientsLL(int patient_id, std::string name, std::string dob, std::string gender) {
        this->patient_id = patient_id;
        this->name = name;
        this->dob = dob;
        this->gender = gender;
        this->next = nullptr;
    }
};

class DoctorsLL {
public:
    int doctor_id;
    std::string name;
    std::string specialization;
    DoctorsLL *next;

    DoctorsLL(int doctor_id, std::string name, std::string specialization) {
        this->doctor_id = doctor_id;
        this->name = name;
        this->specialization = specialization;
        this->next = nullptr;
    }
};

class Appointments {
public:
    int appointment_id;
    int patient_id;
    int doctor_id;
    std::string appointment_date;
    Appointments *next;

    Appointments(int appointment_id, int patient_id, int doctor_id, std::string appointment_date) {
        this->appointment_id = appointment_id;
        this->patient_id = patient_id;
        this->doctor_id = doctor_id;
        this->appointment_date = appointment_date;
        this->next = nullptr;
    }
};

class HealthcareSystem {
public:
    PatientsLL *patients;
    DoctorsLL *doctors;
    Appointments *appointments;

    HealthcareSystem() {
        patients = nullptr;
        doctors = nullptr;
        appointments = nullptr;
    }

    ~HealthcareSystem() {
        // Delete all nodes in the patients linked list
        while (patients != nullptr) {
            PatientsLL* next = patients->next;
            delete patients;
            patients = next;
        }

        // Delete all nodes in the doctors linked list
        while (doctors != nullptr) {
            DoctorsLL* next = doctors->next;
            delete doctors;
            doctors = next;
        }

        // Delete all nodes in the appointments linked list
        while (appointments != nullptr) {
            Appointments* next = appointments->next;
            delete appointments;
            appointments = next;
        }
    }

    bool doesPatientIdExist(int patient_id) const{
        PatientsLL *temp = patients;
        while (temp != nullptr) {
            if (temp->patient_id == patient_id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool doesDoctorIdExist(int doctor_id) const {
        DoctorsLL *temp = doctors;
        while (temp != nullptr) {
            if (temp->doctor_id == doctor_id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool doesAppointmentIdExist(int appointment_id) const {
        Appointments *temp = appointments;
        while (temp != nullptr) {
            if (temp->appointment_id == appointment_id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void registerPatient(int patient_id, std::string name, std::string dob, std::string gender) {
        PatientsLL *temp = patients;
        while (temp != nullptr) {
            if (temp->patient_id == patient_id) {
                throw std::invalid_argument("Patient ID already exists. Please enter a unique ID.");
            }
            temp = temp->next;
        }
        auto *newPatient = new PatientsLL(patient_id, name, dob, gender);
        newPatient->next = patients;
        patients = newPatient;
    }

    void registerDoctor(int doctor_id, std::string name, std::string specialization) {
        DoctorsLL *temp = doctors;
        while (temp != nullptr) {
            if (temp->doctor_id == doctor_id) {
                throw std::invalid_argument("Doctor ID already exists. Please enter a unique ID.");
            }
            temp = temp->next;
        }
        auto *newDoctor = new DoctorsLL(doctor_id, name, specialization);
        newDoctor->next = doctors;
        doctors = newDoctor;
    }

    void registerAppointment(int appointment_id, int patient_id, int doctor_id, std::string appointment_date) {
        Appointments *temp = appointments;
        while (temp != nullptr) {
            if (temp->appointment_id == appointment_id) {
                throw std::invalid_argument("Appointment ID already exists. Please enter a unique ID.");
            }
            temp = temp->next;
        }
        Appointments *newAppointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
        newAppointment->next = appointments;
        appointments = newAppointment;
    }

    void inquireAndRegisterPatient() {
        int patient_id;
        std::string name, dob, gender;
        std::cout << "PATIENT REGISTRATION\n----------------------\n";
        while (true) {
            try {
                std::cout << "ID: ";
                std::cin >> patient_id;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input for patient ID. Please enter a number.");
                }
                if(doesPatientIdExist(patient_id)) {
                    throw std::invalid_argument("Patient ID already exists. Please enter a unique ID.");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
                std::cout << "NAME: ";
                std::getline(std::cin, name);
                while (true) {
                    std::cout << "DoB (dd/mm/yyyy): ";
                    std::getline(std::cin, dob);
                    if (isValidDate(dob)) {
                        break;
                    } else {
                        std::cout <<
                                "Invalid date. Please enter in the format dd/mm/yyyy and the date should not be in the future.\n";
                    }
                }
                while (true) {
                    std::cout << "GENDER (male/female): ";
                    std::getline(std::cin, gender);
                    if (gender == "male" || gender == "female") {
                        break;
                    } else {
                        std::cout << "Invalid gender. Please enter either 'male' or 'female'.\n";
                    }
                }
                registerPatient(patient_id, name, dob, gender);
                break; // break the loop if no exception was thrown
            } catch (const std::invalid_argument &e) {
                std::cout << "INVALID_ARGUMENT_EXCEPTION " << e.what() << std::endl;
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
            }
        }
    }

    void inquireAndRegisterDoctor() {
        int doctor_id;
        std::string name, specialization;
        std::cout << "DOCTOR REGISTRATION\n-------------------\n";
        while (true) {
            try {
                std::cout << "ID: ";
                std::cin >> doctor_id;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input for doctor ID. Please enter a number.");
                }
                if(doesDoctorIdExist(doctor_id)) {
                    throw std::invalid_argument("Doctor ID already exists. Please enter a unique ID.");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
                std::cout << "NAME: ";
                std::getline(std::cin, name);
                std::cout << "SPECIALIZATION: ";
                std::getline(std::cin, specialization);
                registerDoctor(doctor_id, name, specialization);
                break; // break the loop if no exception was thrown
            } catch (const std::invalid_argument &e) {
                std::cout << "INVALID_ARGUMENT_EXCEPTION " << e.what() << std::endl;
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
            }
        }
    }

    void inquireAndRegisterAppointment() {
        int appointment_id, patient_id, doctor_id;
        std::string appointment_date;
        std::cout << "APPOINTMENT REGISTRATION\n----------------------\n";
        while (true) {
            try {
                std::cout << "ID: ";
                std::cin >> appointment_id;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input for appointment ID. Please enter a number.");
                }
                if (doesAppointmentIdExist(appointment_id)) {
                    throw std::invalid_argument("Appointment ID already exists. Please enter a unique ID.");
                }
                std::cout << "PATIENT ID: ";
                std::cin >> patient_id;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input for patient ID. Please enter a number.");
                }
                // check if the patient ID exists
                if (!doesPatientIdExist(patient_id)) {
                    throw std::invalid_argument("Patient ID does not exist. Please register the patient first.");
                }
                std::cout << "DOCTOR ID: ";
                std::cin >> doctor_id;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input for doctor ID. Please enter a number.");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
                // check if the doctor ID exists
                if (!doesDoctorIdExist(doctor_id)) {
                    throw std::invalid_argument("Doctor ID does not exist. Please register the doctor first.");
                }
                while (true) {
                    std::cout << "APPOINTMENT DATE (dd/mm/yyyy): ";
                    std::getline(std::cin, appointment_date);
                    if (isValidDate(appointment_date)) {
                        break;
                    } else {
                        std::cout <<
                                "Invalid date. Please enter in the format dd/mm/yyyy and the date should not be in the future.\n";
                    }
                }
                registerAppointment(appointment_id, patient_id, doctor_id, appointment_date);
                break; // break the loop if no exception was thrown
            } catch (const std::invalid_argument &e) {
                std::cout << "INVALID_ARGUMENT_EXCEPTION " << e.what() << std::endl;
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
            }
        }
    }

    void displayPatients() const {
        PatientsLL *temp = patients;
        while (temp != nullptr) {
            std::cout << "Patient ID: " << temp->patient_id << ", Name: " << temp->name << ", DOB: " << temp->dob <<
                    ", Gender: " << temp->gender << std::endl;
            temp = temp->next;
        }
    }

    void displayDoctors() const {
        DoctorsLL *temp = doctors;
        while (temp != nullptr) {
            std::cout << "Doctor ID: " << temp->doctor_id << ", Name: " << temp->name << ", Specialization: " << temp->
                    specialization << std::endl;
            temp = temp->next;
        }
    }

    void displayAppointments() const {
        Appointments *temp = appointments;
        while (temp != nullptr) {
            std::cout << "Appointment ID: " << temp->appointment_id << ", Patient ID: " << temp->patient_id <<
                    ", Doctor ID: " << temp->doctor_id << ", Appointment Date: " << temp->appointment_date << std::endl;
            temp = temp->next;
        }
    }
};

int main() {
    HealthcareSystem system;
    int choice;
    std::cout << "*****************************************************\n";
    std::cout << "**********RUHENGERI HOSPITAL MANAGEMENT SYSTEM    ****\n";
    std::cout << "*****************************************************\n";
    while (true) {
        std::cout <<
                "Menu:\n1. Register patient\n2. Register doctor\n3. Register appointment\n4. Display patients\n5. Display doctors\n6. Display appointments\n7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
            std::cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer
        try {
            switch (choice) {
                case 1: {
                    // Register patient
                    system.inquireAndRegisterPatient();
                    break;
                }
                case 2: {
                    // Register doctor
                    system.inquireAndRegisterDoctor();
                    break;
                }
                case 3: {
                    // Register appointment
                    system.inquireAndRegisterAppointment();
                    break;
                }
                case 4:
                    // Display patients
                    system.displayPatients();
                    break;
                case 5:
                    // Display doctors
                    system.displayDoctors();
                    break;
                case 6:
                    // Display appointments
                    system.displayAppointments();
                    break;
                case 7:
                    // Exit
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again.\n\n";
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}