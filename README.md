# Hospital Management System

## Overview

This project provides a feature-rich Hospital Management System designed to streamline hospital operations, including patient and doctor management, emergency handling, and data persistence. The system leverages intelligent algorithms to assign doctors to patients based on specialties and workload while supporting priority queue handling and visit history tracking.

### Files in the Repository
1. **`hospital_management.c`**: The main program for managing the hospital, including all user interactions and system operations.
2. **`generate_data.c`**: A utility program for generating a dummy dataset (`hospital_data.bin`) that is used by the main program.

---

## Features

### `hospital_management.c` (Main Program)
- **Patient Management**:
  - Add, remove, and display patient records.
  - Track and view patient visit history.
  - Assign doctors to patients intelligently based on specialty and workload.

- **Doctor Management**:
  - Add and remove doctors.
  - Monitor doctor availability and performance (patients attended).
  - Reassign patients from busy doctors to available ones.

- **Priority Queue**:
  - Handle emergency and regular patient queues efficiently.
  - Process patients based on priority (emergency cases prioritized).

- **Data Persistence**:
  - Save all hospital data (patients, doctors, queues) to a binary file (`hospital_data.bin`).
  - Load data from the file to resume previous sessions.

### `generate_data.c` (Dummy Data Generator)
- Initializes a dataset with sample doctors and patients.
- Automatically assigns patients to doctors based on specialty and workload.
- Creates a `hospital_data.bin` file for use by the main program.

---

## Data Structures Used

1. **Structs**:
   - **`struct Doctor`**: Stores doctor details such as ID, name, specialty, availability, and patients attended.
   - **`struct Patient`**: Stores patient details, including ID, name, age, disease, emergency status, assigned doctor ID, and visit history.
   - **`struct VisitRecord`**: Tracks a patient’s visit history with the doctor’s name and notes for each visit.

2. **Arrays**:
   - Used to store lists of patients and doctors (`struct Patient patients[MAX_PATIENTS]` and `struct Doctor doctors[MAX_DOCTORS]`).
   - `struct VisitRecord` arrays are used to store a patient’s visit history.

3. **Priority Queue**:
   - Implemented for managing the waiting queue, prioritizing emergency patients over regular ones.
   - **Structure**:
     ```c
     struct PriorityQueue {
         int front, rear;
         struct {
             int patientId;
             int priority;  // 1 for emergency, 0 for common
         } items[MAX_PATIENTS];
     };
     ```
   - Operations:
     - **Enqueue**: Adds patients to the queue based on their priority.
     - **Dequeue**: Removes the highest-priority patient from the queue.

4. **Hashing**:
   - Hash function: `id % MAX_PATIENTS` for quick indexing of patients in the array.
   - Used for efficient patient lookup and addition while resolving collisions via linear probing.

---

## How to Run

1. **Compile** the files:
   ```bash
   gcc hospital_management.c -o hospital_management
   gcc generate_data.c -o generate_data
   ```

2. **Generate Dummy Data**:
   Run the `generate_data` executable to create the `hospital_data.bin` file:
   ```bash
   ./generate_data
   ```

3. **Run the Main Program**:
   Use the `hospital_management` executable to interact with the system:
   ```bash
   ./hospital_management
   ```

---

## Usage Instructions

1. **Patient Record Management**:
   - Add new patients or remove existing ones.
   - View detailed patient records, including visit history.
   - Assign patients to doctors intelligently.

2. **Doctor Management**:
   - Add or remove doctors from the system.
   - Monitor doctor availability and track their performance.

3. **Waiting Queue Management**:
   - Add emergency or regular patients to the waiting queue.
   - Process the queue based on patient priority.

4. **Save and Exit**:
   - Save all changes to the `hospital_data.bin` file to preserve continuity.

---

## Example Outputs

### `generate_data.c`
Upon execution, this program generates a sample dataset and outputs patient-doctor assignments. For example:
```
Patient 101 (Amit Mehta): Assigned to Dr. Rajesh Kumar (Specialty: General Medicine)
Patient 109 (Rajiv Bhatia): Assigned to Dr. Suresh Iyer (Specialty: Cardiology)
...
Data file generated successfully!
```

### `hospital_management.c`
The main program provides an interactive menu:
```
========================================
           Hospital Management System
========================================

1. Manage Patient Records
2. Manage Doctor Assignments
3. Manage Waiting Queue
4. Save and Exit

----------------------------------------
Enter your choice:
```

---

## Dependencies
- Standard C libraries: `stdio.h`, `string.h`, `stdlib.h`, `limits.h`.
- Compatible with Windows and Linux systems. Use `cls` for clearing the screen on Windows and `clear` on Linux.

---

## Future Enhancements
- Implement user authentication for secure access.
- Add a GUI for better usability and enhanced features.
- Extend functionality to include hospital inventory and billing management.
