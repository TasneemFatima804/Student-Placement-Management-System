#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class Student {
public:
int rollNo = 0;

string name;
string department;

float cgpa = 0.0;

string email;
string phone;

bool placed = false;

string internshipOffer;
string placementOffer;

string password;

    void inputData(const vector<Student>& students) {
        cout << "Enter Roll No: ";
        while (!(cin >> rollNo) || rollNo <= 0) {
            cout << "Invalid input. Enter a positive integer for Roll No: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Prevent duplicate Roll No
        for (const auto& s : students) {
            if (s.rollNo == rollNo) {
                cout << "Error: Roll No already exists!\n";
                rollNo = 0; // Signal failure
                return;
            }
        }

        do {
            cout << "Enter Name: ";
            getline(cin, name);
            do {
        cout << "Enter Department: ";
        getline(cin, department);
    }        while (department.empty());

cout << "Enter CGPA: ";
while (!(cin >> cgpa) || cgpa < 0 || cgpa > 10) {
    cout << "Invalid CGPA! Enter between 0 and 10: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
cin.ignore(numeric_limits<streamsize>::max(), '\n');

do {
    cout << "Enter Email: ";
    getline(cin, email);
} while (email.empty());

do {
    cout << "Enter Phone Number: ";
    getline(cin, phone);
} while (phone.empty());

char status;
cout << "Is the student placed? (Y/N): ";
cin >> status;
cin.ignore(numeric_limits<streamsize>::max(), '\n');

placed = (status == 'Y' || status == 'y');
        } while (name.empty());

        do {
            cout << "Enter Internship Offer: ";
            getline(cin, internshipOffer);
        } while (internshipOffer.empty());

        do {
            cout << "Enter Placement Offer: ";
            getline(cin, placementOffer);
        } while (placementOffer.empty());

        do {
            cout << "Set Password for Student Login: ";
            getline(cin, password);
        } while (password.empty());
    }

    void displayData() const {

    cout << left
         << setw(8)  << rollNo
         << setw(20) << name
         << setw(15) << department
         << setw(8)  << fixed << setprecision(2) << cgpa
         << setw(15) << phone
         << setw(12) << (placed ? "Placed" : "Not Placed")
         << endl;
}
};

class Faculty {
private:
    string password = "faculty123"; 

public:
    bool login() {
        string pass;
        cout << "Enter Faculty Password: ";
        cin >> pass;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after cin >>
        
        if (pass == password) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Incorrect password!\n";
            return false;
        }
    }

    void editStudent(vector<Student>& students) {
        int roll;
        cout << "Enter Roll No to edit: ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (auto &s : students) {
            if (s.rollNo == roll) {
                cout << "Editing record for " << s.name << "\n";
                cout << "Enter new Internship Offer: ";
                getline(cin, s.internshipOffer);
                cout << "Enter new Placement Offer: ";
                getline(cin, s.placementOffer);
                cout << "Record updated!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void deleteStudent(vector<Student>& students) {
        int roll;
        cout << "Enter Roll No to delete: ";
        cin >> roll;
        
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->rollNo == roll) {
                char choice;
                cout << "Are you sure you want to delete " << it->name << "? (Y/N): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear trailing newline

                if (choice == 'Y' || choice == 'y') {
                    students.erase(it);
                    cout << "Record deleted!\n";
                } else {
                    cout << "Deletion cancelled!\n";
                }
                return;
            }
        }
        cout << "Student not found!\n";
    } 
};

class StudentPortal {
public:
    bool login(const Student& s) {
        string pass;
        cout << "Enter password for " << s.name << ": ";
        cin >> pass;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pass == s.password) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Incorrect password!\n";
            return false;
        }
    }

    void editSelf(Student& s) {
        cout << "Editing your record, " << s.name << "\n";
        cout << "Enter new Internship Offer: ";
        getline(cin, s.internshipOffer);
        cout << "Enter new Placement Offer: ";
        getline(cin, s.placementOffer);
        cout << "Record updated!\n";
    }
};

