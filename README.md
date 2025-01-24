# Hospital Management System

## Overview
A comprehensive C-based hospital management system that allows efficient tracking and management of patients, doctors, and medical queues.

## Prerequisites
- GCC Compiler
- Linux/Unix or Windows with MinGW

## Compilation
```bash
gcc hospital_management.c -o hospital_management
gcc generate_data.c -o generate_data
```

## Running the Application
1. Generate initial data:
```bash
./generate_data
```

2. Run the main application:
```bash
./hospital_management
```

## Key Components
- `hospital_management.c`: Core management system
- `generate_data.c`: Data initialization and population
- `hospital_data.bin`: Persistent data storage

## Functionality
- Patient Record Management
- Doctor Assignment System
- Priority-based Waiting Queue
- Data Persistence
- Doctor Performance Tracking

## Data Structures
- Patient Management: Hash Table
- Doctor Management: Array
- Queue Management: Priority Queue

## License
MIT License
