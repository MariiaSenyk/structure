#include <iostream>
#include <cmath>

using namespace std;

const int QUEUE_SIZE = 10;
const int RANDOM_MINIMUM_VALUE = 1;
const int RANDOM_MAXIMUM_VALUE = 20;
const int INSERTED_VALUE = 100;

struct IntegerQueueNode
{
    int value;
    IntegerQueueNode* nextNode;
};

void pushToQueue(IntegerQueueNode*& frontNode, IntegerQueueNode*& rearNode, int newValue)
{
    IntegerQueueNode* newNode = new IntegerQueueNode;
    newNode->value = newValue;
    newNode->nextNode = nullptr;

    if (rearNode == nullptr)
    {
        frontNode = newNode;
        rearNode = newNode;
    }
    else
    {
        rearNode->nextNode = newNode;
        rearNode = newNode;
    }
}

bool isQueueEmpty(IntegerQueueNode* frontNode)
{
    return frontNode == nullptr;
}

int popFromQueue(IntegerQueueNode*& frontNode, IntegerQueueNode*& rearNode)
{
    if (isQueueEmpty(frontNode))
    {
        return 0;
    }

    IntegerQueueNode* nodeToDelete = frontNode;
    int removedValue = frontNode->value;
    frontNode = frontNode->nextNode;

    if (frontNode == nullptr)
    {
        rearNode = nullptr;
    }

    delete nodeToDelete;
    return removedValue;
}

void printQueue(IntegerQueueNode* frontNode)
{
    cout << "Queue elements: ";

    IntegerQueueNode* currentNode = frontNode;

    while (currentNode != nullptr)
    {
        cout << currentNode->value << " ";
        currentNode = currentNode->nextNode;
    }

    cout << endl;
}

double calculateGeometricMean(IntegerQueueNode* frontNode)
{
    if (frontNode == nullptr)
    {
        return 0;
    }

    double productOfElements = 1;
    int numberOfElements = 0;
    IntegerQueueNode* currentNode = frontNode;

    while (currentNode != nullptr)
    {
        productOfElements *= currentNode->value;
        numberOfElements++;
        currentNode = currentNode->nextNode;
    }

    return pow(productOfElements, 1.0 / numberOfElements);
}

void insertAfterEachEvenElement(IntegerQueueNode*& frontNode, IntegerQueueNode*& rearNode)
{
    IntegerQueueNode* newFrontNode = nullptr;
    IntegerQueueNode* newRearNode = nullptr;

    while (!isQueueEmpty(frontNode))
    {
        int currentValue = popFromQueue(frontNode, rearNode);
        pushToQueue(newFrontNode, newRearNode, currentValue);

        if (currentValue % 2 == 0)
        {
            pushToQueue(newFrontNode, newRearNode, INSERTED_VALUE);
        }
    }

    frontNode = newFrontNode;
    rearNode = newRearNode;
}

void deleteEntireQueue(IntegerQueueNode*& frontNode, IntegerQueueNode*& rearNode)
{
    while (!isQueueEmpty(frontNode))
    {
        popFromQueue(frontNode, rearNode);
    }
}

int main()
{
    srand(time(0));

    IntegerQueueNode* frontNode = nullptr;
    IntegerQueueNode* rearNode = nullptr;

    for (int elementIndex = 0; elementIndex < QUEUE_SIZE; elementIndex++)
    {
        int generatedValue = RANDOM_MINIMUM_VALUE + rand() % (RANDOM_MAXIMUM_VALUE - RANDOM_MINIMUM_VALUE + 1);
        pushToQueue(frontNode, rearNode, generatedValue);
    }

    cout << "Initial queue:" << endl;
    printQueue(frontNode);

    insertAfterEachEvenElement(frontNode, rearNode);

    cout << "Modified queue:" << endl;
    printQueue(frontNode);

    cout << "Geometric mean: " << calculateGeometricMean(frontNode) << endl;

    deleteEntireQueue(frontNode, rearNode);

    return 0;
}