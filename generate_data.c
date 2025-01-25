#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 30
#define MAX_NAME_LEN 50
#define MAX_VISIT_HISTORY 20

struct Doctor {
    int id;
    char name[MAX_NAME_LEN];
    char specialty[MAX_NAME_LEN];
    int isBusy;
    int patientsAttended;
};

struct VisitRecord {
    char doctorName[MAX_NAME_LEN]; 
    char notes[MAX_NAME_LEN]; 
};

struct Patient {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char disease[MAX_NAME_LEN];
    int visitCount;
    int occupied;
    int isEmergency;
    int assignedDoctorId;
    struct VisitRecord visitHistory[MAX_VISIT_HISTORY];
};

// Function to find a doctor in a specific specialty with the least patients
int findDoctorInSpecialty(struct Doctor doctors[], int doctorCount, const char* specialty) {
    int minPatientsAttended = INT_MAX;
    int selectedDoctorId = -1;
    int candidateDoctors[MAX_DOCTORS];
    int candidateCount = 0;

    // First, find all doctors in the specialty
    for (int i = 0; i < doctorCount; i++) {
        if (strcmp(doctors[i].specialty, specialty) == 0) {
            candidateDoctors[candidateCount++] = i;
        }
    }

    // If no doctors found in specialty, fallback to General Medicine
    if (candidateCount == 0) {
        for (int i = 0; i < doctorCount; i++) {
            if (strcmp(doctors[i].specialty, "General Medicine") == 0) {
                candidateDoctors[candidateCount++] = i;
            }
        }
    }

    // Find doctor with least patients among candidates
    for (int i = 0; i < candidateCount; i++) {
        int doctorIndex = candidateDoctors[i];
        if (doctors[doctorIndex].patientsAttended < minPatientsAttended) {
            minPatientsAttended = doctors[doctorIndex].patientsAttended;
            selectedDoctorId = doctors[doctorIndex].id;
        }
    }

    return selectedDoctorId;
}

