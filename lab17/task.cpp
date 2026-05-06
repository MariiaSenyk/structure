#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    double price;
    double nutrients[3];
    float calories;
};

float calculateCalories(double nutrients[3]) {
    return 4.0f * nutrients[0] + 9.0f * nutrients[1] + 4.0f * nutrients[2];
}

void selectionSortByCaloriesDesc(Product arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].calories > arr[maxIdx].calories) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            swap(arr[i], arr[maxIdx]);
        }
    }
}

void gnomeSortByPriceAsc(Product arr[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i].price >= arr[i - 1].price) {
            i++;
        } else {
            swap(arr[i], arr[i - 1]);
            i--;
        }
    }
}

void linearSearchByPrice(Product arr[], int n, double target) {
    bool found = false;
    cout << "\nProduct search results with price " << target << ":\n";
    for (int i = 0; i < n; i++) {
        if (arr[i].price == target) {
            cout << " - " << arr[i].name
                 << ", price = " << arr[i].price
                 << ", calories = " << arr[i].calories << " kcal\n";
            found = true;
        }
    }
    if (!found) {
        cerr << "No products with price " << target << " found.\n";
    }
}

void printProducts(Product arr[], int n, const string& title) {
    cout << "\n" << title << ":\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i].name
             << " | price: " << arr[i].price
             << " | calories: " << arr[i].calories
             << " kcal | (proteins/fats/carbs): "
             << arr[i].nutrients[0] << "/"
             << arr[i].nutrients[1] << "/"
             << arr[i].nutrients[2] << endl;
    }
}

int main() {
    const int N = 6;
    Product products[N] = {
        {"Chicken breast", 31.0,  {23.0, 1.5, 0.0}, 0},
        {"Butter",         120.0,  {0.8, 82.5, 0.8}, 0},
        {"Rice",           45.0,  {7.0, 0.7, 78.9}, 0},
        {"Egg",           15.0,  {12.7, 11.5, 0.7}, 0},
        {"Almonds",       250.0,  {21.2, 49.9, 21.7}, 0},
        {"Apple",          15.0,  {0.4, 0.4, 14.0}, 0}
    };

    for (int i = 0; i < N; i++) {
        products[i].calories = calculateCalories(products[i].nutrients);
    }

    Product copyForPrice[N];
    for (int i = 0; i < N; i++) {
        copyForPrice[i] = products[i];
    }

    selectionSortByCaloriesDesc(products, N);
    printProducts(products, N, "Sorted by calories (descending) - Selection Sort");

    gnomeSortByPriceAsc(copyForPrice, N);
    printProducts(copyForPrice, N, "Sorted by price (ascending) - Gnome Sort");

    double searchPrice;
    cout << "\nEnter price to search: ";
    cin >> searchPrice;
    linearSearchByPrice(products, N, searchPrice);

    return 0;
}