#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define MAX_PATIENTS 100
#define MAX_DOCTORS 30
#define MAX_NAME_LEN 50 
#define MAX_VISIT_HISTORY 20

// Structure for storing doctor info
struct Doctor {
    int id;
    char name[MAX_NAME_LEN];
    char specialty[MAX_NAME_LEN];
    int isBusy;
    int patientsAttended;  
};

// Structure for storing visit records
struct VisitRecord {
    char doctorName[MAX_NAME_LEN]; // Name of the doctor
    char notes[MAX_NAME_LEN]; // Notes from the visit
};

// Structure for storing patient info
struct Patient {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char disease[MAX_NAME_LEN];
    int visitCount;  // Counter for visits
    int occupied;
    int isEmergency;  // New field for priority
    int assignedDoctorId;  // New field to track assigned doctor
    struct VisitRecord visitHistory[MAX_VISIT_HISTORY]; // Array of visit records
};

// Priority Queue structure
struct PriorityQueue {
    int front, rear;
    struct {
        int patientId;
        int priority;  // 1 for emergency, 0 for common
    } items[MAX_PATIENTS];
};
void clearScreen() {
    system(CLEAR);
}
void printHeader(const char* title) {
    clearScreen();
    printf("\n%s", "========================================");
    printf("\n%*s\n", (int)(20 + strlen(title)/2), title);
    printf("%s\n\n", "========================================");
}

// Initialize Priority Queue
void initPriorityQueue(struct PriorityQueue* q) {
    q->front = q->rear = -1;
}

void printDivider() {
    printf("\n----------------------------------------\n");
}

void pauseExecution() {
    printf("\nPress Enter to continue...");
    getchar();
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

// Function to save data to file
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

// Function to load data from file
void loadData(struct Patient patients[], int *patientCount, struct Doctor doctors[], int *doctorCount) {
    FILE *fp = fopen("hospital_data.bin", "rb");
    if (fp == NULL) {
        printf("No previous data found\n");
        return;
    }

    // First read patient and doctor counts
    if (fread(patientCount, sizeof(int), 1, fp) != 1 ||
        fread(doctorCount, sizeof(int), 1, fp) != 1) {
        printf("Error reading counts from file\n");
        fclose(fp);
        return;
    }

    // Then read patients and doctors
    size_t patientsRead = fread(patients, sizeof(struct Patient), MAX_PATIENTS, fp);
    size_t doctorsRead = fread(doctors, sizeof(struct Doctor), MAX_DOCTORS, fp);

    fclose(fp);

    if (patientsRead != MAX_PATIENTS || doctorsRead != MAX_DOCTORS) {
        printf("Warning: Incomplete data read\n");
    }

    printf("Data loaded successfully!\n");
}

// Assign patient to a specific doctor by ID
void assignToDoctor(struct Patient patients[], struct Doctor doctors[], int patientId, int doctorId, int doctorCount) {
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

    // Find the specified doctor by ID
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == doctorId) {
            if (!doctors[i].isBusy) {
                doctors[i].isBusy = 1;
                doctors[i].patientsAttended++;  // Increment the counter
                patients[patientIndex].visitCount++;  // Increment patient visit count
                patients[patientIndex].assignedDoctorId = doctorId;  // Set assigned doctor ID
                printf("Patient assigned to Doctor %s\n", doctors[i].name);
                return;
            } else {
                printf("Doctor is busy.\n");
                return;
            }
        }
    }
    printf("Doctor not found.\n");
}

// Display doctor performance
void displayDoctorPerformance(struct Doctor doctors[], int doctorCount) {
    printf("\nDoctor Performance Tracker\n");
    printf("%-5s %-20s %-20s %-15s\n", "ID", "Name", "Specialty", "Patients Attended");
    printf("%-5s %-20s %-20s %-15s\n", "--", "------------------", "------------------", "-----------------");
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].patientsAttended > 0) {  // Only display doctors who have attended patients
            printf("%-5d %-20s %-20s %-15d\n", doctors[i].id, doctors[i].name, doctors[i].specialty, doctors[i].patientsAttended);
        }
    }
}

// Hash function
int hash(int id) {
    return id % MAX_PATIENTS;
}

