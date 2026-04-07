#include <iostream>
#include <string>

using namespace std;

struct Car {
    string name;
    int year;
    double price;
    Car *next;
};

void addCar(Car *&head, const string &name, int year, double price) {
    Car *newCar = new Car;
    newCar->name = name;
    newCar->year = year;
    newCar->price = price;
    newCar->next = head;
    head = newCar;
}

void printOldCheapCars(Car *head) {
    int currentYear = 2026;
    bool found = false;
    cout << "\nList of cars older than 10 years and costing less than 5000 USD:\n";
    for (Car *temp = head; temp != nullptr; temp = temp->next) {
        if (currentYear - temp->year > 10 && temp->price < 5000) {
            cout << "Name: " << temp->name << " | Year: " << temp->year << " | Price: " << temp->price << " USD" <<
                    endl;
            found = true;
        }
    }
    if (!found) {
        cout << "\nNo cars found that match the criteria.\n";
    }
}

void deleteList(Car *head) {
    while (head != nullptr) {
        Car *temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Car *head = nullptr;
    int n;

    cout << "Enter the number of cars: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string name;
        int year;
        double price;

        cout << "\nEnter the name of car #" << i + 1 << ": ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter the year of manufacture: ";
        cin >> year;

        cout << "Enter the price of the car (in USD): ";
        cin >> price;

        addCar(head, name, year, price);
    }

    printOldCheapCars(head);

    deleteList(head);
    return 0;
}
