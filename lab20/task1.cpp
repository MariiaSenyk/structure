#include <iostream>
#include <algorithm>
using namespace std;

struct Product {
    string name;
    double volumePerKg;
    double caloriesPerKg;
    double mass;
};

int main() {
    Product products[4] = {
        {"М'ясо", 1.5, 1500, 0},
        {"Мука", 2.0, 5000, 0},
        {"Молоко", 1.0, 5000, 0},
        {"Цукор", 1.0, 4000, 0}
    };

    double maxVolume = 45.0;
    double maxMass = 35.0;

    double x = 1;
    double ratioMeat = 16, ratioFlour = 8, ratioMilk = 8, ratioSugar = 1;
    double totalRatio = ratioMeat + ratioFlour + ratioMilk + ratioSugar;


    double maxMassByVolume = maxVolume / (
                                 ratioMeat / totalRatio * products[0].volumePerKg +
                                 ratioFlour / totalRatio * products[1].volumePerKg +
                                 ratioMilk / totalRatio * products[2].volumePerKg +
                                 ratioSugar / totalRatio * products[3].volumePerKg
                             );

    double totalMass = min(maxMass, maxMassByVolume);

    products[0].mass = ratioMeat / totalRatio * totalMass;
    products[1].mass = ratioFlour / totalRatio * totalMass;
    products[2].mass = ratioMilk / totalRatio * totalMass;
    products[3].mass = ratioSugar / totalRatio * totalMass;

    if (products[0].mass >= 2 * products[1].mass &&
        products[1].mass >= products[2].mass &&
        products[2].mass >= 8 * products[3].mass) {
        cout << "Обмеження виконуються!" << endl;
    }

    double totalVolume = 0, totalCalories = 0;

    cout << "\nПродукт\t\tМаса(кг)\tОб'єм(дм³)\tКалорійність(ккал)" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < 4; i++) {
        double volume = products[i].mass * products[i].volumePerKg;
        double calories = products[i].mass * products[i].caloriesPerKg;
        totalVolume += volume;
        totalCalories += calories;

        cout << products[i].name << "\t\t"
                << products[i].mass << "\t\t"
                << volume << "\t\t"
                << calories << endl;
    }

    cout << "--------------------------------------------------------" << endl;
    cout << "Разом:\t\t" << totalMass << " кг\t\t"
            << totalVolume << " дм³\t\t"
            << totalCalories << " ккал" << endl;

    return 0;
}
