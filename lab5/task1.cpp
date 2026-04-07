#include <iostream>
using namespace std;

struct Node {
    int value;
    Node *next;
};

void addToBeginning(Node *&head, int value) {
    head = new Node{value, head};
}

void addToEnd(Node *&head, int value) {
    Node *newNode = new Node{value, nullptr};

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node *currentNode = head;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
}

void addToMiddle(Node *&head, int value) {
    if (head == nullptr || head->next == nullptr) {
        addToEnd(head, value);
        return;
    }

    Node *newNode = new Node{value, head->next};
    head->next = newNode;
}

double findAverage(Node *head) {
    int sum = 0;
    int count = 0;

    while (head != nullptr) {
        sum += head->value;
        count++;
        head = head->next;
    }

    return (double) sum / count;
}

void deleteFirstEven(Node *&head) {
    if (head == nullptr) {
        return;
    }

    if (head->value % 2 == 0) {
        Node *tempNode = head;
        head = head->next;
        delete tempNode;
        return;
    }

    Node *currentNode = head;

    while (currentNode->next != nullptr) {
        if (currentNode->next->value % 2 == 0) {
            Node *tempNode = currentNode->next;
            currentNode->next = tempNode->next;
            delete tempNode;
            return;
        }

        currentNode = currentNode->next;
    }
}

void printList(Node *head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

void deleteList(Node *&head) {
    while (head != nullptr) {
        Node *tempNode = head;
        head = head->next;
        delete tempNode;
    }
}

int main() {
    Node *head = nullptr;

    addToBeginning(head, 20);
    addToEnd(head, 40);
    addToMiddle(head, 30);
    addToBeginning(head, 9);

    printList(head);
    cout << findAverage(head) << endl;

    deleteFirstEven(head);
    printList(head);

    deleteList(head);

    return 0;
}
