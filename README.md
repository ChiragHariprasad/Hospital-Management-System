Patient and Doctor Management System

Overview

This C program is a simple management system designed to handle:

Patient records.

Doctor assignments.

A waiting queue for patients.

The program uses data structures such as arrays, hash tables, and queues to organize and manage the data efficiently. It is an interactive console application with menu-driven functionality.

Features

1. Patient Record Management:

Add Patient:

Stores details such as ID, name, age, disease, and visit history.

Uses a hash function for efficient storage and lookup.

Handles collisions with linear probing.

Remove Patient:

Removes a patient from the records using their ID.

Frees up the occupied slot in the hash table.

Display Patient Records:

Displays all stored patient details.

2. Doctor Assignment Management:

Add Doctor:

Stores doctor details including ID, name, and specialty.

Remove Doctor:

Deletes a doctor record using their ID.

Display Doctor Assignments:

Lists doctors and their specialties, along with the patients assigned to them.

3. Waiting Queue Management:

Add Patient to Queue:

Adds a patient's ID to the waiting queue.

Maintains a FIFO (First In, First Out) structure.

Remove Patient from Queue:

Removes the patient at the front of the queue.

Display Waiting Queue:

Shows the IDs and names of patients in the queue.

Data Structures

Hash Table (Patient Records):

Maps patient IDs to their details using a hash function.

Handles collisions using linear probing.

Queue (Waiting Queue):

Implements a circular queue for managing patient waiting lists.

Array (Doctor Records):

Stores doctor details in a simple array.

Functions

General Utility

hash(int id): Computes the hash value for patient IDs.

Patient Management

addPatient: Adds a new patient to the system.

removePatient: Removes a patient from the system by ID.

displayPatients: Prints all patient records.

Doctor Management

addDoctor: Adds a new doctor to the system.

removeDoctor: Removes a doctor by ID.

displayDoctors: Lists doctors along with their assigned patients.

Queue Operations

initQueue: Initializes a queue.

isQueueEmpty: Checks if the queue is empty.

enqueue: Adds a patient ID to the queue.

dequeue: Removes the patient ID at the front of the queue.

displayQueue: Displays all patient IDs in the queue with their details.

Program Flow

Main Menu:

Navigate between patient records, doctor assignments, and waiting queue management.

Submenus:

Each section has its submenu for specific actions (e.g., add/remove/display).

Exit Option:

Ends the program execution gracefully.

Limitations

Fixed Sizes:

Maximum patients: 100.

Maximum doctors: 10.

Collision Handling:

Uses linear probing, which may degrade performance with high collision rates.

Queue Overflow:

Queue has a fixed capacity of 100 patients.

How to Run

Compile the program using a C compiler, such as GCC:

gcc -o management_system management_system.c

Run the executable:

./management_system

Follow the on-screen menu to interact with the system.

Future Enhancements

Dynamic memory allocation for handling larger data sets.

Implementing priority queues for patients based on severity.

Adding database integration for persistent storage.

Enhancing doctor-patient assignment logic.

Author

This program is collaboratively developed by Chirag, Mowin, Mownil, Joseph, and Shamith, as part of a project to explore data structures and analytics in practical applications.

