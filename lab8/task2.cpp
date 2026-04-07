#include <iostream>
#include <string>

using namespace std;

struct Node {
    string courseName;
    int hours;
    int listeners;
    Node *next;
    Node *prev;

    Node(string name, int h, int l) : courseName(name), hours(h), listeners(l), next(nullptr), prev(nullptr) {
    }
};

class DoublyLinkedList {
private:
    Node *head;
    Node *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {
    }

    void append(string courseName, int hours, int listeners) {
        Node *newNode = new Node(courseName, hours, listeners);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() {
        Node *current = head;
        while (current) {
            cout << current->courseName << " - " << current->hours << " hours - " << current->listeners << " listeners"
                    << endl;
            current = current->next;
        }
    }

    void displayReverse() {
        Node *current = tail;
        while (current) {
            cout << current->courseName << " - " << current->hours << " hours - " << current->listeners << " listeners"
                    << endl;
            current = current->prev;
        }
    }

    double calculateAverageListeners() {
        if (!head) return 0;
        int totalListeners = 0;
        int count = 0;
        Node *current = head;
        while (current) {
            totalListeners += current->listeners;
            count++;
            current = current->next;
        }
        return static_cast<double>(totalListeners) / count;
    }

    void splitByListeners(double averageListeners, DoublyLinkedList &higherList, DoublyLinkedList &lowerList) {
        Node *current = head;
        while (current) {
            if (current->listeners > averageListeners) {
                higherList.append(current->courseName, current->hours, current->listeners);
            } else {
                lowerList.append(current->courseName, current->hours, current->listeners);
            }
            current = current->next;
        }
    }

    void clear() {
        Node *current = head;
        while (current) {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    ~DoublyLinkedList() {
        clear();
    }
};

int main() {
    DoublyLinkedList courseList;
    courseList.append("Course 1", 40, 30);
    courseList.append("Course 2", 50, 25);
    courseList.append("Course 3", 60, 40);
    courseList.append("Course 4", 45, 35);
    courseList.append("Course 5", 55, 20);

    double averageListeners = courseList.calculateAverageListeners();
    cout << "Average number of listeners: " << averageListeners << endl;

    DoublyLinkedList higherList, lowerList;
    courseList.splitByListeners(averageListeners, higherList, lowerList);

    cout << "\nCourses with listeners above average:" << endl;
    higherList.display();
    cout << "\nCourses with listeners below or equal to average:" << endl;
    lowerList.display();

    cout << "\nReverse: " << endl;
    cout << "\nCourses with listeners above average:" << endl;
    higherList.displayReverse();
    cout << "\nCourses with listeners below or equal to average:" << endl;
    lowerList.displayReverse();

    courseList.clear();
    higherList.clear();
    lowerList.clear();

    return 0;
}
