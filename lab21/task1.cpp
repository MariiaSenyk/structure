#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

struct Position {
    string name;
    int A;
    int B;
    int count;
    double coefficient;
    double salary;
    double totalSalary;
};

int utf8len(const string& s) {
    int len = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) ++len;
    return len;
}

void printLeft(const string& s, int width) {
    int byteLen = s.size();
    int charLen = utf8len(s);
    int extra = byteLen - charLen;
    cout << left << setw(width + extra) << s;
}

int main() {
    cout << "-----------------------------------------" << endl;
    cout << " Розрахунок зарплат працівників лікарні " << endl;
    cout << "-----------------------------------------" << endl;

    vector<Position> positions = {
        {"Санітарка",        1, 1, 7,  0, 0, 0},
        {"Медсестра",        6, 5, 10, 0, 0, 0},
        {"Лікар",            8, 5, 10, 0, 0, 0},
        {"Зав. аптекою",     9, 5, 1,  0, 0, 0},
        {"Зав. відділенням", 2, 1, 3,  0, 0, 0},
        {"Головний лікар",   12, 5, 1, 0, 0, 0},
        {"Зав. господарства",13, 5, 1, 0, 0, 0},
        {"Зав. лікарнею",    3, 1, 1,  0, 0, 0}
    };

    const double TOTAL_BUDGET = 380000.0;

    for (auto& p : positions)
        p.coefficient = (double)p.A / p.B;

    double bestSanitarySalary = 0, bestTotalSalary = 0, minDiff = TOTAL_BUDGET;

    for (double s = 5000; s <= 8000; s += 10) {
        double total = 0;
        for (auto& p : positions)
            total += s * p.coefficient * p.count;
        double diff = TOTAL_BUDGET - total;
        if (diff >= 0 && diff < minDiff) {
            minDiff = diff;
            bestSanitarySalary = s;
            bestTotalSalary = total;
        }
    }

    cout << fixed << setprecision(2);

    for (auto& p : positions) {
        p.salary = bestSanitarySalary * p.coefficient;
        p.totalSalary = p.salary * p.count;
    }

    cout << "\nОптимальний розрахунок:" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Базова зарплата санітарки: " << bestSanitarySalary << " грн" << endl;
    cout << "Загальний фонд зарплати:   " << bestTotalSalary   << " грн" << endl;
    cout << "Невикористано:             " << TOTAL_BUDGET - bestTotalSalary << " грн" << endl;
    cout << "-----------------------------------------" << endl << endl;

    printLeft("Посада", 22);
    cout << right << setw(12) << "Коефіцієнт"
         << right << setw(10) << "      Кількість"
         << right << setw(14) << "      Зарплата"
         << right << setw(18) << "      Загальна зарплата" << endl;
    cout << string(76, '-') << endl;

    for (const auto& p : positions) {
        printLeft(p.name, 22);
        cout << right << setw(12) << fixed << setprecision(2) << p.coefficient
             << right << setw(10) << p.count
             << right << setw(14) << p.salary
             << right << setw(18) << p.totalSalary << endl;
    }

    cout << string(76, '-') << endl;
    printLeft("Всього:", 22);
    cout << right << setw(12) << ""
         << right << setw(10) << ""
         << right << setw(14) << ""
         << right << setw(18) << bestTotalSalary << endl;

    return 0;
}