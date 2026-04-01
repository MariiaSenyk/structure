#include<iostream>
#include<string>
using namespace std;
enum Faculty
{
    IT = 1,
    Economics,
    Law,
    Management
};
struct Student
{
    string surname;
    int year{};
    double averageGrade{};
    Faculty faculty;

    void inputData()
    {
        cout << "Surname: ";
        cin.ignore();
        getline(cin, surname);
        cout << "Year (Course): ";
        cin >> year;
        cout << "Average grade: ";
        cin >> averageGrade;
        int facultyChoice;
        cout << "Faculty (1 - IT, 2 - Economics, 3 - Law, 4 - Management): ";
        cin >> facultyChoice;
        faculty = static_cast<Faculty>(facultyChoice);
    }

    void displayStudent() const
    {
        cout << "Surname: " << surname << ", Course: " << year << ", Average Grade: " << averageGrade << endl;
    }

    Faculty getFaculty() const
    {
        return faculty;
    }

    double getAverageGrade() const
    {
        return averageGrade;
    }
};

double groupAverage(Student students[], int size)
{
    double total = 0;
    for (int i = 0; i < size; ++i)
        total += students[i].getAverageGrade();
    return total / size;
}

void showByFaculty(Student students[], int size, Faculty faculty)
{
    for (int i = 0; i < size; ++i) {
        if (students[i].getFaculty() == faculty)
            students[i].displayStudent();
    }
}

int main()
{
    constexpr int numberOfStudents = 5;
    Student students[numberOfStudents];
    for (int i = 0; i < numberOfStudents; ++i) {
        cout << "Enter data for student " << i + 1 << endl;
        students[i].inputData();
    }

    int facultyChoice;
    cout << "\nEnter faculty to filter by (1 - IT, 2 - Economics, 3 - Law, 4 - Management): ";
    cin >> facultyChoice;
    showByFaculty(students, numberOfStudents, static_cast<Faculty>(facultyChoice));

    double group_average = groupAverage(students, numberOfStudents);
    cout << "\nAverage grade for the whole group: " << group_average << endl;

    return 0;
}