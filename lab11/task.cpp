#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct Node {
    int height;
    string name;
    Node *left;
    Node *right;
} *root;

struct NodeHeight {
    int height;
    NodeHeight *left;
    NodeHeight *right;
} *rootNew;

void addNode(Node *&r, int h, string n) {
    if (r == nullptr) {
        Node *c = new Node;
        c->height = h;
        c->name = n;
        c->left = nullptr;
        c->right = nullptr;
        r = c;
        return;
    }
    if (h < r->height) {
        addNode(r->left, h, n);
    } else {
        addNode(r->right, h, n);
    }
}

void addNodeHeight(NodeHeight *&r, int h) {
    if (r == nullptr) {
        NodeHeight *c = new NodeHeight;
        c->height = h;
        c->left = nullptr;
        c->right = nullptr;
        r = c;
        return;
    }
    if (h < r->height) {
        addNodeHeight(r->left, h);
    } else {
        addNodeHeight(r->right, h);
    }
}

void findAndCountName(Node *r, const string &targetName, int &count) {
    if (r == nullptr) return;
    if (r->name == targetName) {
        count++;
    }

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
    int leftD = getDepth(r->left);
    int rightD = getDepth(r->right);
    return (leftD > rightD) ? leftD + 1 : rightD + 1;
}

int getDepthNew(NodeHeight *r) {
    if (r == nullptr) return 0;
    int leftD = getDepthNew(r->left);
    int rightD = getDepthNew(r->right);
    return (leftD > rightD) ? leftD + 1 : rightD + 1;
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
    if (r != nullptr) {
        deleteTree(r->left);
        deleteTree(r->right);
        delete r;
        r = nullptr;
    }
}

void deleteTreeNew(NodeHeight *&r) {
    if (r != nullptr) {
        deleteTreeNew(r->left);
        deleteTreeNew(r->right);
        delete r;
        r = nullptr;
    }
}

int main() {
    srand(time(NULL));

    root = nullptr;
    rootNew = nullptr;

    int n;
    cout << "Vvedit kilkist vuzliv: ";
    cin >> n;

    string sampleNames[] = {"Ivan", "Oleg", "Anna", "Maria", "Petro", "Olena", "Max"};
    int namesCount = 7;

    for (int i = 0; i < n; i++) {
        int randomHeight = 150 + rand() % 51;
        string randomName = sampleNames[rand() % namesCount];
        addNode(root, randomHeight, randomName);
    }
    cout << "Derevo zgenerovano\n";

    string searchName;
    cout << "\nVvedit im'ya dlia poshuku: ";
    cin >> searchName;

    int nameCount = 0;
    findAndCountName(root, searchName, nameCount);

    if (nameCount > 0) {
        cout << "Imya '" << searchName << "' isnuye u derevi\n";
        cout << "Kilkist vhodzhen: " << nameCount << "\n";
    } else {
        cout << "Imya ne znaydeno\n";
    }

    if (root != nullptr && root->left != nullptr) {
        buildNewTreeFromLeftSubtree(root->left, rootNew);
        cout << "\nNove derevo z livogo piddereva sformovano\n";
    } else {
        cout << "\nLivoho piddereva ne isnuye, nove derevo porozhnie\n";
    }

    cout << "Pochatkove derevo:\n";
    cout << "  Kilkist vuzliv: " << countNodes(root) << '\n';
    cout << "  Glybyna: " << getDepth(root) << '\n';

    cout << "Nove derevo (tilky zrist):\n";
    cout << "  Kilkist vuzliv: " << countNodesNew(rootNew) << '\n';
    cout << "  Glybyna: " << getDepthNew(rootNew) << '\n';

    deleteTree(root);
    deleteTreeNew(rootNew);


    return 0;
}