void addPatient(struct Patient patients[], int* patientCount) {
    printHeader("Add New Patient");
    
    if (*patientCount >= MAX_PATIENTS) {
        printf("Error: Maximum capacity reached for patients.\n");
        pauseExecution();
        return;
    }
    
    struct Patient newPatient;
    printf("Enter Patient Details\n");
    printDivider();
    printf("ID: ");
    scanf("%d", &newPatient.id);
    getchar();
    
    printf("Name: ");
    fgets(newPatient.name, MAX_NAME_LEN, stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = 0;
    
    printf("Age: ");
    scanf("%d", &newPatient.age);
    getchar();
    
    printf("Disease: ");
    fgets(newPatient.disease, MAX_NAME_LEN, stdin);
    newPatient.disease[strcspn(newPatient.disease, "\n")] = 0;
    
    // Available specialties with more comprehensive mapping
    char *specialties[] = {
        "General Medicine", 
        "Orthopedics", 
        "Cardiology", 
        "Neurology", 
        "Pulmonology", 
        "Gastroenterology", 
        "Oncology", 
        "Pediatrics", 
        "Dermatology",
        "Gynecology",
        "Urology", 
        "Psychiatry",
        "Endocrinology",
        "Nephrology",
        "Rheumatology"
    };
    int specialtyCount = sizeof(specialties) / sizeof(specialties[0]);
    
    // Improved specialty detection
    char lowercaseDisease[MAX_NAME_LEN];
    strcpy(lowercaseDisease, newPatient.disease);
    for (int i = 0; lowercaseDisease[i]; i++) {
        lowercaseDisease[i] = tolower(lowercaseDisease[i]);
    }
    
    char suggestedSpecialty[MAX_NAME_LEN];
    if (strstr(lowercaseDisease, "heart") || strstr(lowercaseDisease, "cardiac") || 
        strstr(lowercaseDisease, "chest pain") || strstr(lowercaseDisease, "blood pressure") ||
        strstr(lowercaseDisease, "cholesterol")) {
        strcpy(suggestedSpecialty, "Cardiology");
    } else if (strstr(lowercaseDisease, "bone") || strstr(lowercaseDisease, "fracture") || 
               strstr(lowercaseDisease, "arthritis") || strstr(lowercaseDisease, "shoulder") || 
               strstr(lowercaseDisease, "back") || strstr(lowercaseDisease, "knee")) {
        strcpy(suggestedSpecialty, "Orthopedics");
    } else if (strstr(lowercaseDisease, "lung") || strstr(lowercaseDisease, "respiratory") || 
               strstr(lowercaseDisease, "breathing") || strstr(lowercaseDisease, "pneumonia") ||
               strstr(lowercaseDisease, "screening")) {
        strcpy(suggestedSpecialty, "Pulmonology");
    } else if (strstr(lowercaseDisease, "brain") || strstr(lowercaseDisease, "neurological") || 
               strstr(lowercaseDisease, "headache") || strstr(lowercaseDisease, "migraine") ||
               strstr(lowercaseDisease, "memory") || strstr(lowercaseDisease, "nerve")) {
        strcpy(suggestedSpecialty, "Neurology");
    } else if (strstr(lowercaseDisease, "cancer") || strstr(lowercaseDisease, "tumor") || 
               strstr(lowercaseDisease, "oncology")) {
        strcpy(suggestedSpecialty, "Oncology");
    } else if (strstr(lowercaseDisease, "child") || strstr(lowercaseDisease, "kid") || 
               strstr(lowercaseDisease, "chicken pox") || strstr(lowercaseDisease, "vaccination")) {
        strcpy(suggestedSpecialty, "Pediatrics");
    } else if (strstr(lowercaseDisease, "skin") || strstr(lowercaseDisease, "psoriasis") || 
               strstr(lowercaseDisease, "allergy")) {
        strcpy(suggestedSpecialty, "Dermatology");
    } else if (strstr(lowercaseDisease, "stomach") || strstr(lowercaseDisease, "ulcer") || 
               strstr(lowercaseDisease, "digestive")) {
        strcpy(suggestedSpecialty, "Gastroenterology");
    } else if (strstr(lowercaseDisease, "mental") || strstr(lowercaseDisease, "psychiatric") || 
               strstr(lowercaseDisease, "health")) {
        strcpy(suggestedSpecialty, "Psychiatry");
    } else if (strstr(lowercaseDisease, "thyroid") || strstr(lowercaseDisease, "diabetes")) {
        strcpy(suggestedSpecialty, "Endocrinology");
    } else if (strstr(lowercaseDisease, "kidney") || strstr(lowercaseDisease, "renal")) {
        strcpy(suggestedSpecialty, "Nephrology");
    } else if (strstr(lowercaseDisease, "joint") || strstr(lowercaseDisease, "inflammation")) {
        strcpy(suggestedSpecialty, "Rheumatology");
    } else if (strstr(lowercaseDisease, "female") || strstr(lowercaseDisease, "pregnancy")) {
        strcpy(suggestedSpecialty, "Gynecology");
    } else if (strstr(lowercaseDisease, "prostate") || strstr(lowercaseDisease, "urinary")) {
        strcpy(suggestedSpecialty, "Urology");
    } else if (strstr(lowercaseDisease, "hypertension") || 
               strstr(lowercaseDisease, "fatigue") || 
               strstr(lowercaseDisease, "fever")) {
        strcpy(suggestedSpecialty, "General Medicine");
    } else {
        strcpy(suggestedSpecialty, "General Medicine");
    }
    
    printf("Suggested Specialty: %s\n", suggestedSpecialty);
    printf("Accept suggested specialty? (0-No, 1-Yes): ");
    int acceptSpecialty;
    scanf("%d", &acceptSpecialty);
    
    char specialty[MAX_NAME_LEN];
    if (!acceptSpecialty) {
        // Display specialty options
        printf("\nSelect Specialty:\n");
        for (int i = 0; i < specialtyCount; i++) {
            printf("%d. %s\n", i + 1, specialties[i]);
        }
        
        int specialtyChoice;
        printf("Enter specialty number (1-%d): ", specialtyCount);
        scanf("%d", &specialtyChoice);
        getchar();
        
        // Validate and assign specialty
        if (specialtyChoice > 0 && specialtyChoice <= specialtyCount) {
            strcpy(specialty, specialties[specialtyChoice - 1]);
        } else {
            strcpy(specialty, "General Medicine");
        }
    } else {
        strcpy(specialty, suggestedSpecialty);
    }
    
    printf("Selected Specialty: %s\n", specialty);
    
    printf("Emergency case? (1-Yes, 0-No): ");
    scanf("%d", &newPatient.isEmergency);
    
    newPatient.visitCount = 0;
    newPatient.assignedDoctorId = -1;
    strcpy(newPatient.visitHistory[0].doctorName, specialty);
    
    int index = hash(newPatient.id);
    while (patients[index].occupied) {
        index = (index + 1) % MAX_PATIENTS;
    }
    
    patients[index] = newPatient;
    patients[index].occupied = 1;
    (*patientCount)++;
    
    printDivider();
    printf("Patient added successfully!\n");
    pauseExecution();
}

void displayPatients(struct Patient patients[], int patientCount) {
    printHeader("Patient Records");
    
    if (patientCount == 0) {
        printf("No patients in the system.\n");
        pauseExecution();
        return;
    }
    
    printf("%-5s %-20s %-5s %-20s %-8s %-10s\n", 
           "ID", "Name", "Age", "Disease", "Visits", "Type");
    printDivider();
    
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].occupied) {
            printf("%-5d %-20s %-5d %-20s %-8d %-10s\n",
                   patients[i].id, 
                   patients[i].name, 
                   patients[i].age, 
                   patients[i].disease, 
                   patients[i].visitCount,
                   patients[i].isEmergency ? "Emergency" : "Regular");
        }
    }
    
    pauseExecution();
}

