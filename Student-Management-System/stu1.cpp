#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

class Student {
private:
    int roll, age;
    string name, course;

public:
    // Add Student
void addStudent() {
    ofstream file("students.txt", ios::app);

    // Roll Number (4 digits)
    do {
        cout << "\nEnter Roll Number (4 digits): ";
        cin >> roll;

        if (roll < 1000 || roll > 9999)
            cout << "Invalid! Roll Number must be exactly 4 digits.\n";

    } while (roll < 1000 || roll > 9999);

    cin.ignore();

    // Name Validation
while (true) {
    cout << "Enter Name (First Last): ";
    getline(cin, name);

    int spaces = 0;
    bool valid = true;

    for (int i = 0; i < name.length(); i++) {
        if (name[i] == ' ')
            spaces++;
        else if ((name[i] >= 'A' && name[i] <= 'Z') ||
                 (name[i] >= 'a' && name[i] <= 'z')) {
            // valid letter
        }
        else {
            valid = false;
            break;
        }
    }

    if (spaces != 1) {
        cout << "Error! Enter exactly two words.\n";
        continue;
    }

    if (!valid) {
        cout << "Error! Name should contain only alphabets.\n";
        continue;
    }

    name[0] = toupper(name[0]);
    int pos = name.find(' ');
    name[pos + 1] = toupper(name[pos + 1]);

    break;
}
    // Age (17-30 years)
    do {
        cout << "Enter Age (17-30): ";
        cin >> age;

        if (age < 17 || age > 30)
            cout << "Invalid Age! Enter between 17 and 30.\n";

    } while (age < 17 || age > 30);

    cin.ignore();

    cout << "Enter Course: ";
getline(cin, course);

file << roll << "|" << name << "|" << age << "|" << course << endl;

file.close();

cout << "\n====================================";
cout << "\nStudent Added Successfully!!";
cout << "\n====================================\n";
}
    // Display Students
    void displayStudents() {
        ifstream file("students.txt");

        if (!file) {
            cout << "\nNo Records Found!\n";
            return;
        }

        string line;

        cout << "\n-----------------------------------------------------------\n";
        cout << left << setw(10) << "Roll"
             << setw(20) << "Name"
             << setw(10) << "Age"
             << setw(20) << "Course" << endl;
        cout << "-----------------------------------------------------------\n";

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            cout << left
                 << setw(10) << line.substr(0, p1)
                 << setw(20) << line.substr(p1 + 1, p2 - p1 - 1)
                 << setw(10) << line.substr(p2 + 1, p3 - p2 - 1)
                 << setw(20) << line.substr(p3 + 1)
                 << endl;
        }

        file.close();
    }

    // Search Student
    void searchStudent() {
        ifstream file("students.txt");

        string line;
        int searchRoll;
        bool found = false;

        cout << "\nEnter Roll Number: ";
        cin >> searchRoll;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            int r = stoi(line.substr(0, p1));

            if (r == searchRoll) {
                size_t p2 = line.find('|', p1 + 1);
                size_t p3 = line.find('|', p2 + 1);

                cout << "\nStudent Found\n";
                cout << "Roll   : " << r << endl;
                cout << "Name   : " << line.substr(p1 + 1, p2 - p1 - 1) << endl;
                cout << "Age    : " << line.substr(p2 + 1, p3 - p2 - 1) << endl;
                cout << "Course : " << line.substr(p3 + 1) << endl;

                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nStudent Not Found!\n";

        file.close();
    }

    // Update Student
    void updateStudent() {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        string line;
        int searchRoll;
        bool found = false;

        cout << "\nEnter Roll Number to Update: ";
        cin >> searchRoll;
        cin.ignore();

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            int r = stoi(line.substr(0, p1));

            if (r == searchRoll) {
                found = true;

                string newName, newCourse;
                int newAge;

                cout << "Enter New Name: ";
                getline(cin, newName);

                cout << "Enter New Age: ";
                cin >> newAge;
                cin.ignore();

                cout << "Enter New Course: ";
                getline(cin, newCourse);

                temp << r << "|" << newName << "|" << newAge << "|" << newCourse << endl;
            } else {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "\nRecord Updated Successfully!\n";
        else
            cout << "\nStudent Not Found!\n";
    }

    // Delete Student
    void deleteStudent() {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        string line;
        int searchRoll;
        bool found = false;

        cout << "\nEnter Roll Number to Delete: ";
        cin >> searchRoll;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            int r = stoi(line.substr(0, p1));

            if (r == searchRoll) {
                found = true;
                continue;
            }

            temp << line << endl;
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "\nRecord Deleted Successfully!\n";
        else
            cout << "\nStudent Not Found!\n";
    }

    // Count Students
    void totalStudents() {
        ifstream file("students.txt");
        string line;
        int count = 0;

        while (getline(file, line))
            count++;

        cout << "\nTotal Students: " << count << endl;

        file.close();
    }
};

int main() {
    Student s;
    int choice;

    do {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Total Students\n";
        cout << "7. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
    s.addStudent();
    break;
        case 2:
            s.displayStudents();
            break;
        case 3:
            s.searchStudent();
            break;
        case 4:
            s.updateStudent();
            break;
        case 5:
            s.deleteStudent();
            break;
        case 6:
            s.totalStudents();
            break;
        case 7:
            cout << "\nThank You!\n";
            break;
        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
