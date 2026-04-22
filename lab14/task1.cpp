#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

int main() {
    array<int, 10> grades;

    cout << "Enter 10 grades: ";
    for (int i = 0; i < 10; i++) {
        cin >> grades[i];
    }

    double sum = accumulate(grades.begin(), grades.end(), 0);
    double average = sum / 10;
    cout << "Average grade: " << fixed << setprecision(2) << average << endl;

    int max_grade = *max_element(grades.begin(), grades.end());
    int min_grade = *min_element(grades.begin(), grades.end());
    cout << "Maximum grade: " << max_grade << endl;
    cout << "Minimum grade: " << min_grade << endl;

    int above_average = count_if(grades.begin(), grades.end(),
                                   [average](int g) { return g > average; });
    cout << "Grades above average: " << above_average << endl;

    array<int, 10> ascending = grades;
    sort(ascending.begin(), ascending.end());
    cout << "Ascending order: ";
    for (int g: ascending) cout << g << " ";
    cout << endl;
    array<int, 10> descending = grades;
    sort(descending.begin(), descending.end(), ::greater<int>());
    cout << "Descending order: ";
    for (int g: descending) cout << g << " ";
    cout << endl;

    return 0;
}
