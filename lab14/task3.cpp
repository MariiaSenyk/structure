#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
    deque<string> queue;
    int choice;
    string request;

    do {
        cout <<
                "\n1. Add normal (back)\n2. Add urgent (front)\n3. Process\n4. Show queue\n5. Show size\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter request: ";
                cin.ignore();
                getline(cin, request);
                queue.push_back(request);
                cout << "Added to back\n";
                break;

            case 2:
                cout << "Enter urgent request: ";
                cin.ignore();
                getline(cin, request);
                queue.push_front(request);
                cout << "Added to front\n";
                break;

            case 3:
                if (queue.empty()) {
                    cout << "Queue empty\n";
                } else {
                    cout << "Processing: " << queue.front() << endl;
                    queue.pop_front();
                }
                break;

            case 4:
                if (queue.empty()) {
                    cout << "Queue empty\n";
                } else {
                    cout << "Queue: ";
                    for (int i = 0; i < queue.size(); i++) {
                        cout << "[" << queue[i] << "] ";
                    }
                    cout << endl;
                }
                break;

            case 5:
                cout << "Size: " << queue.size() << endl;
                break;

            case 0:
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}
