#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define MAX_NAME_LENGTH 50

// Patient structure
struct Patient {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char disease[MAX_NAME_LENGTH];
    char visitHistory[100];
    int isOccupied;  // To check if a slot is occupied in the hash map
};

// Doctor structure
struct Doctor {
    int id;
    char name[MAX_NAME_LENGTH];
    char specialty[MAX_NAME_LENGTH];
};

// Queue structure
struct Queue {
    int front, rear;
    int items[MAX_PATIENTS];
};

// Global arrays for patients and doctors
struct Patient patients[MAX_PATIENTS];
struct Doctor doctors[MAX_DOCTORS];

// Function declarations
void initQueue(struct Queue *queue);
int isQueueEmpty(struct Queue *queue);
void enqueue(struct Queue *queue, int patientID);
int dequeue(struct Queue *queue);
int hashFunction(int id);
void addPatient();
void removePatient();
void saveToFile();
void loadFromFile();
void displayPatients();
void displayDoctors();
void addDoctor();  // Function prototype for adding doctors
void assignDoctorToPatient();
void displayDoctorAssignments();
void manageQueue();

int main() {
    struct Queue queue;
    initQueue(&queue);
    loadFromFile();

    int choice;
    do {
        printf("\n===== Patient Management System =====\n");
        printf("1. Add Patient\n");
        printf("2. Remove Patient\n");
        printf("3. Display Patients\n");
        printf("4. Display Doctors\n");
        printf("5. Add Doctor\n");  // New option to add doctor
        printf("6. Assign Doctor to Patient\n");
        printf("7. Manage Waiting Queue\n");
        printf("8. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                removePatient();
                break;
            case 3:
                displayPatients();
                break;
            case 4:
                displayDoctors();
                break;
            case 5:
                addDoctor();  // Call addDoctor function
                break;
            case 6:
                assignDoctorToPatient();
                break;
            case 7:
                manageQueue();
                break;
            case 8:
                saveToFile();
                printf("Data saved. Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 8);

    return 0;
}

// Queue functions
void initQueue(struct Queue *queue) {
    queue->front = queue->rear = -1;
}

int isQueueEmpty(struct Queue *queue) {
    return queue->front == -1;
}

void enqueue(struct Queue *queue, int patientID) {
    if (queue->rear == MAX_PATIENTS - 1) {
        printf("Queue is full\n");
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = patientID;
}

int dequeue(struct Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int patientID = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return patientID;
}

// Hashing functions for patient management
int hashFunction(int id) {
    return id % MAX_PATIENTS;
}

void addPatient() {
    int id;
    printf("Enter patient ID: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    
    // Check if slot is occupied (linear probing for collision resolution)
    while (patients[index].isOccupied) {
        index = (index + 1) % MAX_PATIENTS;
    }
    
    patients[index].id = id;
    printf("Enter patient name: ");
    scanf("%s", patients[index].name);
    printf("Enter patient age: ");
    scanf("%d", &patients[index].age);
    printf("Enter disease: ");
    scanf("%s", patients[index].disease);
    printf("Enter visit history: ");
    scanf("%s", patients[index].visitHistory);
    patients[index].isOccupied = 1;

    printf("Patient added successfully!\n");
}

void removePatient() {
    int id;
    printf("Enter patient ID to remove: ");
    scanf("%d", &id);

    int index = hashFunction(id);
    while (patients[index].isOccupied) {
        if (patients[index].id == id) {
            patients[index].isOccupied = 0;
            printf("Patient removed successfully!\n");
            return;
        }
        index = (index + 1) % MAX_PATIENTS;
    }
    printf("Patient not found!\n");
}

void saveToFile() {
    FILE *file = fopen("patients.txt", "w");
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].isOccupied) {
            fprintf(file, "%d,%s,%d,%s,%s\n", patients[i].id, patients[i].name, patients[i].age, patients[i].disease, patients[i].visitHistory);
        }
    }
    fclose(file);

    // Save doctors
    FILE *doctorFile = fopen("doctors.txt", "w");
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (doctors[i].id) {
            fprintf(doctorFile, "%d,%s,%s\n", doctors[i].id, doctors[i].name, doctors[i].specialty);
        }
    }
    fclose(doctorFile);
}

void loadFromFile() {
    FILE *file = fopen("patients.txt", "r");
    if (file) {
        int i = 0;  // Declare i here
        while (fscanf(file, "%d,%49[^,],%d,%49[^,],%99[^\n]", &patients[i].id, patients[i].name, &patients[i].age, patients[i].disease, patients[i].visitHistory) == 5) {
            patients[i].isOccupied = 1;
            i++;  // Increment i after each patient is loaded
        }
        fclose(file);
    }

    // Load doctors
    FILE *doctorFile = fopen("doctors.txt", "r");
    if (doctorFile) {
        int i = 0;  // Declare i for doctor loading
        while (fscanf(doctorFile, "%d,%49[^,],%49[^\n]", &doctors[i].id, doctors[i].name, doctors[i].specialty) == 3) {
            // Find the first empty slot to save the doctor
            if (doctors[i].id != 0) {
                i++;  // Increment i for each doctor loaded
            }
        }
        fclose(doctorFile);
    }
}


void displayPatients() {
    printf("\n=== Patient Records ===\n");
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].isOccupied) {
            printf("ID: %d, Name: %s, Age: %d, Disease: %s, Visit History: %s\n",
                patients[i].id, patients[i].name, patients[i].age, patients[i].disease, patients[i].visitHistory);
        }
    }
}

