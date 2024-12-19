#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define MAX_NAME_LEN 50

// Structure for storing doctor info
struct Doctor {
    int id;
    char name[MAX_NAME_LEN];
    char specialty[MAX_NAME_LEN];
};

// Function prototypes
void addDoctor(struct Doctor docs[], int *docCount);
void removeDoctor(struct Doctor docs[], int *docCount);

// Structure for storing patient info
struct Patient {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char disease[MAX_NAME_LEN];
    char visitHistory[100];
    int occupied; // Slot occupation check
};

// Queue structure
struct Queue {
    int front, rear;
    int items[MAX_PATIENTS];
};

// Queue initialization
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
int isQueueEmpty(struct Queue* q) {
    return (q->front == -1);
}

// Add patient to queue
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

// Remove patient from queue
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

// Hash function to map patient ID
int hash(int id) {
    return id % MAX_PATIENTS;
}

// Add new patient
void addPatient(struct Patient patients[], int* patientCount) {
    if (*patientCount >= MAX_PATIENTS) {
        printf("Max capacity reached for patients.\n");
        return;
    }
    struct Patient newPatient;
    printf("Enter Patient ID: ");
    scanf("%d", &newPatient.id);
    getchar(); // Consume newline
    printf("Enter Patient Name: ");
    fgets(newPatient.name, MAX_NAME_LEN, stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = 0; // Remove newline
    printf("Enter Patient Age: ");
    scanf("%d", &newPatient.age);
    getchar(); // Consume newline
    printf("Enter Disease: ");
    fgets(newPatient.disease, MAX_NAME_LEN, stdin);
    newPatient.disease[strcspn(newPatient.disease, "\n")] = 0; // Remove newline
    printf("Enter Visit History: ");
    fgets(newPatient.visitHistory, 100, stdin);
    newPatient.visitHistory[strcspn(newPatient.visitHistory, "\n")] = 0; // Remove newline

    int index = hash(newPatient.id);
    while (patients[index].occupied) { // Collision handling
        index = (index + 1) % MAX_PATIENTS;
    }

    patients[index] = newPatient;
    patients[index].occupied = 1; // Mark as occupied
    (*patientCount)++;
    printf("Patient added successfully!\n");
}

// Remove patient
void removePatient(struct Patient patients[], int* patientCount) {
    int id;
    printf("Enter Patient ID to remove: ");
    scanf("%d", &id);

    int index = hash(id);
    int found = 0;
    while (patients[index].occupied) {
        if (patients[index].id == id) {
            found = 1;
            patients[index].occupied = 0;
            (*patientCount)--;
            printf("Patient removed successfully!\n");
            break;
        }
        index = (index + 1) % MAX_PATIENTS;
    }
    if (!found) {
        printf("Patient not found.\n");
    }
}

// Display patient records
void displayPatients(struct Patient patients[], int patientCount) {
    printf("\nPatient Records:\n");
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].occupied) {
            printf("ID: %d, Name: %s, Age: %d, Disease: %s, Visit History: %s\n",
                    patients[i].id, patients[i].name, patients[i].age, patients[i].disease, patients[i].visitHistory);
        }
    }
}

// Display doctor assignments
void displayDoctors(struct Doctor doctors[], int doctorCount, struct Patient patients[], int patientCount) {
    printf("\nDoctor Assignments:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("Doctor: %s, Specialty: %s\n", doctors[i].name, doctors[i].specialty);
        for (int j = 0; j < patientCount; j++) {
            if (patients[j].id == (i + 1)) {
                printf("  Patient: %s, Disease: %s\n", patients[j].name, patients[j].disease);
            }
        }
    }
}

// Display waiting queue
void displayQueue(struct Queue* q, struct Patient patients[], int patientCount) {
    printf("\nCurrent Waiting Queue:\n");
    if (isQueueEmpty(q)) {
        printf("No patients in the queue\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        int patientId = q->items[i];
        int found = 0;
        // Find patient details using ID
        for (int j = 0; j < MAX_PATIENTS; j++) {
            if (patients[j].occupied && patients[j].id == patientId) {
                printf("Patient ID: %d, Name: %s\n", patients[j].id, patients[j].name);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Patient ID: %d (Details not found)\n", patientId);
        }
    }
}


// Function to add a doctor
void addDoctor(struct Doctor docs[], int *docCount) {
    if (*docCount >= MAX_DOCTORS) {
        printf("Cannot add more doctors. Maximum capacity reached.\n");
        return;
    }
    struct Doctor newDoc;
    printf("Enter Doctor ID: ");
    scanf("%d", &newDoc.id);
    getchar(); // consume newline
    printf("Enter Doctor Name: ");
    fgets(newDoc.name, MAX_NAME_LEN, stdin);
    newDoc.name[strcspn(newDoc.name, "\n")] = 0; // Remove newline
    printf("Enter Doctor Specialty: ");
    fgets(newDoc.specialty, MAX_NAME_LEN, stdin);
    newDoc.specialty[strcspn(newDoc.specialty, "\n")] = 0; // Remove newline

    docs[*docCount] = newDoc;
    (*docCount)++;
    printf("Doctor added successfully!\n");
}

// Function to remove a doctor
void removeDoctor(struct Doctor docs[], int *docCount) {
    int id;
    printf("Enter Doctor ID to remove: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *docCount; i++) {
        if (docs[i].id == id) {
            found = 1;
            for (int j = i; j < *docCount - 1; j++) {
                docs[j] = docs[j + 1];
            }
            (*docCount)--;
            printf("Doctor removed successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Doctor not found.\n");
    }
}

int main() {
    struct Patient patients[MAX_PATIENTS] = {0}; // Initialize with 0 (unoccupied)
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
                    displayPatients(patients, patientCount);
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
                    displayDoctors(doctors, doctorCount, patients, patientCount);
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
                    displayQueue(&waitingQueue, patients, patientCount);
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
