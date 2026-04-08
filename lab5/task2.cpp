#include <iostream>
#include <string>

using namespace std;

struct City {
    string name;
    int distance;
    City *next;
};

void addCity(City *&head, const string &name, int distance) {
    City *newCity = new City;
    newCity->name = name;
    newCity->distance = distance;
    newCity->next = head;
    head = newCity;
}

void printFarthestCities(City *head) {
    City *city1 = nullptr, *city2 = nullptr;
    int maxDistance1 = -1, maxDistance2 = -1;

    for (City *temp = head; temp != nullptr; temp = temp->next) {
        if (temp->distance > maxDistance1) {
            maxDistance2 = maxDistance1;
            city2 = city1;
            maxDistance1 = temp->distance;
            city1 = temp;
        } else if (temp->distance > maxDistance2) {
            maxDistance2 = temp->distance;
            city2 = temp;
        }
    }

    cout << "Most distant cities from Kyiv:" << endl;
    if (city1 != nullptr)
        cout << city1->name << " (" << city1->distance << " km)" << endl;
    if (city2 != nullptr)
        cout << city2->name << " (" << city2->distance << " km)" << endl;
}

void deleteList(City *head) {
    while (head != nullptr) {
        City *temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    City *head = nullptr;
    int n;

    cout << "Enter the number of cities: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string name;
        int distance;

        cout << "Enter the name of city " << i + 1 << ": ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter the distance to Kyiv from " << name << ": ";
        cin >> distance;

        addCity(head, name, distance);
    }

    addCity(head, "Warsaw", 800);

    printFarthestCities(head);

    deleteList(head);
    return 0;
}
