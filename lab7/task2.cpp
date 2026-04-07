#include <iostream>
#include <string>

using namespace std;

struct Node {
    string surname;
    string department;
    float salary;
    Node *next;
    Node *prev;

    Node(string s, string d, float sal) : surname(s), department(d), salary(sal), next(nullptr), prev(nullptr) {
    }
};

class DoublyLinkedList {
private:
    Node *head;
    Node *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {
    }

    void append(string surname, string department, float salary) {
        Node *newNode = new Node(surname, department, salary);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printList() {
        Node *current = head;
        while (current) {
            cout << current->surname << " - " << current->department << " - " << current->salary << " USD" << endl;
            current = current->next;
        }
    }

    void printReverse() {
        Node *current = tail;
        while (current) {
            cout << current->surname << " - " << current->department << " - " << current->salary << " USD" << endl;
            current = current->prev;
        }
    }

    void splitBySalary(float averageSalary, DoublyLinkedList &higherList, DoublyLinkedList &lowerList) {
        Node *current = head;
        while (current) {
            if (current->salary > averageSalary) {
                higherList.append(current->surname, current->department, current->salary);
            } else {
                lowerList.append(current->surname, current->department, current->salary);
            }
            current = current->next;
        }
    }

    float calculateAverageSalary() {
        if (!head) return 0;
        float totalSalary = 0;
        int count = 0;
        Node *current = head;
        while (current) {
            totalSalary += current->salary;
            count++;
            current = current->next;
        }
        return totalSalary / count;
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

    ~DoublyLinkedList() {
        freeMemory();
    }
};

int main() {
    DoublyLinkedList list;
    list.append("Ivanenko", "IT", 1500);
    list.append("Petrenko", "HR", 1200);
    list.append("Senyk", "Finance", 2000);
    list.append("Nigda", "Marketing", 1700);
    list.append("Perzhan", "Sales", 1300);

    float averageSalary = list.calculateAverageSalary();
    cout << "Average salary: " << averageSalary << " USD" << endl;

    DoublyLinkedList higherSalaryList;
    DoublyLinkedList lowerSalaryList;
    list.splitBySalary(averageSalary, higherSalaryList, lowerSalaryList);

    cout << "\nEmployees with salary higher than average:" << endl;
    higherSalaryList.printList();
    cout << "\nEmployees with salary lower or equal to average:" << endl;
    lowerSalaryList.printList();

    cout << "\nEmployees with salary higher than average (reverse):" << endl;
    higherSalaryList.printReverse();
    cout << "\nEmployees with salary lower or equal to average (reverse):" << endl;
    lowerSalaryList.printReverse();

    higherSalaryList.append("Novikov", "IT", 2200);
    cout << "\nAfter adding new employee to higher salary list:" << endl;
    higherSalaryList.printList();

    list.freeMemory();
    higherSalaryList.freeMemory();
    lowerSalaryList.freeMemory();

    return 0;
}
