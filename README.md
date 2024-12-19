# Patient Management System

## Overview

This is a **Patient Management System** written in C. It is designed to manage patient records, doctor assignments, and a waiting queue system in a healthcare facility. The system utilizes structures, queues, and hashing to organize data effectively, providing functionalities such as adding/removing patients and doctors, displaying records, and managing waiting queues.

---

## Features

### 1. **Patient Record Management**
   - **Add Patient**: Records the details of a new patient.
   - **Remove Patient**: Deletes a patient record based on the provided ID.
   - **Display Patient Records**: Displays the list of all patients.

### 2. **Doctor Management**
   - **Add Doctor**: Records a new doctor's details.
   - **Remove Doctor**: Deletes a doctor’s record using their ID.
   - **Display Doctor Assignments**: Lists all doctors along with their specialties and assigned patients.

### 3. **Waiting Queue Management**
   - **Add to Queue**: Adds a patient to the waiting queue using their ID.
   - **Remove from Queue**: Removes the patient at the front of the queue.
   - **Display Queue**: Displays all patients currently in the waiting queue.

---

## System Components

### 1. **Data Structures**
   - **`struct Patient`**: Stores patient information, including ID, name, age, disease, visit history, and slot occupation status.
   - **`struct Doctor`**: Stores doctor information, including ID, name, and specialty.
   - **`struct Queue`**: Implements a queue for managing the waiting list.

### 2. **Hashing**
   - Utilizes a simple hash function to store patient records efficiently by mapping patient IDs to an index in the array.

### 3. **Collision Handling**
   - Employs linear probing to resolve hash collisions when two IDs map to the same index.

---

## How to Use

### **1. Running the Program**
   - Compile the program using a C compiler (e.g., `gcc`).
   - Execute the compiled binary.

### **2. Main Menu**
   - Select options from the main menu:
     1. **Manage Patient Records**
     2. **Manage Doctor Assignments**
     3. **Manage Waiting Queue**
     4. **Exit**

### **3. Patient Management**
   - Add a new patient by providing ID, name, age, disease, and visit history.
   - Remove an existing patient by entering their ID.
   - Display all existing patient records.

### **4. Doctor Management**
   - Add a new doctor by providing ID, name, and specialty.
   - Remove a doctor by entering their ID.
   - View all doctor-patient assignments.

### **5. Waiting Queue**
   - Add a patient to the queue by entering their ID.
   - Remove the patient at the front of the queue.
   - Display the current waiting queue.

---

## Constraints

- **Maximum Patients**: 100
- **Maximum Doctors**: 10
- **Name Length**: 50 characters

---

## Dependencies

This program does not depend on external libraries and runs on any C compiler.

---

## Notes

1. **Collision Handling**: The program uses linear probing for hashing collisions in the patient management system.
2. **Queue Implementation**: A simple queue is used for the waiting list with basic enqueue and dequeue operations.
3. **Input Validation**: Limited input validation is implemented, so ensure valid inputs during use.

---

## Future Enhancements

- Add support for saving and loading data from a file.
- Include advanced search and filtering options for patient and doctor records.
- Improve input validation and error handling.
- Implement dynamic memory allocation for scalability.

---

## Compilation Instructions

1. Save the code in a file, e.g., `patient_management.c`.
2. Compile the code using:
   ```bash
   gcc -o patient_management patient_management.c
   ```
3. Run the program:
   ```bash
   ./patient_management
   ```

---

This program is a simple yet functional patient management system designed for small-scale healthcare applications, showcasing basic data structures and algorithms in C.