void displayDoctors() {
    printf("\n=== Doctors ===\n");
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (doctors[i].id) {
            printf("ID: %d, Name: %s, Specialty: %s\n", doctors[i].id, doctors[i].name, doctors[i].specialty);
        }
    }
}

void assignDoctorToPatient() {
    int doctorID, patientID;
    printf("Enter doctor ID: ");
    scanf("%d", &doctorID);
    printf("Enter patient ID: ");
    scanf("%d", &patientID);

    // Simple assignment based on ID (for simplicity)
    printf("Assigned Patient %d to Doctor %d\n", patientID, doctorID);
}

void displayDoctorAssignments() {
    printf("\n=== Doctor Assignments ===\n");
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (doctors[i].id) {
            printf("Doctor: %s, Specialty: %s\n", doctors[i].name, doctors[i].specialty);
            for (int j = 0; j < MAX_PATIENTS; j++) {
                if (patients[j].id == (i + 1)) {  // Assigning patients based on ID for simplicity
                    printf("  Patient: %s, Disease: %s\n", patients[j].name, patients[j].disease);
                }
            }
        }
    }
}

void manageQueue() {
    struct Queue queue;
    initQueue(&queue);
    int choice;
    do {
        printf("\nQueue Management:\n");
        printf("1. Add Patient to Queue\n");
        printf("2. Remove Patient from Queue\n");
        printf("3. Display Queue\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue(&queue, 1);  // Example of adding patient by ID
                break;
            case 2:
                dequeue(&queue);
                break;
            case 3:
                for (int i = queue.front; i <= queue.rear; i++) {
                    printf("Patient ID: %d\n", queue.items[i]);
                }
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}

void addDoctor() {
    int id;
    printf("Enter doctor ID: ");
    scanf("%d", &id);

    // Find an empty spot for the doctor
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (doctors[i].id == 0) {  // Check if the doctor ID is not assigned
            doctors[i].id = id;
            printf("Enter doctor name: ");
            scanf(" %[^\n]", doctors[i].name);  // To allow spaces in the name
            printf("Enter doctor's specialty: ");
            scanf(" %[^\n]", doctors[i].specialty);  // To allow spaces in specialty
            printf("Doctor added successfully!\n");
            return;
        }
    }
    printf("Doctor list is full. Cannot add more doctors.\n");
}
