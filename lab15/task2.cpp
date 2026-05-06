#include <iostream>
#include <string>
using namespace std;

struct Time {
    int hours;
    int minutes;
};

struct Train {
    int number;
    string destination;
    double distance;
    Time departure;
    Time arrival;
    int travelMinutes;
};

void printTrain(const Train& t) {
    cout << "  #" << t.number
         << " | " << t.destination
         << " | " << t.travelMinutes << " min\n";
}

void selectionSortDesc(Train* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].travelMinutes > arr[maxIdx].travelMinutes)
                maxIdx = j;
        Train tmp = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx] = tmp;
    }
}

int main() {
    const int N = 5;
    Train trains[N] = {
        {101, "Kyiv",       500.0, {8,  0},  {14, 30}, 390},
        {202, "Lviv",       340.0, {9,  15}, {13, 45}, 270},
        {303, "Odesa",      480.0, {7,  0},  {15,  0}, 480},
        {404, "Kharkiv",    410.0, {10, 30}, {16,  0}, 330},
        {505, "Dnipro",     550.0, {6,  0},  {14,  0}, 480},
    };

    cout << "All trains:\n";
    for (int i = 0; i < N; i++)
        printTrain(trains[i]);

    int maxIdx = 0;
    for (int i = 1; i < N; i++)
        if (trains[i].travelMinutes > trains[maxIdx].travelMinutes)
            maxIdx = i;

    cout << "\na) Longest travel time:\n";
    printTrain(trains[maxIdx]);

    selectionSortDesc(trains, N);

    cout << "\nb) Sorted by travel time (descending):\n";
    for (int i = 0; i < N; i++)
        printTrain(trains[i]);

    cout << "\nTrain with max travel time:\n";
    printTrain(trains[0]);

    return 0;
}