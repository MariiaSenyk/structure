#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

void updateGrade(map<string, int>& grades, const string& name, int newGrade) {
    auto it = grades.find(name);
    if (it != grades.end()) {
        cout << "Grade updated for \"" << name << "\": "
             << it->second << " -> " << newGrade << "\n";
        it->second = newGrade;
    } else {
        grades[name] = newGrade;
        cout << "Student \"" << name << "\" not found. "
             << "New record added with grade " << newGrade << ".\n";
    }
}

void printGrades(const map<string, int>& grades) {
    if (grades.empty()) {
        cout << "Student list is empty.\n";
        return;
    }
    cout << "\n--- Students and Grades ---\n";
    for (const auto& [name, grade] : grades) {
        cout << name << ": " << grade << "\n";
    }
}

int main() {
    map<string, int> grades = {
        {"Alice Johnson",  85},
        {"Bob Smith",      92},
        {"Carol White",    74},
        {"David Brown",    88},
        {"Eva Davis",      67}
    };

    cout << "Initial grades:";
    printGrades(grades);

    int choice;
    do {
        cout << "\n1. Update / add student grade\n"
             << "2. Show all grades\n"
             << "0. Exit\n"
             << "Your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string name;
                int grade;
                cout << "Student name: ";
                getline(cin, name);
                cout << "New grade (0-100): ";
                cin >> grade;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (grade < 0 || grade > 100) {
                    cout << "Invalid grade. Enter a value between 0 and 100.\n";
                } else {
                    updateGrade(grades, name, grade);
                }
                break;
            }
            case 2:
                printGrades(grades);
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}