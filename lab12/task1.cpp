#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string genre;
    double price;
    int popularity;
    int arrivalYear;
};

void displayInventory(const vector<Book> &inventory) {
    cout << "\n" << left << setw(5) << "ID" << setw(20) << "Title" << setw(15) << "Author"
            << setw(12) << "Genre" << setw(8) << "Price" << setw(10) << "Popular" << setw(6) << "Year" << endl;
    cout << string(75, '-') << endl;
    for (const auto &b: inventory) {
        cout << left << setw(5) << b.id << setw(20) << b.title << setw(15) << b.author
                << setw(12) << b.genre << setw(8) << b.price << setw(10) << b.popularity
                << setw(6) << b.arrivalYear << endl;
    }
}

int main() {
    vector<Book> inventory = {
        {101, "The Great Gatsby", "F.S. Fitzgerald", "Classic", 15.99, 85, 2022},
        {102, "Project Hail Mary", "Andy Weir", "Sci-Fi", 24.50, 98, 2023},
        {103, "The Hobbit", "J.R.R. Tolkien", "Fantasy", 19.99, 92, 2021},
        {104, "Steve Jobs", "Walter Isaacson", "Biography", 30.00, 75, 2020}
    };

    int choice;
    do {
        cout << "\n--- BOOKSTORE MANAGEMENT SYSTEM ---\n";
        cout << "1. Display All Books\n2. Add New Book\n3. Remove Sold Out (by ID)\n";
        cout << "4. Sort by Price\n5. Sort by Popularity\n6. Sort by Arrival Date\n";
        cout << "7. Filter by Genre\n8. Filter by Price Range\n0. Exit\nSelection: ";
        cin >> choice;

        if (choice == 1) {
            displayInventory(inventory);
        } else if (choice == 2) {
            Book b;
            cout << "Enter ID, Title, Author, Genre, Price, Popularity, Year: ";
            cin >> b.id;
            cin.ignore();
            getline(cin, b.title);
            getline(cin, b.author);
            getline(cin, b.genre);
            cin >> b.price >> b.popularity >> b.arrivalYear;
            inventory.push_back(b);
        } else if (choice == 3) {
            int id;
            cout << "Enter ID to remove: ";
            cin >> id;
            inventory.erase(remove_if(inventory.begin(), inventory.end(), [id](const Book &b) {
                return b.id == id;
            }), inventory.end());
        } else if (choice == 4) {
            sort(inventory.begin(), inventory.end(), [](const Book &a, const Book &b) {
                return a.price < b.price;
            });
        } else if (choice == 5) {
            sort(inventory.begin(), inventory.end(), [](const Book &a, const Book &b) {
                return a.popularity > b.popularity;
            });
        } else if (choice == 6) {
            sort(inventory.begin(), inventory.end(), [](const Book &a, const Book &b) {
                return a.arrivalYear > b.arrivalYear;
            });
        } else if (choice == 7) {
            string g;
            cout << "Enter genre: ";
            cin >> g;
            for (const auto &b: inventory) if (b.genre == g) cout << b.title << endl;
        } else if (choice == 8) {
            double minP, maxP;
            cout << "Enter min and max price: ";
            cin >> minP >> maxP;
            for (const auto &b: inventory) {
                if (b.price >= minP && b.price <= maxP) cout << b.title << " - $" << b.price << endl;
            }
        }
    } while (choice != 0);

    return 0;
}
