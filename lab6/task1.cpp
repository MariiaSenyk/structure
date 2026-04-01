#include <iostream>
#include <cstdlib>

using namespace std;

const int stackSize = 10;
const double minValue = -6.0;
const double maxValue = 11.0;

struct RealNumberStackNode
{
    double value;
    RealNumberStackNode* nextNode;
};

double generateRandomRealNumber(double minimumValue, double maximumValue)
{
    double randomPart = static_cast<double>(rand()) / RAND_MAX;
    return minimumValue + randomPart * (maximumValue - minimumValue);
}

void pushToStack(RealNumberStackNode*& topNode, double newValue)
{
    RealNumberStackNode* newNode = new RealNumberStackNode;
    newNode->value = newValue;
    newNode->nextNode = topNode;
    topNode = newNode;
}

bool isStackEmpty(RealNumberStackNode* topNode)
{
    return topNode == nullptr;
}

double popFromStack(RealNumberStackNode*& topNode)
{
    if (isStackEmpty(topNode))
    {
        return 0;
    }

    RealNumberStackNode* nodeToDelete = topNode;
    double removedValue = topNode->value;
    topNode = topNode->nextNode;
    delete nodeToDelete;

    return removedValue;
}

void printStack(RealNumberStackNode* topNode)
{
    cout << "Stack elements: ";

    RealNumberStackNode* currentNode = topNode;

    while (currentNode != nullptr)
    {
        cout << currentNode->value << " ";
        currentNode = currentNode->nextNode;
    }

    cout << endl;
}

double calculateAverageValue(RealNumberStackNode* topNode)
{
    if (topNode == nullptr)
    {
        return 0;
    }

    double sumOfElements = 0;
    int numberOfElements = 0;
    RealNumberStackNode* currentNode = topNode;

    while (currentNode != nullptr)
    {
        sumOfElements += currentNode->value;
        numberOfElements++;
        currentNode = currentNode->nextNode;
    }

    return sumOfElements / numberOfElements;
}

void removeElementsSmallerThanEnteredValue(RealNumberStackNode*& topNode, double enteredValue)
{
    RealNumberStackNode* temporaryStackTopNode = nullptr;

    while (!isStackEmpty(topNode))
    {
        double currentValue = popFromStack(topNode);

        if (currentValue >= enteredValue)
        {
            pushToStack(temporaryStackTopNode, currentValue);
        }
    }

    while (!isStackEmpty(temporaryStackTopNode))
    {
        pushToStack(topNode, popFromStack(temporaryStackTopNode));
    }
}

void deleteEntireStack(RealNumberStackNode*& topNode)
{
    while (!isStackEmpty(topNode))
    {
        popFromStack(topNode);
    }
}

int main()
{
    srand(time(0));

    RealNumberStackNode* topNode = nullptr;
    double enteredValue;

    for (int elementIndex = 0; elementIndex < stackSize; elementIndex++)
    {
        double generatedValue = generateRandomRealNumber(minValue, maxValue);
        pushToStack(topNode, generatedValue);
    }

    cout << "Initial stack:" << endl;
    printStack(topNode);

    cout << "Enter a value: ";
    cin >> enteredValue;

    removeElementsSmallerThanEnteredValue(topNode, enteredValue);

    cout << "Stack after removing elements:" << endl;
    printStack(topNode);

    if (!isStackEmpty(topNode))
    {
        cout << "Average value: " << calculateAverageValue(topNode) << endl;
    }
    else
    {
        cout << "The stack is empty." << endl;
    }

    deleteEntireStack(topNode);

    return 0;
}