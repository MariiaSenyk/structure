#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

void gnomeSort(int* arr, int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1])
            i++;
        else {
            swap(arr[i], arr[i - 1]);
            i--;
        }
    }
}

void fillRandom(int* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

double measureTime(void (*sortFunc)(int*, int), int* original, int n) {
    int* arr = new int[n];
    memcpy(arr, original, n * sizeof(int));
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();
    delete[] arr;
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(42);

    int sizes[] = {1000, 10000, 100000};
    const char* names[] = {
        "Bubble sort   ",
        "Insertion sort",
        "Selection sort",
        "Gnome sort    "
    };
    void (*sorts[])(int*, int) = {bubbleSort, insertionSort, selectionSort, gnomeSort};

    cout << "Algorithm      | n=1000   | n=10000  | n=100000\n";
    cout << "---------------|----------|----------|----------\n";

    for (int s = 0; s < 4; s++) {
        cout << names[s] << " | ";
        for (int k = 0; k < 3; k++) {
            int n = sizes[k];
            int* arr = new int[n];
            fillRandom(arr, n);
            double t = measureTime(sorts[s], arr, n);
            delete[] arr;
            cout << t << " s  | ";
        }
        cout << "\n";
    }

    return 0;
}