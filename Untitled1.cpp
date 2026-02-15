#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int SIZE = 100;
int rollNos[SIZE];
string names[SIZE];
float marks[SIZE];
int total = 0;
const string FILE_NAME = "students.txt";

// Load data from file
void loadData() {
    ifstream file(FILE_NAME);

    if (!file) {
        ofstream createFile(FILE_NAME); // create file if not exists
        createFile.close();
        return;
    }

    while (total < SIZE && file >> rollNos[total]) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, names[total]);
        file >> marks[total];
        total++;
    }
    file.close();
}

// Save data to file
void saveData() {
    ofstream file(FILE_NAME);
    for (int i = 0; i < total; i++) {
        file << rollNos[i] << '\n';
        file << names[i] << '\n';
        file << marks[i] << '\n';
    }
    file.close();
}

// Add student
void addStudent() {
    if (total >= SIZE) {
        cout << "Database Full!\n";
        return;
    }

    cout << "Enter Roll No: ";
    cin >> rollNos[total];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Name: ";
    getline(cin, names[total]);

    do {
        cout << "Enter Marks (0 - 1100): ";
        cin >> marks[total];
    } while (marks[total] < 0 || marks[total] > 1100);

    total++;
    saveData();

    cout << "Student Added & Saved Successfully!\n";
}

// Show students
void showStudents() {
    if (total == 0) {
        cout << "No records found!\n";
        return;
    }

    for (int i = 0; i < total; i++) {
        float percentage = (marks[i] * 100.0f) / 1100;
        cout << "\nRoll No: " << rollNos[i];
        cout << "\nName: " << names[i];
        cout << "\nMarks: " << marks[i];
        cout << "\nPercentage: " << percentage << "%\n";
    }
}

int main() {
    loadData();

    int choice;
    do {
        cout << "\n1. Add\n2. Show\n3. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: showStudents(); break;
            case 3: cout << "Program Exit\n"; break;
            default: cout << "Invalid Choice\n";
        }
    } while (choice != 3);

    return 0;
}
