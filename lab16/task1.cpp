#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int grades[3];
    double avgGrade;
};

void calcAverage(Student* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i].avgGrade = (arr[i].grades[0] + arr[i].grades[1] + arr[i].grades[2]) / 3.0;
}

void printStudent(const Student& s, int idx) {
    cout << "  #" << idx + 1 << " " << s.name << " | avg: " << s.avgGrade << "\n";
}

void linearSearchMax(Student* arr, int n) {
    double maxAvg = arr[0].avgGrade;
    for (int i = 1; i < n; i++)
        if (arr[i].avgGrade > maxAvg)
            maxAvg = arr[i].avgGrade;

    int count = 0;
    cout << "Max avg grade: " << maxAvg << "\n";
    cout << "Students with max avg grade:\n";
    for (int i = 0; i < n; i++) {
        if (arr[i].avgGrade == maxAvg) {
            printStudent(arr[i], i);
            count++;
        }
    }
    cout << "Count: " << count << "\n";
}

void sortByAvg(Student* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].avgGrade > arr[j + 1].avgGrade) {
                Student tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void binarySearch(Student* arr, int n, double target) {
    int left = 0, right = n - 1;
    int mid = -1;
    bool found = false;

    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid].avgGrade == target) {
            found = true;
            break;
        } else if (arr[mid].avgGrade < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (!found) {
        cout << "No student found with avg grade " << target << "\n";
        return;
    }

    int start = mid;
    while (start > 0 && arr[start - 1].avgGrade == target)
        start--;

    cout << "Students with avg grade " << target << ":\n";
    for (int i = start; i < n && arr[i].avgGrade == target; i++)
        printStudent(arr[i], i);
}

int main() {
    const int N = 6;
    Student students[N] = {
        {"Alice",   {90, 85, 92}, 0},
        {"Bob",     {70, 75, 80}, 0},
        {"Carol",   {90, 85, 92}, 0},
        {"David",   {60, 65, 70}, 0},
        {"Eve",     {88, 91, 87}, 0},
        {"Frank",   {75, 80, 85}, 0},
    };

    calcAverage(students, N);

    cout << "All students:\n";
    for (int i = 0; i < N; i++)
        printStudent(students[i], i);

    cout << "\n--- Linear search ---\n";
    linearSearchMax(students, N);

    sortByAvg(students, N);

    cout << "\nSorted by avg grade:\n";
    for (int i = 0; i < N; i++)
        printStudent(students[i], i);

    cout << "\n--- Binary search ---\n";
    cout << "Enter avg grade to search: ";
    double target;
    cin >> target;
    binarySearch(students, N, target);

    return 0;
}