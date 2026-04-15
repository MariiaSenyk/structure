#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct Node {
    int height;
    string name;
    Node *left;
    Node *right;
} *root = nullptr;

struct NodeHeight {
    int height;
    NodeHeight *left;
    NodeHeight *right;
} *rootNew = nullptr;

void addNode(Node *&r, int h, const string &n) {
    if (r == nullptr) {
        r = new Node{h, n, nullptr, nullptr};
        return;
    }
    if (h < r->height)
        addNode(r->left, h, n);
    else
        addNode(r->right, h, n);
}

void addNodeHeight(NodeHeight *&r, int h) {
    if (r == nullptr) {
        r = new NodeHeight{h, nullptr, nullptr};
        return;
    }
    if (h < r->height)
        addNodeHeight(r->left, h);
    else
        addNodeHeight(r->right, h);
}

void findAndCountName(Node *r, const string &targetName, int &count) {
    if (r == nullptr) return;
    if (r->name == targetName)
        count++;
    findAndCountName(r->left, targetName, count);
    findAndCountName(r->right, targetName, count);
}

void buildNewTreeFromLeftSubtree(Node *source, NodeHeight *&destRoot) {
    if (source == nullptr) return;
    addNodeHeight(destRoot, source->height);
    buildNewTreeFromLeftSubtree(source->left, destRoot);
    buildNewTreeFromLeftSubtree(source->right, destRoot);
}

int getDepth(Node *r) {
    if (r == nullptr) return 0;
    return 1 + max(getDepth(r->left), getDepth(r->right));
}

int getDepthNew(NodeHeight *r) {
    if (r == nullptr) return 0;
    return 1 + max(getDepthNew(r->left), getDepthNew(r->right));
}

int countNodes(Node *r) {
    if (r == nullptr) return 0;
    return 1 + countNodes(r->left) + countNodes(r->right);
}

int countNodesNew(NodeHeight *r) {
    if (r == nullptr) return 0;
    return 1 + countNodesNew(r->left) + countNodesNew(r->right);
}

void deleteTree(Node *&r) {
    if (r == nullptr) return;
    deleteTree(r->left);
    deleteTree(r->right);
    delete r;
    r = nullptr;
}

void deleteTreeNew(NodeHeight *&r) {
    if (r == nullptr) return;
    deleteTreeNew(r->left);
    deleteTreeNew(r->right);
    delete r;
    r = nullptr;
}

int main() {
    srand(time(nullptr));

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    string sampleNames[] = {"Ivan", "Oleg", "Anna", "Maria", "Petro", "Olena", "Max"};
    int namesCount = 7;

    for (int i = 0; i < n; i++) {
        int randomHeight = 150 + rand() % 51;
        string randomName = sampleNames[rand() % namesCount];
        addNode(root, randomHeight, randomName);
    }
    cout << "Tree generated successfully.\n";

    string searchName;
    cout << "\nEnter name to search for: ";
    cin >> searchName;

    int nameCount = 0;
    findAndCountName(root, searchName, nameCount);

    if (nameCount > 0) {
        cout << "Name '" << searchName << "' exists in the tree.\n";
        cout << "Number of occurrences: " << nameCount << "\n";
    } else {
        cout << "Name not found.\n";
    }

    if (root != nullptr && root->left != nullptr) {
        buildNewTreeFromLeftSubtree(root->left, rootNew);
        cout << "\nNew tree built from the left subtree.\n";
    } else {
        cout << "\nLeft subtree does not exist. New tree is empty.\n";
    }

    cout << "\nOriginal tree:\n";
    cout << "  Number of nodes: " << countNodes(root) << '\n';
    cout << "  Depth: " << getDepth(root) << '\n';

    cout << "\nNew tree (heights only):\n";
    cout << "  Number of nodes: " << countNodesNew(rootNew) << '\n';
    cout << "  Depth: " << getDepthNew(rootNew) << '\n';

    deleteTree(root);
    deleteTreeNew(rootNew);

    return 0;
}