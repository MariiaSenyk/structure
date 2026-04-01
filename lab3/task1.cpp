#include <iostream>
#include <string>
using namespace std;
enum Position
{
    Manager = 1,
    Engineer,
    Technician,
    Clerk
};
struct Worker
{
    string fullName;
    Position position;
    int yearOfJoining;
    double salary;

    void inputData()
    {
        cout << "Surname and initials: ";
        cin.ignore();
        getline(cin, fullName);
        int pos;
        cout << "Position (1 - Manager, 2 - Engineer, 3 - Technician, 4 - Clerk): ";
        cin >> pos;
        position = static_cast<Position>(pos);
        cout << "Year of joining: ";
        cin >> yearOfJoining;
        cout << "Salary: ";
        cin >> salary;
    }

    string getPositionString() const
    {
        switch (position) {
            case Manager: return "Manager";
            case Engineer: return "Engineer";
            case Technician: return "Technician";
            case Clerk: return "Clerk";
            default: return "Unknown";
        }
    }
};

int experience(const Worker& w, int currentYear)
{
    if (currentYear < w.yearOfJoining) return 0;
    return currentYear - w.yearOfJoining;
}

double salaryAfterTax(const Worker& w) // TODO pass taxRate as param
{
    double taxRate = 0.33;
    return w.salary * (1 - taxRate);
}

int main() {
    int nubmerOfWorkers, currentYear;
    cout << "Enter the number of workers: ";
    cin >> nubmerOfWorkers;
    cout << "Enter the current year: ";
    cin >> currentYear;
    Worker workers[nubmerOfWorkers];
    for (int i = 0; i < nubmerOfWorkers; ++i)
    {
        cout << "Enter details for worker " << i + 1 << endl;
        workers[i].inputData();
    }
    for (int i = 0; i < nubmerOfWorkers; ++i)
    {
        cout << "\nWorker " << i + 1 << " details:" << endl;
        cout << "Surname and initials: " << workers[i].fullName << endl;
        cout << "Position: " << workers[i].getPositionString() << endl;
        cout << "Experience: " << experience(workers[i], currentYear) << " years" << endl;
        cout << "Salary after tax: " << salaryAfterTax(workers[i]) << endl;
    }
    return 0;
}