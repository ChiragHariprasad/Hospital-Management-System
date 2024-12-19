#include <stdio.h>
#include <string.h>

// Define constants for maximum sizes
#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define MAX_NAME_LENGTH 50

// Structure for storing patient information
struct Patient {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char disease[MAX_NAME_LENGTH];
    char visitHistory[100];
};

// Structure for storing doctor information
struct Doctor {
    int id;
    char name[MAX_NAME_LENGTH];
    char specialty[MAX_NAME_LENGTH];
};

// Structure for managing the waiting queue
struct Queue {
    int front, rear;
    int items[MAX_PATIENTS];
};

// Function to initialize a queue
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* q) {
    return (q->front == -1);
}

// Function to add a patient to the queue
void enqueue(struct Queue* q, int patientId) {
    if (q->rear == MAX_PATIENTS - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = patientId;
}

// Function to remove a patient from the queue
int dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int patientId = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return patientId;
}

// Function to display patient records
void displayPatientRecords(struct Patient patients[], int patientCount) {
    printf("\nPatient Records:\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s, Visit History: %s\n",
                patients[i].id, patients[i].name, patients[i].age, patients[i].disease, patients[i].visitHistory);
    }
}

// Function to display doctor assignments
void displayDoctorAssignments(struct Doctor doctors[], int doctorCount, struct Patient patients[], int patientCount) {
    printf("\nDoctor Assignments:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("Doctor: %s, Specialty: %s\n", doctors[i].name, doctors[i].specialty);
        for (int j = 0; j < patientCount; j++) {
            if (patients[j].id == (i + 1)) {  // Assigning patients based on ID for simplicity
                printf("  Patient: %s, Disease: %s\n", patients[j].name, patients[j].disease);
            }
        }
    }
}

// Function to display the current waiting queue
void displayWaitingQueue(struct Queue* q, struct Patient patients[], int patientCount) {
    printf("\nCurrent Waiting Queue:\n");
    if (isQueueEmpty(q)) {
        printf("No patients in the queue\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        int patientId = q->items[i];
        printf("Patient ID: %d, Name: %s\n", patients[patientId].id, patients[patientId].name);
    }
}

// Function to add a patient
void addPatient(struct Patient patients[], int *patientCount) {
    if (*patientCount >= MAX_PATIENTS) {
        printf("Cannot add more patients. Maximum capacity reached.\n");
        return;
    }
    struct Patient newPatient;
    printf("Enter Patient ID: ");
    scanf("%d", &newPatient.id);
    getchar(); // consume newline
    printf("Enter Patient Name: ");
    fgets(newPatient.name, MAX_NAME_LENGTH, stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = 0; // Remove newline
    printf("Enter Patient Age: ");
    scanf("%d", &newPatient.age);
    getchar(); // consume newline
    printf("Enter Disease: ");
    fgets(newPatient.disease, MAX_NAME_LENGTH, stdin);
    newPatient.disease[strcspn(newPatient.disease, "\n")] = 0; // Remove newline
    printf("Enter Visit History: ");
    fgets(newPatient.visitHistory, 100, stdin);
    newPatient.visitHistory[strcspn(newPatient.visitHistory, "\n")] = 0; // Remove newline
    
    patients[*patientCount] = newPatient;
    (*patientCount)++;
    printf("Patient added successfully!\n");
}

// Function to remove a patient
void removePatient(struct Patient patients[], int *patientCount) {
    int id;
    printf("Enter Patient ID to remove: ");
    scanf("%d", &id);
    
    int found = 0;
    for (int i = 0; i < *patientCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            for (int j = i; j < *patientCount - 1; j++) {
                patients[j] = patients[j + 1]; // Shift elements to remove the patient
            }
            (*patientCount)--;
            printf("Patient removed successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Patient not found.\n");
    }
}

// Function to add a doctor
void addDoctor(struct Doctor doctors[], int *doctorCount) {
    if (*doctorCount >= MAX_DOCTORS) {
        printf("Cannot add more doctors. Maximum capacity reached.\n");
        return;
    }
    struct Doctor newDoctor;
    printf("Enter Doctor ID: ");
    scanf("%d", &newDoctor.id);
    getchar(); // consume newline
    printf("Enter Doctor Name: ");
    fgets(newDoctor.name, MAX_NAME_LENGTH, stdin);
    newDoctor.name[strcspn(newDoctor.name, "\n")] = 0; // Remove newline
    printf("Enter Doctor Specialty: ");
    fgets(newDoctor.specialty, MAX_NAME_LENGTH, stdin);
    newDoctor.specialty[strcspn(newDoctor.specialty, "\n")] = 0; // Remove newline
    
    doctors[*doctorCount] = newDoctor;
    (*doctorCount)++;
    printf("Doctor added successfully!\n");
}

// Function to remove a doctor
void removeDoctor(struct Doctor doctors[], int *doctorCount) {
    int id;
    printf("Enter Doctor ID to remove: ");
    scanf("%d", &id);
    
    int found = 0;
    for (int i = 0; i < *doctorCount; i++) {
        if (doctors[i].id == id) {
            found = 1;
            for (int j = i; j < *doctorCount - 1; j++) {
                doctors[j] = doctors[j + 1]; // Shift elements to remove the doctor
            }
            (*doctorCount)--;
            printf("Doctor removed successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Doctor not found.\n");
    }
}

int main() {
    // Sample data
    struct Patient patients[MAX_PATIENTS];
    int patientCount = 0;
    
    struct Doctor doctors[MAX_DOCTORS];
    int doctorCount = 0;
    
    struct Queue waitingQueue;
    initQueue(&waitingQueue);
    
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Manage Patient Records\n");
        printf("2. Manage Doctor Assignments\n");
        printf("3. Manage Waiting Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nPatient Record Management:\n");
                printf("1. Add Patient\n");
                printf("2. Remove Patient\n");
                printf("3. Display Patient Records\n");
                printf("Enter your choice: ");
                int recordChoice;
                scanf("%d", &recordChoice);
                if (recordChoice == 1) {
                    addPatient(patients, &patientCount);
                } else if (recordChoice == 2) {
                    removePatient(patients, &patientCount);
                } else if (recordChoice == 3) {
                    displayPatientRecords(patients, patientCount);
                }
                break;
            case 2:
                printf("\nDoctor Assignment Management:\n");
                printf("1. Add Doctor\n");
                printf("2. Remove Doctor\n");
                printf("3. Display Doctor Assignments\n");
                printf("Enter your choice: ");
                int doctorChoice;
                scanf("%d", &doctorChoice);
                if (doctorChoice == 1) {
                    addDoctor(doctors, &doctorCount);
                } else if (doctorChoice == 2) {
                    removeDoctor(doctors, &doctorCount);
                } else if (doctorChoice == 3) {
                    displayDoctorAssignments(doctors, doctorCount, patients, patientCount);
                }
                break;
            case 3:
                printf("\nWaiting Queue Management:\n");
                printf("1. Add Patient to Queue\n");
                printf("2. Remove Patient from Queue\n");
                printf("3. Display Waiting Queue\n");
                printf("Enter your choice: ");
                int queueChoice;
                scanf("%d", &queueChoice);
                if (queueChoice == 1) {
                    int patientId;
                    printf("Enter Patient ID to add to queue: ");
                    scanf("%d", &patientId);
                    enqueue(&waitingQueue, patientId);
                } else if (queueChoice == 2) {
                    dequeue(&waitingQueue);
                } else if (queueChoice == 3) {
                    displayWaitingQueue(&waitingQueue, patients, patientCount);
                }
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

