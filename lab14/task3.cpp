#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    multimap<string, string> phoneBook;
    int choice;
    string name, phone;

    do {
        cout <<"\n1. Add contact\n2. Show numbers\n3. Delete number\n4. Delete all numbers\n5. Show all\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone: ";
                cin >> phone;
                phoneBook.insert(make_pair(name, phone));
                cout << "Added\n";
                break;

            case 2: {
                cout << "Enter name: ";
                cin >> name;
                pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range;
                range = phoneBook.equal_range(name);
                if (range.first == range.second) {
                    cout << "No entries\n";
                } else {
                    cout << "Numbers: ";
                    for (multimap<string, string>::iterator it = range.first; it != range.second; ++it) {
                        cout << it->second << " ";
                    }
                    cout << endl;
                }
                break;
            }

            case 3: {
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone to delete: ";
                cin >> phone;
                pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range2;
                range2 = phoneBook.equal_range(name);
                bool deleted = false;
                for (multimap<string, string>::iterator it = range2.first; it != range2.second; ++it) {
                    if (it->second == phone) {
                        phoneBook.erase(it);
                        deleted = true;
                        cout << "Deleted\n";
                        break;
                    }
                }
                if (!deleted) cout << "Not found\n";
                break;
            }

            case 4:
                cout << "Enter name: ";
                cin >> name;
                cout << "Deleted " << phoneBook.erase(name) << " entries\n";
                break;

            case 5:
                cout << "\nPhone book:\n";
                for (multimap<string, string>::iterator it = phoneBook.begin(); it != phoneBook.end(); ++it) {
                    cout << it->first << ": " << it->second << endl;
                }
                break;
        }
    } while (choice != 0);

    return 0;
}
