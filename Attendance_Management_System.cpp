#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

const int MAX_STUDENTS = 50;

// Function declarations
void addStudents(string names[], int &count);
void markAttendance(char attendance[], int count);
void displayAttendance(string names[], char attendance[], int count);
void saveToFile(string names[], char attendance[], int count);
void loadFromFile(string names[], char attendance[], int &count);

int main() {
    string studentNames[MAX_STUDENTS];
    char attendance[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        cout << "\n===== Attendance Management System =====\n";
        cout << "1. Add Students\n";
        cout << "2. Mark Attendance\n";
        cout << "3. Display Attendance\n";
        cout << "4. Save Attendance to File\n";
        cout << "5. Load Attendance from File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudents(studentNames, studentCount);
                break;

            case 2:
                markAttendance(attendance, studentCount);
                break;

            case 3:
                displayAttendance(studentNames, attendance, studentCount);
                break;

            case 4:
                saveToFile(studentNames, attendance, studentCount);
                break;

            case 5:
                loadFromFile(studentNames, attendance, studentCount);
                break;

            case 6:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}

// Add students
void addStudents(string names[], int &count) {
    int n;

    cout << "How many students do you want to add? ";
    while (!(cin >> n)) {
        cout << "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cin.ignore();

    for (int i = 0; i < n && count < MAX_STUDENTS; i++) {
        cout << "Enter name of student " << count + 1 << ": ";
        getline(cin, names[count]);
        count++;
    }
}

// Mark attendance
void markAttendance(char attendance[], int count) {
    if (count == 0) {
        cout << "No students found.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "Mark attendance for student " << i + 1
             << " (P/A): ";
        cin >> attendance[i];
        attendance[i] = toupper(attendance[i]);

        if (attendance[i] != 'P' && attendance[i] != 'A') {
            cout << "Invalid input! Marked as Absent.\n";
            attendance[i] = 'A';
        }
    }
}

// Display attendance
void displayAttendance(string names[], char attendance[], int count) {
    if (count == 0) {
        cout << "No attendance data available.\n";
        return;
    }

    cout << "\n--- Attendance Report ---\n";
    for (int i = 0; i < count; i++) {
        cout << names[i] << " : "
             << (attendance[i] == 'P' ? "Present" : "Absent") << endl;
    }
}

// Save data to file
void saveToFile(string names[], char attendance[], int count) {
    ofstream file("attendance.txt");

    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    file << count << endl;
    for (int i = 0; i < count; i++) {
        file << names[i] << " " << attendance[i] << endl;
    }

    file.close();
    cout << "Attendance saved successfully.\n";
}

// Load data from file
void loadFromFile(string names[], char attendance[], int &count) {
    ifstream file("attendance.txt");

    if (!file) {
        cout << "No saved file found.\n";
        return;
    }

    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        file >> names[i] >> attendance[i];
    }

    file.close();
    cout << "Attendance loaded successfully.\n";
}
