#include <iostream>
#include <string>

using namespace std;

struct Node {
    string cityName;
    int distanceFromKyiv;
    Node *next;
};

void addToEnd(Node *&head, string cityName, int distanceFromKyiv) {
    Node *newNode = new Node{cityName, distanceFromKyiv, nullptr};

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

void showTwoFarthest(Node *head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node *firstCity = head;
    Node *secondCity = head->next;

    if (secondCity->distanceFromKyiv > firstCity->distanceFromKyiv) {
        Node *tempNode = firstCity;
        firstCity = secondCity;
        secondCity = tempNode;
    }

    head = head->next->next;

    while (head != nullptr) {
        if (head->distanceFromKyiv > firstCity->distanceFromKyiv) {
            secondCity = firstCity;
            firstCity = head;
        } else if (head->distanceFromKyiv > secondCity->distanceFromKyiv) {
            secondCity = head;
        }

        head = head->next;
    }

    cout << firstCity->cityName << endl;
    cout << secondCity->cityName << endl;
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
    int cityCount;

    cin >> cityCount;

    for (int index = 0; index < cityCount; index++) {
        string cityName;
        int distanceFromKyiv;
        cin >> cityName >> distanceFromKyiv;
        addToEnd(head, cityName, distanceFromKyiv);
    }


    showTwoFarthest(head);

    addToEnd(head, "Warsaw", 790);

    deleteList(head);

    return 0;
}
