#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define MAX_NAME_LENGTH 50
#define MAX_QUEUE_SIZE 100

// Structure for storing patient information
struct Patient {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char disease[MAX_NAME_LENGTH];
    char visitHistory[100];
    int isOccupied;  // To check if a slot is occupied in the hash map
};

// Structure for storing doctor information
struct Doctor {
    int id;
    char name[MAX_NAME_LENGTH];
    char specialty[MAX_NAME_LENGTH];
};

// Structure for the waiting queue
struct Queue {
    struct Patient patients[MAX_QUEUE_SIZE];
    int front;
    int rear;
};

// Function to initialize the queue
void initQueue(struct Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue *queue) {
    return (queue->front == -1);
}

// Function to check if the queue is full
int isQueueFull(struct Queue *queue) {
    return (queue->rear == MAX_QUEUE_SIZE - 1);
}

// Function to enqueue a patient
void enqueue(struct Queue *queue, struct Patient patient) {
    if (isQueueFull(queue)) {
        printf("Queue is full! Cannot add more patients.\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0; // Set front if it's the first element
    }
    queue->patients[++queue->rear] = patient;  // Add patient to the queue
}

// Function to dequeue a patient
struct Patient dequeue(struct Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty! No patients to assign.\n");
        struct Patient emptyPatient = {0}; // Return an empty patient structure
        return emptyPatient;
    }
    struct Patient patient = queue->patients[queue->front];
    if (queue->front >= queue->rear) { // Reset queue when last patient is dequeued
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return patient;
}

// Function to save patient data to file
void savePatients(struct Patient patients[], int patientCount) {
    FILE *file = fopen("patients.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving patient data.\n");
        return;
    }
    fwrite(&patientCount, sizeof(int), 1, file);  // Save patient count
    fwrite(patients, sizeof(struct Patient), patientCount, file);  // Save patient data
    fclose(file);
}

// Function to load patient data from file
void loadPatients(struct Patient patients[], int *patientCount) {
    FILE *file = fopen("patients.dat", "rb");
    if (file == NULL) {
        printf("No previous patient data found.\n");
        return;
    }
    fread(patientCount, sizeof(int), 1, file);  // Load patient count
    fread(patients, sizeof(struct Patient), *patientCount, file);  // Load patient data
    fclose(file);
}

// Function to save doctor data to file
void saveDoctors(struct Doctor doctors[], int doctorCount) {
    FILE *file = fopen("doctors.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving doctor data.\n");
        return;
    }
    fwrite(&doctorCount, sizeof(int), 1, file);  // Save doctor count
    fwrite(doctors, sizeof(struct Doctor), doctorCount, file);  // Save doctor data
    fclose(file);
}

// Function to load doctor data from file
void loadDoctors(struct Doctor doctors[], int *doctorCount) {
    FILE *file = fopen("doctors.dat", "rb");
    if (file == NULL) {
        printf("No previous doctor data found.\n");
        return;
    }
    fread(doctorCount, sizeof(int), 1, file);  // Load doctor count
    fread(doctors, sizeof(struct Doctor), *doctorCount, file);  // Load doctor data
    fclose(file);
}

// Function to save queue data to file
void saveQueue(struct Queue *queue) {
    FILE *file = fopen("queue.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving queue data.\n");
        return;
    }
    fwrite(&queue->front, sizeof(int), 1, file);  // Save front index
    fwrite(&queue->rear, sizeof(int), 1, file);   // Save rear index
    fwrite(queue->patients, sizeof(struct Patient), queue->rear + 1, file);  // Save queue data
    fclose(file);
}

// Function to load queue data from file
void loadQueue(struct Queue *queue) {
    FILE *file = fopen("queue.dat", "rb");
    if (file == NULL) {
        printf("No previous queue data found.\n");
        return;
    }
    fread(&queue->front, sizeof(int), 1, file);  // Load front index
    fread(&queue->rear, sizeof(int), 1, file);   // Load rear index
    fread(queue->patients, sizeof(struct Patient), queue->rear + 1, file);  // Load queue data
    fclose(file);
}

// Function to add a patient to the system
void addPatient(struct Patient patients[], int *patientCount, struct Queue *queue) {
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

    // Adding the patient to the array and enqueueing the patient
    patients[*patientCount] = newPatient;
    (*patientCount)++;
    enqueue(queue, newPatient);

    // Save updated data to files
    savePatients(patients, *patientCount);
    saveQueue(queue);

    printf("Patient added successfully!\n");
}

// Function to display patient records
void displayPatientRecords(struct Patient patients[], int patientCount) {
    printf("\nPatient Records:\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s, Visit History: %s\n",
               patients[i].id, patients[i].name, patients[i].age, patients[i].disease, patients[i].visitHistory);
    }
}

// Function to display waiting queue
void displayQueue(struct Queue *queue) {
    printf("\nWaiting Queue:\n");
    if (isQueueEmpty(queue)) {
        printf("The queue is empty.\n");
        return;
    }
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("ID: %d, Name: %s, Disease: %s\n",
               queue->patients[i].id, queue->patients[i].name, queue->patients[i].disease);
    }
}

int main() {
    struct Patient patients[MAX_PATIENTS] = {0};
    int patientCount = 0;
    
    struct Doctor doctors[MAX_DOCTORS];
    int doctorCount = 0;
    
    struct Queue queue;
    initQueue(&queue);

    // Load previously saved data
    loadPatients(patients, &patientCount);
    loadDoctors(doctors, &doctorCount);
    loadQueue(&queue);

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Manage Patient Records\n");
        printf("2. Manage Doctor Assignments\n");
        printf("3. View Waiting Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nPatient Record Management:\n");
                printf("1. Add Patient\n");
                printf("2. Display Patient Records\n");
                printf("Enter your choice: ");
                int recordChoice;
                scanf("%d", &recordChoice);
                if (recordChoice == 1) {
                    addPatient(patients, &patientCount, &queue);
                } else if (recordChoice == 2) {
                    displayPatientRecords(patients, patientCount);
                }
                break;
            case 2:
                // Doctor management part can be implemented here
                break;
            case 3:
                displayQueue(&queue);
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