int main() {
    struct Patient patients[MAX_PATIENTS] = {0};
    struct Doctor doctors[MAX_DOCTORS] = {0};
    int patientCount = 0;
    int doctorCount = 0;

    // Comprehensive doctor specialties (same as previous version)
    struct Doctor sampleDoctors[] = {
        // General Medicine
        {1, "Dr. Rajesh Kumar", "General Medicine", 0, 0},
        {2, "Dr. Sunita Desai", "General Medicine", 0, 0},
        {3, "Dr. Arvind Shah", "General Medicine", 0, 0},
        {4, "Dr. Neelam Gupta", "General Medicine", 0, 0},

        // Cardiology
        {5, "Dr. Suresh Iyer", "Cardiology", 0, 0},
        {6, "Dr. Rekha Nair", "Cardiology", 0, 0},

        // Orthopedics
        {7, "Dr. Anil Patel", "Orthopedics", 0, 0},
        {22, "Dr. Meera Deshmukh", "Orthopedics", 0, 0},

        // Pediatrics
        {8, "Dr. Priya Sharma", "Pediatrics", 0, 0},
        {9, "Dr. Ankit Verma", "Pediatrics", 0, 0},

        // Gynecology & Urology
        {10, "Dr. Vikram Rao", "Gynecology", 0, 0},
        {11, "Dr. Kavita Nair", "Urology", 0, 0},

        // Neurology
        {12, "Dr. Sushma Joshi", "Neurology", 0, 0},
        {23, "Dr. Rahul Khanna", "Neurology", 0, 0},

        // Dermatology
        {13, "Dr. Neha Desai", "Dermatology", 0, 0},

        // Other specialties
        {14, "Dr. Amit Kapoor", "Pulmonology", 0, 0},
        {15, "Dr. Manoj Yadav", "Gastroenterology", 0, 0},
        {16, "Dr. Pooja Rani", "Oncology", 0, 0},
        {17, "Dr. Raghav Sharma", "Psychiatry", 0, 0},
        {18, "Dr. Ravi Bhatia", "Urology", 0, 0},
        {19, "Dr. Simran Mehta", "Endocrinology", 0, 0},
        {20, "Dr. Rajiv Bhatia", "Nephrology", 0, 0},
        {21, "Dr. Harshika Patil", "Rheumatology", 0, 0}
    };

    // Comprehensive patient list from first code
    struct Patient samplePatients[] = {
        // General Medicine Patients
        {101, "Amit Mehta", 52, "Hypertension", 3, 1, 0, 0, {0}},
        {102, "Sneha Reddy", 34, "Fatigue", 2, 1, 0, 0, {0}},
        {103, "Rahul Kapoor", 40, "Chronic Fever", 4, 1, 0, 0, {0}},
        {104, "Sunita Verma", 61, "Diabetes", 5, 1, 0, 0, {0}},

        // Cardiology Patients
        {109, "Rajiv Bhatia", 72, "Heart Disease", 6, 1, 1, 0, {0}},
        {110, "Ishaan Gupta", 19, "Chest Pain", 2, 1, 0, 0, {0}},
        {111, "Nisha Jain", 28, "High Blood Pressure", 4, 1, 0, 0, {0}},
        {112, "Kabir Das", 65, "Cholesterol Management", 3, 1, 0, 0, {0}},

        // Orthopedics Patients
        {113, "Meena Yadav", 65, "Arthritis", 4, 1, 0, 0, {0}},
        {114, "Simran Kaur", 25, "Shoulder Pain", 2, 1, 0, 0, {0}},
        {202, "Vikram Singh", 45, "Back Problems", 3, 1, 0, 0, {0}},
        {203, "Priya Patel", 55, "Knee Replacement", 2, 1, 0, 0, {0}},

        // Pediatrics Patients
        {115, "Deepa Choudhury", 5, "Chickenpox", 1, 1, 0, 0, {0}},
        {116, "Kabir Kumar", 7, "Viral Fever", 1, 1, 0, 0, {0}},
        {117, "Ishaan Gupta", 6, "Growth Checkup", 2, 1, 0, 0, {0}},
        {118, "Rajiv Bhatia Jr", 8, "Vaccination", 1, 1, 0, 0, {0}},

        // Neurology Patients
        {122, "Sunita Verma", 60, "Migraine", 4, 1, 0, 0, {0}},
        {204, "Arun Malhotra", 55, "Memory Loss", 2, 1, 0, 0, {0}},
        {205, "Deepika Sharma", 45, "Nerve Pain", 3, 1, 0, 0, {0}},

        // Dermatology Patients
        {123, "Simran Mehta", 30, "Psoriasis", 2, 1, 0, 0, {0}},
        {206, "Ravi Kumar", 35, "Skin Allergy", 1, 1, 0, 0, {0}},

        // Other Specialty Patients
        {124, "Ravi Bhatia", 45, "Pneumonia", 2, 1, 0, 0, {0}},
        {125, "Priya Rani", 50, "Stomach Ulcers", 3, 1, 0, 0, {0}},
        {126, "Amit Kapoor", 55, "Lung Screening", 4, 1, 0, 0, {0}},
        {127, "Harish Kumar", 36, "Mental Health", 2, 1, 0, 0, {0}},
        {128, "Kabir Mehta", 60, "Prostate Check", 2, 1, 0, 0, {0}},
        {129, "Anjali Singh", 40, "Thyroid Issues", 3, 1, 0, 0, {0}},
        {130, "Neelam Sharma", 50, "Kidney Function", 4, 1, 0, 0, {0}},
        {131, "Deepika Raj", 45, "Joint Inflammation", 3, 1, 0, 0, {0}}
    };

    doctorCount = sizeof(sampleDoctors) / sizeof(sampleDoctors[0]);
    for (int i = 0; i < doctorCount; i++) {
        doctors[i] = sampleDoctors[i];
    }

    patientCount = sizeof(samplePatients) / sizeof(samplePatients[0]);
    for (int i = 0; i < patientCount; i++) {
        patients[i] = samplePatients[i];

        // Intelligent doctor assignment based on specialty
        int assignedDoctorId = findDoctorInSpecialty(doctors, doctorCount, 
            (strcmp(patients[i].disease, "Heart Disease") == 0 || 
             strcmp(patients[i].disease, "Chest Pain") == 0 || 
             strcmp(patients[i].disease, "High Blood Pressure") == 0 ||
             strcmp(patients[i].disease, "Cholesterol Management") == 0) ? "Cardiology" :
            (strcmp(patients[i].disease, "Arthritis") == 0 || 
             strcmp(patients[i].disease, "Shoulder Pain") == 0 ||
             strcmp(patients[i].disease, "Back Problems") == 0 ||
             strcmp(patients[i].disease, "Knee Replacement") == 0) ? "Orthopedics" :
            (patients[i].age < 12) ? "Pediatrics" :
            (strcmp(patients[i].disease, "Migraine") == 0 || 
             strcmp(patients[i].disease, "Memory Loss") == 0 || 
             strcmp(patients[i].disease, "Nerve Pain") == 0) ? "Neurology" :
            (strcmp(patients[i].disease, "Psoriasis") == 0 || 
             strcmp(patients[i].disease, "Skin Allergy") == 0) ? "Dermatology" :
            (strcmp(patients[i].disease, "Lung Screening") == 0 || 
             strcmp(patients[i].disease, "Pneumonia") == 0) ? "Pulmonology" :
            (strcmp(patients[i].disease, "Prostate Check") == 0 || 
             strcmp(patients[i].disease, "Kidney Function") == 0) ? "Urology" :
            (strcmp(patients[i].disease, "Thyroid Issues") == 0) ? "Endocrinology" :
            (strcmp(patients[i].disease, "Stomach Ulcers") == 0) ? "Gastroenterology" :
            (strcmp(patients[i].disease, "Mental Health") == 0) ? "Psychiatry" :
            "General Medicine");

        patients[i].assignedDoctorId = assignedDoctorId;

        // Find the doctor and increment their patient count
        for (int j = 0; j < doctorCount; j++) {
            if (doctors[j].id == assignedDoctorId) {
                doctors[j].patientsAttended++;
                break;
            }
        }
    }

    // Rest of the code remains the same as previous version
    FILE *fp = fopen("hospital_data.bin", "wb");
    if (fp == NULL) {
        printf("Error creating data file!\n");
        return 1;
    }

    fwrite(&patientCount, sizeof(int), 1, fp);
    fwrite(&doctorCount, sizeof(int), 1, fp);

    fwrite(patients, sizeof(struct Patient), MAX_PATIENTS, fp);
    fwrite(doctors, sizeof(struct Doctor), MAX_DOCTORS, fp);

    fclose(fp);
    printf("Data file generated successfully!\n");
    printf("Created with %d patients and %d doctors\n", patientCount, doctorCount);

    // Print out patient-doctor assignments for verification
    printf("\nPatient-Doctor Assignments:\n");
    for (int i = 0; i < patientCount; i++) {
        for (int j = 0; j < doctorCount; j++) {
            if (doctors[j].id == patients[i].assignedDoctorId) {
                printf("Patient %d (%s): Assigned to Dr. %s (Specialty: %s)\n", 
                       patients[i].id, patients[i].name, 
                       doctors[j].name, doctors[j].specialty);
                break;
            }
        }
    }

    return 0;
}
