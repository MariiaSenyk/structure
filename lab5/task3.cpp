#include <iostream>
#include <string>

using namespace std;

struct Node {
    string carName;
    int productionYear;
    int price;
    Node *next;
};

void addToEnd(Node *&head, string carName, int productionYear, int price) {
    Node *newNode = new Node{carName, productionYear, price, nullptr};

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

void showCars(Node *head) {
    int currentYear = 2026;

    while (head != nullptr) {
        if (currentYear - head->productionYear > 10 && head->price < 5000) {
            cout << head->carName << " " << head->productionYear << " " << head->price << endl;
        }

        head = head->next;
    }
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
    int carCount;

    cin >> carCount;

    for (int index = 0; index < carCount; index++) {
        string carName;
        int productionYear;
        int price;
        cin >> carName >> productionYear >> price;
        addToEnd(head, carName, productionYear, price);
    }

    showCars(head);
    deleteList(head);

    return 0;
}