void displayDoctors(struct Doctor doctors[], int doctorCount) {
    printHeader("Doctor Status");
    
    if (doctorCount == 0) {
        printf("No doctors in the system.\n");
        pauseExecution();
        return;
    }
    
    printf("%-5s %-20s %-20s %-10s\n", 
           "ID", "Name", "Specialty", "Status");
    printDivider();
    
    for (int i = 0; i < doctorCount; i++) {
        printf("%-5d %-20s %-20s %-10s\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialty,
               doctors[i].isBusy ? "Busy" : "Available");
    }
    
    pauseExecution();
}

void displayQueue(struct PriorityQueue* q, struct Patient patients[]) {
    printHeader("Current Waiting Queue");
    
    if (isPriorityQueueEmpty(q)) {
        printf("No patients in the queue.\n");
        pauseExecution();
        return;
    }
    
    printf("%-5s %-20s %-10s\n", 
           "ID", "Name", "Priority");
    printDivider();
    
    for (int i = q->front; i <= q->rear; i++) {
        int patientId = q->items[i].patientId;
        for (int j = 0; j < MAX_PATIENTS; j++) {
            if (patients[j].occupied && patients[j].id == patientId) {
                printf("%-5d %-20s %-10s\n",
                       patients[j].id,
                       patients[j].name,
                       q->items[i].priority ? "Emergency" : "Regular");
                break;
            }
        }
    }
    
    pauseExecution();
}

