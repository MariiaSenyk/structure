#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

const int ROWS = 3;
const int COLS = 3;

struct Cell {
    int row, col, value;
};

pair<vector<vector<int>>, int> northWestCorner(
    vector<int>& supply,
    vector<int>& demand,
    const vector<vector<int>>& cost) {

    vector<vector<int>> plan(ROWS, vector<int>(COLS, 0));
    vector<int> s = supply;
    vector<int> d = demand;
    int totalCost = 0;

    int i = 0, j = 0;

    while (i < ROWS && j < COLS) {
        int amount = min(s[i], d[j]);
        plan[i][j] = amount;
        totalCost += amount * cost[i][j];
        s[i] -= amount;
        d[j] -= amount;

        if (s[i] == 0) i++;
        if (d[j] == 0) j++;
    }

    return {plan, totalCost};
}

pair<vector<vector<int>>, int> minimumCost(
    vector<int>& supply,
    vector<int>& demand,
    const vector<vector<int>>& cost) {

    vector<vector<int>> plan(ROWS, vector<int>(COLS, 0));
    vector<int> s = supply;
    vector<int> d = demand;
    int totalCost = 0;

    vector<Cell> cells;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cells.push_back({i, j, cost[i][j]});
        }
    }

    sort(cells.begin(), cells.end(), [](const Cell& a, const Cell& b) {
        return a.value < b.value;
    });

    for (const auto& cell : cells) {
        int i = cell.row;
        int j = cell.col;

        if (s[i] > 0 && d[j] > 0) {
            int amount = min(s[i], d[j]);
            plan[i][j] = amount;
            totalCost += amount * cost[i][j];
            s[i] -= amount;
            d[j] -= amount;
        }
    }

    return {plan, totalCost};
}

void printPlan(const vector<vector<int>>& plan, int totalCost, const string& method) {
    cout << "\n" << method << ":" << endl;
    cout << "Оптимальний план доставки:" << endl;
    cout << "         M1    M2    M3" << endl;
    cout << "       -----------------" << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << "C" << i + 1 << "    |";
        for (int j = 0; j < COLS; j++) {
            cout << "  " << setw(3) << plan[i][j] << "  ";
        }
        cout << "|" << endl;
    }
    cout << "       -----------------" << endl;
    cout << "Мінімальна загальна вартість доставки: " << totalCost << " грн" << endl;
}

int main() {
    cout << "-----------------------------------------" << endl;
    cout << "    Оптимізація логістики доставки" << endl;
    cout << "-----------------------------------------" << endl;

    vector<vector<int>> cost = {
        {8, 7, 2},
        {1, 4, 3},
        {5, 1, 6}
    };

    vector<int> supply = {1500, 1900, 1600};
    vector<int> demand = {1800, 1200, 2000};

    int totalSupply = 0, totalDemand = 0;
    for (int s : supply) totalSupply += s;
    for (int d : demand) totalDemand += d;

    cout << "\nВихідні дані:" << endl;
    cout << "Запаси складів: C1=" << supply[0] << ", C2=" << supply[1] << ", C3=" << supply[2]
         << " (Всього: " << totalSupply << ")" << endl;
    cout << "Потреби магазинів: M1=" << demand[0] << ", M2=" << demand[1] << ", M3=" << demand[2]
         << " (Всього: " << totalDemand << ")" << endl;

    if (totalSupply != totalDemand) {
        cout << "\nУвага! Задача незбалансована!" << endl;
        cout << "Загальні запаси (" << totalSupply << ") != Загальні потреби (" << totalDemand << ")" << endl;

        if (totalSupply > totalDemand) {
            cout << "Додаємо фіктивного споживача з потребою " << totalSupply - totalDemand << endl;
            demand.push_back(totalSupply - totalDemand);
            for (int i = 0; i < ROWS; i++) {
                cost[i].push_back(0);
            }
        } else {
            cout << "Додаємо фіктивного постачальника з запасом " << totalDemand - totalSupply << endl;
            supply.push_back(totalDemand - totalSupply);
            cost.push_back(vector<int>(COLS, 0));
        }
    }

    cout << "\nМатриця витрат (вартість доставки одиниці товару):" << endl;
    cout << "         M1    M2    M3" << endl;
    cout << "       -----------------" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "C" << i + 1 << "    |";
        for (int j = 0; j < COLS; j++) {
            cout << "  " << setw(3) << cost[i][j] << "  ";
        }
        cout << "|" << endl;
    }
    cout << "       -----------------" << endl << endl;

    auto result1 = northWestCorner(supply, demand, cost);
    printPlan(result1.first, result1.second, "Алгоритм північно-західного кута");

    auto result2 = minimumCost(supply, demand, cost);
    printPlan(result2.first, result2.second, "Алгоритм мінімальної вартості");

    cout << "\n-----------------------------------------" << endl;
    cout << "Порівння результатів:" << endl;
    cout << "Алгоритм північно-західного кута: " << result1.second << " грн" << endl;
    cout << "Алгоритм мінімальної вартості: " << result2.second << " грн" << endl;

    if (result1.second < result2.second) {
        cout << "\nКращий результат дає алгоритм північно-західного кута" << endl;
    } else if (result2.second < result1.second) {
        cout << "\nКращий результат дає алгоритм мінімальної вартості" << endl;
    } else {
        cout << "\nОбидва алгоритми дають однаковий результат" << endl;
    }

    return 0;
}