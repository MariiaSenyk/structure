#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {
    }
};

class BinarySearchTree {
private:
    Node *root;

    void insert(Node *&node, int val) {
        if (node == nullptr) {
            node = new Node(val);
        } else if (val < node->data) {
            insert(node->left, val);
        } else {
            insert(node->right, val);
        }
    }

    bool find(Node *node, int val) {
        if (node == nullptr) return false;
        if (node->data == val) return true;
        if (val < node->data) return find(node->left, val);
        return find(node->right, val);
    }

    int depth(Node *node) {
        if (node == nullptr) return 0;
        int left_depth = depth(node->left);
        int right_depth = depth(node->right);
        return max(left_depth, right_depth) + 1;
    }

    void generateEvenOddTrees(Node *node, BinarySearchTree &evenTree, BinarySearchTree &oddTree) {
        if (node == nullptr) return;
        if (node->data % 2 == 0) evenTree.insert(node->data);
        else oddTree.insert(node->data);
        generateEvenOddTrees(node->left, evenTree, oddTree);
        generateEvenOddTrees(node->right, evenTree, oddTree);
    }

    void deleteTree(Node *node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {
    }

    void insert(int val) {
        insert(root, val);
    }

    bool find(int val) {
        return find(root, val);
    }

    int depth() {
        return depth(root);
    }

    void generateEvenOddTrees(BinarySearchTree &evenTree, BinarySearchTree &oddTree) {
        generateEvenOddTrees(root, evenTree, oddTree);
    }

    void deleteTree() {
        deleteTree(root);
        root = nullptr;
    }

    ~BinarySearchTree() {
        deleteTree();
    }
};

int main() {
    srand(time(0));

    BinarySearchTree tree;
    int n, choice;

    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Choose input method (1: Manual, 2: Random): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the values: ";
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            tree.insert(val);
        }
    } else if (choice == 2) {
        int a, b;
        cout << "Enter the range [a, b]: ";
        cin >> a >> b;
        if (n > (b - a)) {
            cout << "Error: n should be less than or equal to (b - a)" << endl;
            return 1;
        }
        for (int i = 0; i < n; i++) {
            int val = rand() % (b - a + 1) + a;
            tree.insert(val);
        }
    }

    cout << "Tree depth: " << tree.depth() << endl;

    BinarySearchTree evenTree, oddTree;
    tree.generateEvenOddTrees(evenTree, oddTree);

    cout << "Even tree depth: " << evenTree.depth() << endl;
    cout << "Odd tree depth: " << oddTree.depth() << endl;

    tree.deleteTree();
    evenTree.deleteTree();
    oddTree.deleteTree();

    return 0;
}
