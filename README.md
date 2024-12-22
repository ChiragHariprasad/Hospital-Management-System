# Hospital Management System

## Overview
A comprehensive C-based Hospital Management System designed to manage patient records, doctor assignments, and a priority-based waiting queue. The system includes features for handling both regular and emergency patients, tracking patient visits, and managing doctor availability.

## Features

### 1. Patient Management
- Add new patients with details (ID, name, age, condition)
- Remove existing patients
- Track patient visit history
- Distinguish between emergency and regular patients
- View all patient records in a formatted display

### 2. Doctor Management
- Add new doctors with specializations
- Remove doctors from the system
- Track doctor availability status
- View all doctor records and their current status
- Assign doctors to patients

### 3. Waiting Queue System
- Priority-based queue (emergency patients get priority)
- Add patients to waiting queue
- Remove patients from queue when doctor available
- View current queue status

### 4. Data Persistence
- Save all records to binary file
- Load existing records on startup
- Sample data generation utility included

## System Requirements
- C compiler (GCC recommended)
- Terminal/Command Prompt
- Operating System: Windows/Linux/MacOS

## Installation & Setup

1. **Compile the Data Generator:**
```bash
gcc generate_data.c -o generate_data
```

2. **Generate Initial Sample Data:**
```bash
./generate_data
```

3. **Compile the Main Program:**
```bash
gcc hospital_management.c -o hospital_management
```

4. **Run the Program:**
```bash
./hospital_management
```

## File Structure
- `hospital_management.c` - Main program file
- `generate_data.c` - Sample data generator utility
- `hospital_data.bin` - Binary file storing system data

## Sample Data Included

### Sample Patients
- 15 patients with various conditions
- Mix of emergency and regular cases
- Various age groups and medical conditions
- Different visit histories

## Usage Guide

### Main Menu Options
1. **Manage Patient Records**
   - Add new patients
   - Remove existing patients
   - View all patient records

2. **Manage Doctor Assignments**
   - Add new doctors
   - Remove doctors
   - View doctor status
   - Mark doctors as available

3. **Manage Waiting Queue**
   - Add patients to queue
   - Remove patients from queue
   - View current queue

4. **Save and Exit**
   - Save all changes to file
   - Exit program

### Navigation
- Use number keys to select menu options
- Press Enter after each selection
- Follow on-screen prompts for data entry
- Press Enter to continue after viewing records

## Data Management
- All data is automatically saved when exiting
- Previous data is loaded on startup
- If no previous data exists, sample data is loaded

## Technical Details

### Data Structures
- Maximum 100 patients
- Maximum 10 doctors
- Priority queue for patient waiting list
- Hash table implementation for patient records

### Algorithms
- Hash-based patient record storage
- Priority-based queuing system
- Linear probing for collision resolution

## Best Practices
1. Always save before exiting
2. Update doctor status after patient consultation
3. Check waiting queue regularly
4. Verify patient ID before operations
5. Keep track of emergency cases

## Error Handling
- Checks for maximum capacity
- Validates patient and doctor IDs
- Handles file operations safely
- Prevents duplicate entries

## Limitations
- Fixed maximum capacity for patients and doctors
- Single binary file for data storage
- Basic text-based user interface

## Future Improvements
1. Database integration
2. Multi-user support
3. Appointment scheduling
4. Patient history tracking
5. Advanced reporting features
6. GUI implementation

## Support
For issues and suggestions:
1. Check input data format
2. Verify file permissions
3. Ensure proper compilation
4. Check system requirements

## Contributing
To contribute to this project:
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License
This project is open-source and available under the MIT License.
