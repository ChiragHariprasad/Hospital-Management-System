#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define MAX_NAME_LEN 50

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
    struct Patient patients[MAX_PATIENTS] = {0};
    struct Doctor doctors[MAX_DOCTORS] = {0};
    int patientCount = 0;
    int doctorCount = 0;

    struct Doctor sampleDoctors[] = {
        {1, "Dr. Rajesh Kumar", "Cardiology", 0},
        {2, "Dr. Priya Sharma", "Pediatrics", 0},
        {3, "Dr. Anil Patel", "Orthopedics", 0},
        {4, "Dr. Kavita Nair", "General Medicine", 0},
        {5, "Dr. Suresh Iyer", "Neurology", 0},
        {6, "Dr. Neha Desai", "Dermatology", 0},
        {7, "Dr. Vikram Rao", "Psychiatry", 0}
    };

    struct Patient samplePatients[] = {
        {101, "Amit Mehta", 52, "Hypertension", 3, 1, 0},
        {102, "Sneha Reddy", 34, "Fractured Leg", 2, 1, 1},
        {103, "Rahul Kapoor", 40, "Migraine", 4, 1, 0},
        {104, "Sunita Verma", 61, "Diabetes", 5, 1, 0},
        {105, "Arjun Joshi", 6, "Viral Fever", 1, 1, 0},
        {106, "Pooja Singh", 47, "Back Pain", 3, 1, 0},
        {107, "Ravi Nair", 31, "Anxiety", 2, 1, 0},
        {108, "Lakshmi Rao", 55, "Skin Allergy", 2, 1, 0},
        {109, "Rajiv Bhatia", 72, "Heart Disease", 6, 1, 1},
        {110, "Ishaan Gupta", 19, "Sports Injury", 1, 1, 0},
        {111, "Deepa Choudhury", 50, "Depression", 3, 1, 0},
        {112, "Nisha Jain", 28, "Insomnia", 4, 1, 0},
        {113, "Kabir Das", 8, "Tonsillitis", 1, 1, 0},
        {114, "Meena Yadav", 65, "Arthritis", 4, 1, 0},
        {115, "Simran Kaur", 25, "Severe Allergies", 2, 1, 1}
    };

    doctorCount = sizeof(sampleDoctors) / sizeof(sampleDoctors[0]);
    for (int i = 0; i < doctorCount; i++) {
        doctors[i] = sampleDoctors[i];
    }

    patientCount = sizeof(samplePatients) / sizeof(samplePatients[0]);
    for (int i = 0; i < patientCount; i++) {
        patients[i] = samplePatients[i];
    }

    FILE *fp = fopen("hospital_data_india.bin", "wb");
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

    return 0;
}