void displayPatientInfo(struct Patient patients[], int patientId) {
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].occupied && patients[i].id == patientId) {
            printf("Patient ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Disease: %s\n", patients[i].disease);
            printf("Visits: %d\n", patients[i].visitCount);
            printf("Emergency: %s\n", patients[i].isEmergency ? "Yes" : "No");
            printf("Assigned Doctor ID: %d\n", patients[i].assignedDoctorId);
            return;
        }
    }
    printf("Patient not found.\n");
}

// New function to add a visit record
void addVisitRecord(struct Patient *patient, const char *doctorName, const char *notes) {
    if (patient->visitCount < MAX_VISIT_HISTORY) {
        strncpy(patient->visitHistory[patient->visitCount].doctorName, doctorName, MAX_NAME_LEN);
        strncpy(patient->visitHistory[patient->visitCount].notes, notes, MAX_NAME_LEN);
        patient->visitCount++;
    } else {
        printf("Visit history is full for patient ID %d.\n", patient->id);
    }
}

void displayVisitHistory(struct Patient patients[], struct Doctor doctors[], int patientId) {
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].occupied && patients[i].id == patientId) {
            printf("Visit History for Patient ID: %d, Name: %s\n", 
                   patients[i].id, patients[i].name);
            
            if (patients[i].visitCount == 0) {
                printf("No visit records found.\n");
                return;
            }
            
            for (int j = 0; j < patients[i].visitCount; j++) {
                // Find the doctor's full name based on the assigned doctor ID
                char doctorFullName[MAX_NAME_LEN] = "Unknown Doctor";
                for (int k = 0; k < MAX_DOCTORS; k++) {
                    if (patients[i].assignedDoctorId == doctors[k].id) {
                        strcpy(doctorFullName, doctors[k].name);
                        break;
                    }
                }
                
                printf("%d. Doctor: %s\n", j + 1, 
                       patients[i].visitHistory[j].doctorName[0] != '\0' ? 
                       patients[i].visitHistory[j].doctorName : doctorFullName);
                printf("   Reason: %s\n", patients[i].disease);
                printf("   Notes: %s\n", patients[i].visitHistory[j].notes);
                printf("\n");
            }
            return;
        }
    }
    printf("Patient not found.\n");
}

void markDoctorAvailable(struct Doctor doctors[], int doctorCount, struct Patient patients[]) {
    printf("Currently Busy Doctors:\n");
    printf("%-5s %-20s %-20s\n", "ID", "Name", "Specialty");
    printf("----------------------------------------\n");
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].isBusy) {
            printf("%-5d %-20s %-20s\n", doctors[i].id, doctors[i].name, doctors[i].specialty);
        }
    }

    int docId;
    printf("Enter Doctor ID to mark as available: ");
    scanf("%d", &docId);
    getchar();

    int found = 0;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == docId && doctors[i].isBusy) {
            doctors[i].isBusy = 0;  // Mark doctor available
            printf("Doctor marked as available.\n");
            found = 1;

            // Show the patient they attended and add notes
            for (int j = 0; j < MAX_PATIENTS; j++) {
                if (patients[j].occupied && patients[j].assignedDoctorId == docId) {
                    printf("\nAttended Patient: %s (ID: %d)\n", patients[j].name, patients[j].id);
                    printf("Reason for Visit: %s\n", patients[j].disease);

                    printf("Enter Notes for the Visit: ");
                    fgets(patients[j].visitHistory[patients[j].visitCount - 1].notes, MAX_NAME_LEN, stdin);
                    patients[j].visitHistory[patients[j].visitCount - 1].notes[strcspn(patients[j].visitHistory[patients[j].visitCount - 1].notes, "\n")] = 0;
                    break;
                }
            }
            break;
        }
    }

    if (!found) {
        printf("Doctor not found or not busy.\n");
    }
}


