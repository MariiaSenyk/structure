#include <iostream>

using namespace std;

class Stack {
private:
    int *stackArray;
    int top;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        stackArray = new int[capacity];
        top = -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack overflow!" << endl;
            return;
        }
        stackArray[++top] = value;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        top--;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Stack elements: ";
        for (int i = 0; i <= top; i++) {
            cout << stackArray[i] << " ";
        }
        cout << endl;
    }

    double calculateAverage() {
        if (isEmpty()) return 0;
        int sum = 0;
        for (int i = 0; i <= top; i++) {
            sum += stackArray[i];
        }
        return static_cast<double>(sum) / (top + 1);
    }

    void clear() {
        top = -1;
    }

    ~Stack() {
        delete[] stackArray;
    }
};

int main() {
    Stack stack(5);
    stack.push(85);
    stack.push(90);
    stack.push(78);
    stack.push(92);
    stack.push(88);

    stack.display();
    cout << "Average grade: " << stack.calculateAverage() << endl;

    stack.clear();

    return 0;
}
