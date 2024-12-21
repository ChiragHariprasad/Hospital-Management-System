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
    int isBusy;  // New field to track doctor's status
};

// Structure for storing patient info
struct Patient {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char disease[MAX_NAME_LEN];
    int visitCount;  // Changed from visitHistory to counter
    int occupied;
    int isEmergency;  // New field for priority
};

// Priority Queue structure
struct PriorityQueue {
    int front, rear;
    struct {
        int patientId;
        int priority;  // 1 for emergency, 0 for common
    } items[MAX_PATIENTS];
};

// Function prototypes
void saveData(struct Patient[], int, struct Doctor[], int);
void loadData(struct Patient[], int*, struct Doctor[], int*);
void addDoctor(struct Doctor[], int*);
void removeDoctor(struct Doctor[], int*);
void initPriorityQueue(struct PriorityQueue*);
int isPriorityQueueEmpty(struct PriorityQueue*);
void enqueuePriority(struct PriorityQueue*, int, int);
int dequeuePriority(struct PriorityQueue*);
void assignToDoctor(struct Patient[], struct Doctor[], int, int);

// Initialize Priority Queue
void initPriorityQueue(struct PriorityQueue* q) {
    q->front = q->rear = -1;
}
void removeDoctor(struct Doctor doctors[], int *doctorCount) {
    if (*doctorCount <= 0) {
        printf("No doctors to remove.\n");
        return;
    }

    int id;
    printf("Enter Doctor ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *doctorCount; i++) {
        if (doctors[i].id == id) {
            // Shift remaining doctors to fill the gap
            for (int j = i; j < *doctorCount - 1; j++) {
                doctors[j] = doctors[j + 1];
            }
            (*doctorCount)--;
            printf("Doctor removed successfully!\n");
            return;
        }
    }

    printf("Doctor not found.\n");
}
void addDoctor(struct Doctor doctors[], int *doctorCount) {
    if (*doctorCount >= MAX_DOCTORS) {
        printf("Max capacity reached for doctors.\n");
        return;
    }

    struct Doctor newDoctor;
    printf("Enter Doctor ID: ");
    scanf("%d", &newDoctor.id);
    getchar(); // Consume leftover newline
    printf("Enter Doctor Name: ");
    fgets(newDoctor.name, MAX_NAME_LEN, stdin);
    newDoctor.name[strcspn(newDoctor.name, "\n")] = 0; // Remove newline
    printf("Enter Doctor Specialty: ");
    fgets(newDoctor.specialty, MAX_NAME_LEN, stdin);
    newDoctor.specialty[strcspn(newDoctor.specialty, "\n")] = 0; // Remove newline
    newDoctor.isBusy = 0; // Initialize as not busy

    doctors[*doctorCount] = newDoctor;
    (*doctorCount)++;
    printf("Doctor added successfully!\n");
}

// Check if Priority Queue is empty
int isPriorityQueueEmpty(struct PriorityQueue* q) {
    return (q->front == -1);
}

// Add patient to Priority Queue
void enqueuePriority(struct PriorityQueue* q, int patientId, int priority) {
    if (q->rear == MAX_PATIENTS - 1) {
        printf("Queue is full\n");
        return;
    }

    if (q->front == -1) {
        q->front = q->rear = 0;
        q->items[q->rear].patientId = patientId;
        q->items[q->rear].priority = priority;
        return;
    }

    // Find position for new patient based on priority
    int i;
    for (i = q->rear; i >= q->front; i--) {
        if (q->items[i].priority >= priority) {
            break;
        }
        q->items[i + 1] = q->items[i];
    }
    
    q->items[i + 1].patientId = patientId;
    q->items[i + 1].priority = priority;
    q->rear++;
}

// Remove patient from Priority Queue
int dequeuePriority(struct PriorityQueue* q) {
    if (isPriorityQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    
    int patientId = q->items[q->front].patientId;
    q->front++;
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return patientId;
}

// Save data to file
void saveData(struct Patient patients[], int patientCount, struct Doctor doctors[], int doctorCount) {
    FILE *fp = fopen("hospital_data.bin", "wb");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    fwrite(&patientCount, sizeof(int), 1, fp);
    fwrite(&doctorCount, sizeof(int), 1, fp);
    fwrite(patients, sizeof(struct Patient), MAX_PATIENTS, fp);
    fwrite(doctors, sizeof(struct Doctor), MAX_DOCTORS, fp);

    fclose(fp);
    printf("Data saved successfully!\n");
}

// Load data from file
void loadData(struct Patient patients[], int *patientCount, struct Doctor doctors[], int *doctorCount) {
    FILE *fp = fopen("hospital_data.bin", "rb");
    if (fp == NULL) {
        printf("No previous data found\n");
        return;
    }

    fread(patientCount, sizeof(int), 1, fp);
    fread(doctorCount, sizeof(int), 1, fp);
    fread(patients, sizeof(struct Patient), MAX_PATIENTS, fp);
    fread(doctors, sizeof(struct Doctor), MAX_DOCTORS, fp);

    fclose(fp);
    printf("Data loaded successfully!\n");
}

// Assign patient to available doctor
void assignToDoctor(struct Patient patients[], struct Doctor doctors[], int patientId, int doctorCount) {
    // Find the patient
    int patientIndex = -1;
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].occupied && patients[i].id == patientId) {
            patientIndex = i;
            break;
        }
    }

    if (patientIndex == -1) {
        printf("Patient not found\n");
        return;
    }

    // Find available doctor
    for (int i = 0; i < doctorCount; i++) {
        if (!doctors[i].isBusy) {
            doctors[i].isBusy = 1;
            patients[patientIndex].visitCount++;  // Increment visit count
            printf("Patient assigned to Dr. %s\n", doctors[i].name);
            return;
        }
    }
    printf("No doctors available at the moment\n");
}

