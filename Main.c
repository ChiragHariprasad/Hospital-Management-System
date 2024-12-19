#include <stdio.h>
#include <string.h>

#define MAX_PAT 100
#define MAX_DOC 10
#define MAX_NAME 50

struct Pat {
    int id;
    char name[MAX_NAME];
    int age;
    char disease[MAX_NAME];
    char visitHistory[100];
};

struct Doc {
    int id;
    char name[MAX_NAME];
    char specialty[MAX_NAME];
};

struct Queue {
    int front, rear;
    int items[MAX_PAT];
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(struct Queue* q) {
    return (q->front == -1);
}

void enqueue(struct Queue* q, int patId) {
    if (q->rear == MAX_PAT - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = patId;
}

int dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int patId = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return patId;
}

void displayPatRecords(struct Pat pats[], int patCount) {
    printf("\nPatient Records:\n");
    for (int i = 0; i < patCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s, Visit History: %s\n",
                pats[i].id, pats[i].name, pats[i].age, pats[i].disease, pats[i].visitHistory);
    }
}

void displayDocAssignments(struct Doc docs[], int docCount, struct Pat pats[], int patCount) {
    printf("\nDoctor Assignments:\n");
    for (int i = 0; i < docCount; i++) {
        printf("Doctor: %s, Specialty: %s\n", docs[i].name, docs[i].specialty);
        for (int j = 0; j < patCount; j++) {
            if (pats[j].id == (i + 1)) {
                printf("  Patient: %s, Disease: %s\n", pats[j].name, pats[j].disease);
            }
        }
    }
}

void displayWaitingQueue(struct Queue* q, struct Pat pats[], int patCount) {
    printf("\nCurrent Waiting Queue:\n");
    if (isQueueEmpty(q)) {
        printf("No patients in the queue\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        int patId = q->items[i];
        printf("Patient ID: %d, Name: %s\n", pats[patId].id, pats[patId].name);
    }
}

void addPat(struct Pat pats[], int *patCount) {
    if (*patCount >= MAX_PAT) {
        printf("Cannot add more patients. Maximum capacity reached.\n");
        return;
    }
    struct Pat newPat;
    printf("Enter Patient ID: ");
    scanf("%d", &newPat.id);
    getchar();
    printf("Enter Patient Name: ");
    fgets(newPat.name, MAX_NAME, stdin);
    newPat.name[strcspn(newPat.name, "\n")] = 0;
    printf("Enter Patient Age: ");
    scanf("%d", &newPat.age);
    getchar();
    printf("Enter Disease: ");
    fgets(newPat.disease, MAX_NAME, stdin);
    newPat.disease[strcspn(newPat.disease, "\n")] = 0;
    printf("Enter Visit History: ");
    fgets(newPat.visitHistory, 100, stdin);
    newPat.visitHistory[strcspn(newPat.visitHistory, "\n")] = 0;
    
    pats[*patCount] = newPat;
    (*patCount)++;
    printf("Patient added successfully!\n");
}

void removePat(struct Pat pats[], int *patCount) {
    int id;
    printf("Enter Patient ID to remove: ");
    scanf("%d", &id);
    
    int found = 0;
    for (int i = 0; i < *patCount; i++) {
        if (pats[i].id == id) {
            found = 1;
            for (int j = i; j < *patCount - 1; j++) {
                pats[j] = pats[j + 1];
            }
            (*patCount)--;
            printf("Patient removed successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Patient not found.\n");
    }
}

void addDoc(struct Doc docs[], int *docCount) {
    if (*docCount >= MAX_DOC) {
        printf("Cannot add more doctors. Maximum capacity reached.\n");
        return;
    }
    struct Doc newDoc;
    printf("Enter Doctor ID: ");
    scanf("%d", &newDoc.id);
    getchar();
    printf("Enter Doctor Name: ");
    fgets(newDoc.name, MAX_NAME, stdin);
    newDoc.name[strcspn(newDoc.name, "\n")] = 0;
    printf("Enter Doctor Specialty: ");
    fgets(newDoc.specialty, MAX_NAME, stdin);
    newDoc.specialty[strcspn(newDoc.specialty, "\n")] = 0;
    
    docs[*docCount] = newDoc;
    (*docCount)++;
    printf("Doctor added successfully!\n");
}

void removeDoc(struct Doc docs[], int *docCount) {
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
    struct Pat pats[MAX_PAT];
    int patCount = 0;
    
    struct Doc docs[MAX_DOC];
    int docCount = 0;
    
    struct Queue q;
    initQueue(&q);
    
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
                    addPat(pats, &patCount);
                } else if (recordChoice == 2) {
                    removePat(pats, &patCount);
                } else if (recordChoice == 3) {
                    displayPatRecords(pats, patCount);
                }
                break;
            case 2:
                printf("\nDoctor Assignment Management:\n");
                printf("1. Add Doctor\n");
                printf("2. Remove Doctor\n");
                printf("3. Display Doctor Assignments\n");
                printf("Enter your choice: ");
                int docChoice;
                scanf("%d", &docChoice);
                if (docChoice == 1) {
                    addDoc(docs, &docCount);
                } else if (docChoice == 2) {
                    removeDoc(docs, &docCount);
                } else if (docChoice == 3) {
                    displayDocAssignments(docs, docCount, pats, patCount);
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
                    int patId;
                    printf("Enter Patient ID to add to queue: ");
                    scanf("%d", &patId);
                    enqueue(&q, patId);
                } else if (queueChoice == 2) {
                    dequeue(&q);
                } else if (queueChoice == 3) {
                    displayWaitingQueue(&q, pats, patCount);
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
