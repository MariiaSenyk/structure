#include <iostream>
#include <string>

using namespace std;

struct Node {
    string date;
    float temperature;
    Node *next;
    Node *prev;

    Node(string d, float temp) : date(d), temperature(temp), next(nullptr), prev(nullptr) {
    }
};

class DoublyLinkedList {
private:
    Node *head;
    Node *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {
    }

    void append(string date, float temperature) {
        Node *newNode = new Node(date, temperature);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void merge(DoublyLinkedList &otherList) {
        if (!head) {
            head = otherList.head;
            tail = otherList.tail;
        } else {
            tail->next = otherList.head;
            if (otherList.head) {
                otherList.head->prev = tail;
            }
            tail = otherList.tail;
        }
    }

    void findMaxMin(float &maxTemp, float &minTemp) {
        if (!head) return;

        maxTemp = minTemp = head->temperature;
        Node *current = head->next;
        while (current) {
            if (current->temperature > maxTemp) maxTemp = current->temperature;
            if (current->temperature < minTemp) minTemp = current->temperature;
            current = current->next;
        }
    }

    void freeMemory() {
        Node *current = head;
        while (current) {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    void printList() {
        Node *current = head;
        while (current) {
            cout << current->date << " - " << current->temperature << "°C" << endl;
            current = current->next;
        }
    }

    ~DoublyLinkedList() {
        freeMemory();
    }
};

int main() {
    DoublyLinkedList list1;
    list1.append("2026-01-01", 5);
    list1.append("2026-01-02", 7);
    list1.append("2026-01-03", 3);

    DoublyLinkedList list2;
    list2.append("2026-02-01", 10);
    list2.append("2026-02-02", 2);
    list2.append("2026-02-03", 4);

    list1.merge(list2);

    cout << "Combined list of temperatures: " << endl;
    list1.printList();

    float maxTemp, minTemp;
    list1.findMaxMin(maxTemp, minTemp);
    cout << "\nMax temperature " << maxTemp << "°C" << endl;
    cout << "Min temperature " << minTemp << "°C" << endl;

    list1.freeMemory();

    return 0;
}
