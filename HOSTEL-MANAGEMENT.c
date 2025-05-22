#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 100
#define MAX_APPOINTMENTS 100
#define MAX_HISTORY 100

// Structure to represent a patient
typedef struct {
    int id;
    char name[100];
    int age;
    char medicalCondition[100];
    int appointments[MAX_APPOINTMENTS]; // List of appointment IDs
    int numAppointments;
    char history[MAX_HISTORY][100]; // History of the patient with the hospital
    int numHistory;
} Patient;

// Structure to represent a doctor
typedef struct {
    int id;
    char name[100];
    char department[100];
    int patients[MAX_PATIENTS]; // List of patient IDs
    int numPatients;
} Doctor;

// Global arrays to store patients and doctors
Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
int numPatients = 0;
int numDoctors = 0;
int nextPatientId = 1;
int nextDoctorId = 101;
int nextAppointmentId = 1;

// Function prototypes
void addPatient();
void addDoctor();
void assignPatientToDoctor();
void scheduleAppointment();
void displayPatients();
void displayDoctors();
void displayMenu();
void addHistory();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                addDoctor();
                break;
            case 3:
                assignPatientToDoctor();
                break;
            case 4:
                scheduleAppointment();
                break;
            case 5:
                addHistory();
                break;
            case 6:
                displayPatients();
                break;
            case 7:
                displayDoctors();
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

void displayMenu() {
    printf("\n--- Hospital Management System ---\n");
    printf("1. Add Patient\n");
    printf("2. Add Doctor\n");
    printf("3. Assign Patient to Doctor\n");
    printf("4. Schedule Appointment\n");
    printf("5. Add History for Patient\n");
    printf("6. Display Patients\n");
    printf("7. Display Doctors\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

void addPatient() {
    Patient p;
    p.id = nextPatientId++;
    printf("Enter patient name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0'; // Remove newline character
    printf("Enter patient age: ");
    scanf("%d", &p.age);
    getchar(); // Consume newline
    printf("Enter patient medical condition: ");
    fgets(p.medicalCondition, sizeof(p.medicalCondition), stdin);
    p.medicalCondition[strcspn(p.medicalCondition, "\n")] = '\0'; // Remove newline character
    p.numAppointments = 0;
    p.numHistory = 0;
    patients[numPatients++] = p;
    printf("Patient added successfully with ID %d.\n", p.id);
}

void addDoctor() {
    Doctor d;
    d.id = nextDoctorId++;
    printf("Enter doctor name: ");
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = '\0'; // Remove newline character
    printf("Enter doctor department: ");
    fgets(d.department, sizeof(d.department), stdin);
    d.department[strcspn(d.department, "\n")] = '\0'; // Remove newline character
    d.numPatients = 0;
    doctors[numDoctors++] = d;
    printf("Doctor added successfully with ID %d.\n", d.id);
}

void assignPatientToDoctor() {
    int patientId, doctorId;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);
    printf("Enter doctor ID: ");
    scanf("%d", &doctorId);

    if (patientId < 1 || patientId >= nextPatientId || doctorId < 101 || doctorId >= nextDoctorId) {
        printf("Invalid patient or doctor ID.\n");
        return;
    }

    for (int i = 0; i < numDoctors; i++) {
        if (doctors[i].id == doctorId) {
            if (doctors[i].numPatients == MAX_PATIENTS) {
                printf("Doctor's patient list is full.\n");
                return;
            }
            doctors[i].patients[doctors[i].numPatients] = patientId;
            doctors[i].numPatients++;
            printf("Patient %d assigned to doctor %d.\n", patientId, doctorId);
            return;
        }
    }

    printf("Doctor not found.\n");
}

void scheduleAppointment() {
    int patientId, doctorId;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);
    printf("Enter doctor ID: ");
    scanf("%d", &doctorId);

    if (patientId < 1 || patientId >= nextPatientId || doctorId < 101 || doctorId >= nextDoctorId) {
        printf("Invalid patient or doctor ID.\n");
        return;
    }

    // Find the patient and doctor
    Patient *patient = NULL;
    Doctor *doctor = NULL;
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].id == patientId) {
            patient = &patients[i];
            break;
        }
    }
    for (int i = 0; i < numDoctors; i++) {
        if (doctors[i].id == doctorId) {
            doctor = &doctors[i];
            break;
        }
    }

    // Check if patient and doctor were found
    if (patient == NULL || doctor == NULL) {
        printf("Patient or doctor not found.\n");
        return;
    }

    // Check if the doctor can accept more appointments
    if (doctor->numPatients == MAX_PATIENTS) {
        printf("Doctor's schedule is full.\n");
        return;
    }

    // Assign the appointment
    patient->appointments[patient->numAppointments++] = nextAppointmentId;
    doctor->patients[doctor->numPatients++] = patientId;
    printf("Appointment scheduled successfully with ID %d.\n", nextAppointmentId);
    nextAppointmentId++;
}

void addHistory() {
    int patientId;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);

    if (patientId < 1 || patientId >= nextPatientId) {
        printf("Invalid patient ID.\n");
        return;
    }

    // Find the patient
    Patient *patient = NULL;
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].id == patientId) {
            patient = &patients[i];
            break;
        }
    }

    if (patient == NULL) {
        printf("Patient not found.\n");
        return;
    }

    // Add history
    printf("Enter patient history: ");
    getchar(); // Consume newline
    fgets(patient->history[patient->numHistory], sizeof(patient->history[patient->numHistory]), stdin);
    patient->history[patient->numHistory][strcspn(patient->history[patient->numHistory], "\n")] = '\0'; // Remove newline character
    patient->numHistory++;
    printf("History added successfully for patient %d.\n", patientId);
}

void displayPatients() {
    printf("Patients:\n");
    for (int i = 0; i < numPatients; i++) {
        printf("ID: %d, Name: %s, Age: %d, Medical Condition: %s\n", patients[i].id, patients[i].name, patients[i].age, patients[i].medicalCondition);
        printf("History:\n");
        for (int j = 0; j < patients[i].numHistory; j++) {
            printf("- %s\n", patients[i].history[j]);
        }
    }
}

void displayDoctors() {
    printf("Doctors:\n");
    for (int i = 0; i < numDoctors; i++) {
        printf("ID: %d, Name: %s, Department: %s\n", doctors[i].id, doctors[i].name, doctors[i].department);
    }
}