int main() {
    struct Patient patients[MAX_PATIENTS] = {0};
    struct Doctor doctors[MAX_DOCTORS] = {0};
    int patientCount = 0;
    int doctorCount = 0;
    
    struct PriorityQueue waitingQueue;
    initPriorityQueue(&waitingQueue);
    
    loadData(patients, &patientCount, doctors, &doctorCount);
    
    int choice;
    while (1) {
        printHeader("Hospital Management System");
        printf("1. Manage Patient Records\n");
        printf("2. Manage Doctor Assignments\n");
        printf("3. Manage Waiting Queue\n");
        printf("4. Save and Exit\n");
        printDivider();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                printHeader("Patient Record Management");
                printf("1. Add Patient\n");
                printf("2. Remove Patient\n");
                printf("3. Display Patient Records\n");
                printf("4. View Patient Visit History\n");
                printDivider();
                printf("Enter your choice: ");
                int recordChoice;
                scanf("%d", &recordChoice);
                getchar();
                
                switch (recordChoice) {
                    case 1:
                        addPatient(patients, &patientCount);
                        break;
                    case 2: {
                        printHeader("Remove Patient");
                        int id;
                        printf("Enter Patient ID to remove: ");
                        scanf("%d", &id);
                        getchar();
                        
                        int index = hash(id);
                        int found = 0;
                        while (patients[index].occupied) {
                            if (patients[index].id == id) {
                                patients[index].occupied = 0;
                                patientCount--;
                                found = 1;
                                printf("Patient removed successfully!\n");
                                break;
                            }
                            index = (index + 1) % MAX_PATIENTS;
                        }
                        if (!found) printf("Patient not found.\n");
                        pauseExecution();
                        break;
                    }
                    case 3:
                        displayPatients(patients, patientCount);
                        break;
                    case 4: {
                        printHeader("View Patient Visit History");
                        int id;
                        printf("Enter Patient ID to view visit history: ");
                        scanf("%d", &id);
                        getchar();
                        displayVisitHistory(patients, doctors, id);
                        pauseExecution();
                        break;
                    }
                }
                break;
            }
            case 2: {
                printHeader("Doctor Assignment Management");
                printf("1. Add Doctor\n");
                printf("2. Remove Doctor\n");
                printf("3. Display Doctor Status\n");
                printf("4. Mark Doctor as Available\n");
                printf("5. Doctor Performance\n");
                printDivider();
                printf("Enter your choice: ");
                int doctorChoice;
                scanf("%d", &doctorChoice);
                getchar();
                
                switch (doctorChoice) {
                    case 1:
                        addDoctor(doctors, &doctorCount);
                        break;
                    case 2:
                        removeDoctor(doctors, &doctorCount);
                        break;
                    case 3:
                        displayDoctors(doctors, doctorCount);
                        break;
                    case 4:
                        markDoctorAvailable(doctors, doctorCount, patients);
                        pauseExecution();
                        break;
                    case 5: {
                        printHeader("Doctor Performance");
                        displayDoctorPerformance(doctors, doctorCount);
                        pauseExecution();
                        break;
                    }
                    default:
                        printf("Invalid choice. Please try again.\n");
                        pauseExecution();
                }
                break;
            }
            case 3: {
                printHeader("Waiting Queue Management");
                printf("1. Add Patient to Queue\n");
                printf("2. Remove Patient from Queue\n");
                printf("3. Display Waiting Queue\n");
                printDivider();
                printf("Enter your choice: ");
                int queueChoice;
                scanf("%d", &queueChoice);
                getchar();
                
                switch (queueChoice) {
                    case 1: {
                        printHeader("Add Patient to Queue");
                        int patientId;
                        printf("Enter Patient ID: ");
                        scanf("%d", &patientId);
                        getchar();
                        
                        int priority = 0;
                        int found = 0;
                        for (int i = 0; i < MAX_PATIENTS; i++) {
                            if (patients[i].occupied && patients[i].id == patientId) {
                                priority = patients[i].isEmergency;
                                found = 1;
                                break;
                            }
                        }
                        
                        if (found) {
                            enqueuePriority(&waitingQueue, patientId, priority);
                            printf("Patient added to queue successfully!\n");
                        } else {
                            printf("Patient not found.\n");
                        }
                        pauseExecution();
                        break;
                    }
                    case 2: {
                        printHeader("Remove Patient from Queue");
                        int patientId = dequeuePriority(&waitingQueue);
                        if (patientId != -1) {
                            // Find the patient to get their assigned doctor
                            int patientIndex = -1;
                            for (int i = 0; i < MAX_PATIENTS; i++) {
                                if (patients[i].occupied && patients[i].id == patientId) {
                                    patientIndex = i;
                                    break;
                                }
                            }

                            if (patientIndex != -1) {
                                int previousDoctorId = patients[patientIndex].assignedDoctorId;
                                char previousDoctorSpecialty[MAX_NAME_LEN] = "Unknown";

                                // If no previous doctor was assigned, use the specialty from visit history
                            if (previousDoctorId == -1 && patientIndex != -1) {
                                strcpy(previousDoctorSpecialty, patients[patientIndex].visitHistory[0].doctorName);
                            }
                            
                                // Display the previous doctor information
                                printf("Previous Doctor Assigned: ID %d, Specialty: %s\n", previousDoctorId, previousDoctorSpecialty);

                                // Show available doctors with the same specialty
                                printf("Available Doctors with Specialty '%s':\n", previousDoctorSpecialty);
                                printf("%-5s %-20s %-20s\n", "ID", "Name", "Specialty");
                                printDivider();
                                
                                // Track if any available doctors exist
                                int availableDoctorsExist = 0;
                                for (int i = 0; i < doctorCount; i++) {
                                    if (!doctors[i].isBusy && strcmp(doctors[i].specialty, previousDoctorSpecialty) == 0) {
                                        printf("%-5d %-20s %-20s\n", doctors[i].id, doctors[i].name, doctors[i].specialty);
                                        availableDoctorsExist = 1;
                                    }
                                }

                                if (!availableDoctorsExist) {
                                    printf("No available doctors with matching specialty.\n");
                                    // Re-enqueue the patient if no doctors are available
                                    enqueuePriority(&waitingQueue, patientId, patients[patientIndex].isEmergency);
                                    printf("Patient returned to waiting queue.\n");
                                    pauseExecution();
                                    break;
                                }

                                // Prompt user to select a doctor
                                int selectedDoctorId;
                                int doctorAssigned = 0;
                                int attempts = 0;
                                
                                while (!doctorAssigned && attempts < 3) {
                                    printf("Enter Doctor ID to assign the patient (Attempt %d/3): ", attempts + 1);
                                    scanf("%d", &selectedDoctorId);
                                    getchar(); // Consume newline
                                    
                                    // Check if the selected doctor matches specialty and is available
                                    for (int i = 0; i < doctorCount; i++) {
                                        if (doctors[i].id == selectedDoctorId) {
                                            if (strcmp(doctors[i].specialty, previousDoctorSpecialty) == 0 && !doctors[i].isBusy) {
                                                // Attempt to assign patient to doctor
                                                assignToDoctor(patients, doctors, patientId, selectedDoctorId, doctorCount);
                                                doctorAssigned = 1;
                                                break;
                                            } else {
                                                if (strcmp(doctors[i].specialty, previousDoctorSpecialty) != 0) {
                                                    printf("Error: Doctor's specialty does not match patient's previous specialty.\n");
                                                } else if (doctors[i].isBusy) {
                                                    printf("Error: Selected doctor is currently busy.\n");
                                                }
                                            }
                                        }
                                    }
                                    
                                    if (!doctorAssigned) {
                                        attempts++;
                                        if (attempts < 3) {
                                            printf("Assignment failed. Please try again.\n");
                                        }
                                    }
                                }
                                
                                // If doctor could not be assigned after 3 attempts
                                if (!doctorAssigned) {
                                    printf("Failed to assign patient to a doctor after 3 attempts.\n");
                                    // Re-enqueue the patient
                                    enqueuePriority(&waitingQueue, patientId, patients[patientIndex].isEmergency);
                                    printf("Patient returned to waiting queue.\n");
                                }
                            } else {
                                printf("Patient not found in the system.\n");
                            }
                            pauseExecution();
                        }
                        break;
                    }
                    case 3:
                        displayQueue(&waitingQueue, patients);
                        break;
                }
                break;
            }
            case 4: {
                printHeader("Saving and Exiting");
                saveData(patients, patientCount, doctors, doctorCount);
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                pauseExecution();
        }
    }
}
