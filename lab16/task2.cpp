#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    double proteins;
    double fats;
    double carbs;
    double calories;
};

void calcCalories(Product* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i].calories = 4 * arr[i].proteins + 9 * arr[i].fats + 4 * arr[i].carbs;
}

void printProduct(const Product& p, int idx) {
    cout << "  #" << idx + 1 << " " << p.name << " | calories: " << p.calories << " kcal\n";
}

void linearSearchMax(Product* arr, int n) {
    double maxCal = arr[0].calories;
    for (int i = 1; i < n; i++)
        if (arr[i].calories > maxCal)
            maxCal = arr[i].calories;

    int count = 0;
    cout << "Max calories: " << maxCal << "\n";
    cout << "Products with max calories:\n";
    for (int i = 0; i < n; i++) {
        if (arr[i].calories == maxCal) {
            printProduct(arr[i], i);
            count++;
        }
    }
    cout << "Count: " << count << "\n";
}

void searchInRange(Product* arr, int n, double A, double B) {
    bool found = false;
    cout << "Products with calories in [" << A << "; " << B << "]:\n";
    for (int i = 0; i < n; i++) {
        if (arr[i].calories >= A && arr[i].calories <= B) {
            printProduct(arr[i], i);
            found = true;
        }
    }
    if (!found)
        cout << "No products found in range [" << A << "; " << B << "]\n";
}

int main() {
    const int N = 6;
    Product products[N] = {
        {"Chicken breast", 31.0,  3.6,  0.0,  0},
        {"Butter",          0.5, 82.5,  0.8,  0},
        {"Rice",            6.7,  0.7, 78.9,  0},
        {"Egg",            12.7, 11.5,  0.7,  0},
        {"Almonds",        21.2, 49.9, 21.7,  0},
        {"Apple",           0.4,  0.4, 14.0,  0},
    };

    calcCalories(products, N);

    cout << "All products:\n";
    for (int i = 0; i < N; i++)
        printProduct(products[i], i);

    cout << "\n--- Linear search (max calories) ---\n";
    linearSearchMax(products, N);

    cout << "\n--- Range search ---\n";
    double A, B;
    cout << "Enter range [A B]: ";
    cin >> A >> B;
    searchInRange(products, N, A, B);

    return 0;
}