#include <iostream>
#include <string>
using namespace std;

struct TV {
    string brand;
    int screenSize;
    double price;
};

void printTV(const TV& t) {
    cout << "  " << t.brand << " | " << t.screenSize << "\" | " << t.price << " uah\n";
}

void insertionSortBySize(TV* arr, int n) {
    for (int i = 1; i < n; i++) {
        TV key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].screenSize > key.screenSize) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void gnomeSortByPriceDesc(TV* arr, int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i].price <= arr[i - 1].price)
            i++;
        else {
            TV tmp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = tmp;
            i--;
        }
    }
}

void sortTVs(TV* arr, int n) {
    insertionSortBySize(arr, n);

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && arr[j].screenSize == arr[i].screenSize)
            j++;
        gnomeSortByPriceDesc(arr + i, j - i);
        i = j;
    }
}

int main() {
    const int N = 9;
    TV tvs[N] = {
        {"Samsung", 60, 32000.0},
        {"LG",      45, 18000.0},
        {"Sony",    32,  9500.0},
        {"Philips", 60, 28000.0},
        {"Samsung", 32, 11000.0},
        {"LG",      60, 35000.0},
        {"Sony",    45, 21000.0},
        {"Philips", 32,  8000.0},
        {"Samsung", 45, 17000.0},
    };

    cout << "Before sorting:\n";
    for (int i = 0; i < N; i++)
        printTV(tvs[i]);

    sortTVs(tvs, N);

    cout << "\nAfter sorting (by screen size asc, price desc within group):\n";
    for (int i = 0; i < N; i++)
        printTV(tvs[i]);

    return 0;
}