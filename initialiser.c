#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define MAX_NAME_LEN 50

// Structure definitions (must match main program)
struct Doctor {
    int id;
    char name[MAX_NAME_LEN];
    char specialty[MAX_NAME_LEN];
    int isBusy;
};

struct Patient {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char disease[MAX_NAME_LEN];
    int visitCount;
    int occupied;
    int isEmergency;
};

int main() {
    struct Patient patients[MAX_PATIENTS] = {0};  // Initialize all to zero
    struct Doctor doctors[MAX_DOCTORS] = {0};     // Initialize all to zero
    int patientCount = 0;
    int doctorCount = 0;

    // Initialize doctors
    struct Doctor sampleDoctors[] = {
        {1, "Dr. John Smith", "Cardiology", 0},
        {2, "Dr. Sarah Johnson", "Pediatrics", 0},
        {3, "Dr. Michael Chen", "Orthopedics", 0},
        {4, "Dr. Emily Brown", "General Medicine", 0},
        {5, "Dr. David Wilson", "Neurology", 0},
        {6, "Dr. Lisa Anderson", "Dermatology", 0},
        {7, "Dr. James Taylor", "Psychiatry", 0}
    };

    // Initialize patients
    struct Patient samplePatients[] = {
        {101, "Alice Thompson", 45, "Hypertension", 2, 1, 0},
        {102, "Bob Williams", 28, "Fractured Arm", 1, 1, 1},
        {103, "Carol Davis", 35, "Migraine", 3, 1, 0},
        {104, "Daniel Miller", 62, "Diabetes", 4, 1, 0},
        {105, "Eva Garcia", 7, "Flu", 1, 1, 0},
        {106, "Frank Wilson", 51, "Back Pain", 2, 1, 0},
        {107, "Grace Lee", 29, "Anxiety", 5, 1, 0},
        {108, "Henry Martinez", 41, "Skin Rash", 1, 1, 0},
        {109, "Isabella Clark", 73, "Heart Disease", 6, 1, 1},
        {110, "Jack Wright", 18, "Sports Injury", 2, 1, 0},
        {111, "Karen White", 55, "Depression", 4, 1, 0},
        {112, "Leo Rodriguez", 31, "Insomnia", 3, 1, 0},
        {113, "Maria Hernandez", 9, "Tonsillitis", 2, 1, 0},
        {114, "Nathan Turner", 67, "Arthritis", 5, 1, 0},
        {115, "Olivia Parker", 22, "Severe Allergies", 1, 1, 1}
    };

    // Copy doctors
    doctorCount = sizeof(sampleDoctors) / sizeof(sampleDoctors[0]);
    for (int i = 0; i < doctorCount; i++) {
        doctors[i] = sampleDoctors[i];
    }

    // Copy patients
    patientCount = sizeof(samplePatients) / sizeof(samplePatients[0]);
    for (int i = 0; i < patientCount; i++) {
        // Simple direct placement for the data file
        patients[i] = samplePatients[i];
    }

    // Write to binary file
    FILE *fp = fopen("hospital_data.bin", "wb");
    if (fp == NULL) {
        printf("Error creating data file!\n");
        return 1;
    }

    // Write counts
    fwrite(&patientCount, sizeof(int), 1, fp);
    fwrite(&doctorCount, sizeof(int), 1, fp);

    // Write full arrays
    fwrite(patients, sizeof(struct Patient), MAX_PATIENTS, fp);
    fwrite(doctors, sizeof(struct Doctor), MAX_DOCTORS, fp);

    fclose(fp);
    printf("Data file generated successfully!\n");
    printf("Created with %d patients and %d doctors\n", patientCount, doctorCount);

    return 0;
}