// Hash function
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
    getchar();
    printf("Enter Patient Name: ");
    fgets(newPatient.name, MAX_NAME_LEN, stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = 0;
    printf("Enter Patient Age: ");
    scanf("%d", &newPatient.age);
    getchar();
    printf("Enter Disease: ");
    fgets(newPatient.disease, MAX_NAME_LEN, stdin);
    newPatient.disease[strcspn(newPatient.disease, "\n")] = 0;
    printf("Is this an emergency case? (1 for Yes, 0 for No): ");
    scanf("%d", &newPatient.isEmergency);
    
    newPatient.visitCount = 0;  // Initialize visit count
    
    int index = hash(newPatient.id);
    while (patients[index].occupied) {
        index = (index + 1) % MAX_PATIENTS;
    }
    
    patients[index] = newPatient;
    patients[index].occupied = 1;
    (*patientCount)++;
    printf("Patient added successfully!\n");
}

// Display patient records
void displayPatients(struct Patient patients[], int patientCount) {
    printf("\nPatient Records:\n");
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].occupied) {
            printf("ID: %d, Name: %s, Age: %d, Disease: %s, Visits: %d, Type: %s\n",
                   patients[i].id, patients[i].name, patients[i].age, 
                   patients[i].disease, patients[i].visitCount,
                   patients[i].isEmergency ? "Emergency" : "Regular");
        }
    }
}

// Display doctor assignments
void displayDoctors(struct Doctor doctors[], int doctorCount) {
    printf("\nDoctor Status:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("Doctor: %s, Specialty: %s, Status: %s\n",
               doctors[i].name, doctors[i].specialty,
               doctors[i].isBusy ? "Busy" : "Available");
    }
}

// Display waiting queue
void displayQueue(struct PriorityQueue* q, struct Patient patients[]) {
    printf("\nCurrent Waiting Queue:\n");
    if (isPriorityQueueEmpty(q)) {
        printf("No patients in the queue\n");
        return;
    }
    
    for (int i = q->front; i <= q->rear; i++) {
        int patientId = q->items[i].patientId;
        for (int j = 0; j < MAX_PATIENTS; j++) {
            if (patients[j].occupied && patients[j].id == patientId) {
                printf("Patient ID: %d, Name: %s, Priority: %s\n",
                       patients[j].id, patients[j].name,
                       q->items[i].priority ? "Emergency" : "Regular");
                break;
            }
        }
    }
}

// Main function
int main() {
    struct Patient patients[MAX_PATIENTS] = {0};
    int patientCount = 0;
    
    struct Doctor doctors[MAX_DOCTORS] = {0};
    int doctorCount = 0;
    
    struct PriorityQueue waitingQueue;
    initPriorityQueue(&waitingQueue);
    
    // Load saved data at startup
    loadData(patients, &patientCount, doctors, &doctorCount);
    
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Manage Patient Records\n");
        printf("2. Manage Doctor Assignments\n");
        printf("3. Manage Waiting Queue\n");
        printf("4. Save and Exit\n");
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
                    int id;
                    printf("Enter Patient ID to remove: ");
                    scanf("%d", &id);
                    // First try to find and remove from queue
                    // Then mark as unoccupied in patients array
                    int index = hash(id);
                    while (patients[index].occupied) {
                        if (patients[index].id == id) {
                            patients[index].occupied = 0;
                            patientCount--;
                            printf("Patient removed successfully!\n");
                            break;
                        }
                        index = (index + 1) % MAX_PATIENTS;
                    }
                } else if (recordChoice == 3) {
                    displayPatients(patients, patientCount);
                }
                break;
            case 2:
                printf("\nDoctor Assignment Management:\n");
                printf("1. Add Doctor\n");
                printf("2. Remove Doctor\n");
                printf("3. Display Doctor Status\n");
                printf("4. Mark Doctor as Available\n");
                printf("Enter your choice: ");
                int doctorChoice;
                scanf("%d", &doctorChoice);
                if (doctorChoice == 1) {
                    addDoctor(doctors, &doctorCount);
                } else if (doctorChoice == 2) {
                    removeDoctor(doctors, &doctorCount);
                } else if (doctorChoice == 3) {
                    displayDoctors(doctors, doctorCount);
                } else if (doctorChoice == 4) {
                    int docId;
                    printf("Enter Doctor ID: ");
                    scanf("%d", &docId);
                    for (int i = 0; i < doctorCount; i++) {
                        if (doctors[i].id == docId) {
                            doctors[i].isBusy = 0;
                            printf("Doctor marked as available\n");
                            break;
                        }
                    }
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
                    // Find patient's emergency status
                    int priority = 0;
                    for (int i = 0; i < MAX_PATIENTS; i++) {
                        if (patients[i].occupied && patients[i].id == patientId) {
                            priority = patients[i].isEmergency;
                            break;
                        }
                    }
                    enqueuePriority(&waitingQueue, patientId, priority);
                } else if (queueChoice == 2) {
                    int patientId = dequeuePriority(&waitingQueue);
                    if (patientId != -1) {
                        assignToDoctor(patients, doctors, patientId, doctorCount);
                    }
                } else if (queueChoice == 3) {
                    displayQueue(&waitingQueue, patients);
                }
                break;
            case 4:
                saveData(patients, patientCount, doctors, doctorCount);
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