void saveToCSV(const vector<Student>& students) {
    ofstream file("students.csv");
    if (!file.is_open()) {
        cout << "Error opening file for writing!\n";
        return;
    }
    file << "RollNo,Name,Department,CGPA,Email,Phone,Placed,Internship,Placement,Password\n";
    for (const auto& s : students) {
        file << s.rollNo << ","
     << s.name << ","
     << s.department << ","
     << s.cgpa << ","
     << s.email << ","
     << s.phone << ","
     << s.placed << ","
     << s.internshipOffer << ","
     << s.placementOffer << ","
     << s.password << "\n";
    }
}

vector<Student> loadFromCSV() {
    vector<Student> students;
    ifstream file("students.csv");
    if (!file.is_open()) return students;

    string line;
    getline(file, line); // Skip header row

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Student s;
        string rollNoStr;

        getline(ss, rollNoStr, ',');
        if (rollNoStr.empty()) continue;

        try {
            s.rollNo = stoi(rollNoStr);
        } catch (...) {
            continue;
        }

        getline(ss, s.name, ',');
getline(ss, s.department, ',');

string cgpaStr;
getline(ss, cgpaStr, ',');
s.cgpa = stof(cgpaStr);

getline(ss, s.email, ',');
getline(ss, s.phone, ',');

string placedStr;
getline(ss, placedStr, ',');
s.placed = (placedStr == "1");

getline(ss, s.internshipOffer, ',');
getline(ss, s.placementOffer, ',');
getline(ss, s.password);

        // Trim trailing carriage return if running on Windows/DOS newline files
        if (!s.password.empty() && s.password.back() == '\r') {
            s.password.pop_back();
        }

        students.push_back(s);
    }
    return students;
}

void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }

    cout << left
     << setw(8)  << "Roll"
     << setw(20) << "Name"
     << setw(15) << "Department"
     << setw(8)  << "CGPA"
     << setw(15) << "Phone"
     << setw(12) << "Status"
     << endl;

cout << string(78, '-') << endl;

    for (const auto& s : students) {
        s.displayData();
    }
}

void searchStudent(const vector<Student>& students) {
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (const auto& s : students) {
        if (s.rollNo == roll) {
            cout << "\nRecord Found:\n";
            cout << left 
                 << setw(10) << "Roll No" 
                 << setw(22) << "Name" 
                 << setw(22) << "Internship Offer" 
                 << setw(22) << "Placement Offer" << endl;
            cout << string(76, '-') << endl;
            s.displayData();
            return;
        }
    }
    cout << "Student not found!\n";
}

int main() {
    vector<Student> students = loadFromCSV();
    Faculty faculty;
    StudentPortal portal;
    int choice = 0;

    do {
        cout << "\n====================================================\n";
        cout << "     STUDENT PLACEMENT MANAGEMENT SYSTEM\n";
        cout << "====================================================\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Faculty Edit\n";
        cout << "5. Faculty Delete\n";
        cout << "6. Student Edit (self)\n";
        cout << "7. Save & Exit\n";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cout << "Invalid choice! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            Student s;
            s.inputData(students);
            if (s.rollNo != 0) {
                students.push_back(s);
                saveToCSV(students);
            }
        }
        else if (choice == 2) {
            cout << "\n--- Student Records ---\n";
            viewStudents(students);
        }
        else if (choice == 3) {
            searchStudent(students);
        }
        else if (choice == 4) {
            if (faculty.login()) {
                faculty.editStudent(students);
                saveToCSV(students);
            }
        }
        else if (choice == 5) {
            if (faculty.login()) {
                faculty.deleteStudent(students);
                saveToCSV(students);
            }
        }
        else if (choice == 6) {
            int roll;
            cout << "Enter your Roll No: ";
            cin >> roll;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool found = false;
            for (auto &s : students) {
                if (s.rollNo == roll) {
                    found = true;
                    if (portal.login(s)) {
                        portal.editSelf(s);
                        saveToCSV(students);
                    }
                    break;
                }
            }
            if (!found) {
                cout << "Student not found!\n";
            }
        }
        else if (choice == 7) {
            saveToCSV(students);
            cout << "Data saved to 'students.csv'. Exiting...\n";
        }
        else {
            cout << "Invalid choice! Enter a number between 1 and 7.\n";
        }
    } while (choice != 7);

    return 0;
}