#include <iostream>
#include <array>

using namespace std;

int main() {
    array<int, 10> grades;

    cout << "Enter 10 grades: ";
    for (int i = 0; i < 10; i++) {
        cin >> grades[i];
    }

    double sum = 0;
    int max_grade = grades[0];
    int min_grade = grades[0];

    for (int i = 0; i < 10; i++) {
        sum += grades[i];
        if (grades[i] > max_grade) max_grade = grades[i];
        if (grades[i] < min_grade) min_grade = grades[i];
    }

    double average = sum / 10;
    cout << "Average grade: " << average << endl;
    cout << "Maximum grade: " << max_grade << endl;
    cout << "Minimum grade: " << min_grade << endl;

    int above_average = 0;
    for (int i = 0; i < 10; i++) {
        if (grades[i] > average) above_average++;
    }
    cout << "Grades above average: " << above_average << endl;

    array<int, 10> ascending = grades;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (ascending[i] > ascending[j]) {
                int temp = ascending[i];
                ascending[i] = ascending[j];
                ascending[j] = temp;
            }
        }
    }

    cout << "Ascending order: ";
    for (int i = 0; i < 10; i++) {
        cout << ascending[i] << " ";
    }
    cout << endl;

    array<int, 10> descending = grades;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (descending[i] < descending[j]) {
                int temp = descending[i];
                descending[i] = descending[j];
                descending[j] = temp;
            }
        }
    }

    cout << "Descending order: ";
    for (int i = 0; i < 10; i++) {
        cout << descending[i] << " ";
    }
    cout << endl;

    return 0;
}