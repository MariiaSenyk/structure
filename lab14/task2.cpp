#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    multimap<string, string> phoneBook;
    int choice;
    string name, phone;

    do {
        cout <<
                "\n1. Add contact\n2. Show numbers\n3. Delete number\n4. Delete all numbers\n5. Show all\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone: ";
                cin >> phone;
                phoneBook.insert({name, phone});
                cout << "Added\n";
                break;

            case 2:
                cout << "Enter name: ";
                cin >> name;
                auto range = phoneBook.equal_range(name);
                if (range.first == range.second) {
                    cout << "No entries\n";
                } else {
                    cout << "Numbers: ";
                    for (auto it = range.first; it != range.second; ++it) {
                        cout << it->second << " ";
                    }
                    cout << endl;
                }
                break;

            case 3:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone to delete: ";
                cin >> phone;
                range = phoneBook.equal_range(name);
                bool deleted = false;
                for (auto it = range.first; it != range.second; ++it) {
                    if (it->second == phone) {
                        phoneBook.erase(it);
                        deleted = true;
                        cout << "Deleted\n";
                        break;
                    }
                }
                if (!deleted) cout << "Not found\n";
                break;

            case 4:
                cout << "Enter name: ";
                cin >> name;
                cout << "Deleted " << phoneBook.erase(name) << " entries\n";
                break;

            case 5:
                cout << "\nPhone book:\n";
                for (const auto &contact: phoneBook) {
                    cout << contact.first << ": " << contact.second << endl;
                }
                break;
        }
    } while (choice != 0);

    return 0;
}
