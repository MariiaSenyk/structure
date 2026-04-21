#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

class PhoneBook {
private:
    map<string, string> book;

public:
    void add(const string &name, const string &phone) {
        book[name] = phone;
        cout << "Saved: " << name << " -> " << phone << "\n";
    }

    void find(const string &name) const {
        auto it = book.find(name);
        if (it != book.end()) {
            cout << "Found: " << it->first << " -> " << it->second << "\n";
        } else {
            cout << "Contact \"" << name << "\" not found.\n";
        }
    }

    void remove(const string &name) {
        if (book.erase(name)) {
            cout << "Contact \"" << name << "\" deleted.\n";
        } else {
            cout << "Contact \"" << name << "\" not found.\n";
        }
    }

    void printAll() const {
        if (book.empty()) {
            cout << "Phone book is empty.\n";
            return;
        }
        cout << "\n--- Phone Book ---\n";
        for (const auto &[name, phone]: book) {
            cout << name << ": " << phone << "\n";
        }
    }
};

void showMenu() {
    cout << "\n1. Add contact\n"
            << "2. Find contact\n"
            << "3. Delete contact\n"
            << "4. Show all contacts\n"
            << "0. Exit\n"
            << "Your choice: ";
}

int main() {
    PhoneBook pb;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string name, phone;
                cout << "Name: ";
                getline(cin, name);
                cout << "Phone: ";
                getline(cin, phone);
                pb.add(name, phone);
                break;
            }
            case 2: {
                string name;
                cout << "Name to search: ";
                getline(cin, name);
                pb.find(name);
                break;
            }
            case 3: {
                string name;
                cout << "Name to delete: ";
                getline(cin, name);
                pb.remove(name);
                break;
            }
            case 4:
                pb.printAll();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
