#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class TechNode {
public:
    string code;
    string name;
    double price;
    TechNode* left;
    TechNode* right;

    TechNode(string c, string n, double p) : code(c), name(n), price(p), left(nullptr), right(nullptr) {}
};

class TechTree {
private:
    TechNode* root;

    void insert(TechNode*& node, const string& code, const string& name, double price) {
        if (node == nullptr) {
            node = new TechNode(code, name, price);
        } else if (code < node->code) {
            insert(node->left, code, name, price);
        } else {
            insert(node->right, code, name, price);
        }
    }

    double calculateAveragePrice(TechNode* node, int& count) {
        if (node == nullptr) return 0;
        count++;
        double left = calculateAveragePrice(node->left, count);
        double right = calculateAveragePrice(node->right, count);
        return node->price + left + right;
    }

    int countNodesAtLevel(TechNode* node, int level, int currentLevel) {
        if (node == nullptr) return 0;
        if (currentLevel == level) return 1;
        return countNodesAtLevel(node->left, level, currentLevel + 1) + countNodesAtLevel(node->right, level, currentLevel + 1);
    }

    TechNode* findNode(TechNode* node, const string& code) {
        if (node == nullptr) return nullptr;
        if (node->code == code) return node;
        if (code < node->code) return findNode(node->left, code);
        return findNode(node->right, code);
    }

    void deleteTree(TechNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    TechTree() : root(nullptr) {}

    void insert(const string& code, const string& name, double price) {
        insert(root, code, name, price);
    }

    double calculateAveragePrice() {
        int count = 0;
        double total = calculateAveragePrice(root, count);
        return total / count;
    }

    int countNodesAtLevel(int level) {
        return countNodesAtLevel(root, level, 0);
    }

    void deleteNodeAndDescendants(const string& code) {
        TechNode* node = findNode(root, code);
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            node->left = nullptr;
            node->right = nullptr;
        }
    }

    ~TechTree() {
        deleteTree(root);
    }
};

int main() {
    ifstream file("tech_info.txt");
    string code, name;
    double price;
    TechTree techTree;

    while (file >> code >> name >> price) {
        techTree.insert(code, name, price);
    }

    cout << "Average price: " << techTree.calculateAveragePrice() << endl;

    int level;
    cout << "Enter level to count nodes: ";
    cin >> level;
    cout << "Nodes at level " << level << ": " << techTree.countNodesAtLevel(level) << endl;

    cout << "Enter code to delete: ";
    cin >> code;
    techTree.deleteNodeAndDescendants(code);

    return 0;
}