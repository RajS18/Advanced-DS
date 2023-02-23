#include <iostream>
#include <queue>

using namespace std;

// Leftist tree node
class LeftistNode {
public:
    int key;
    int rank;
    LeftistNode* left;
    LeftistNode* right;

    LeftistNode(int key) {
        this->key = key;
        this->rank = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~LeftistNode() {
        delete left;
        delete right;
    }
};

// Comparison object to be used to order the leftist tree
class Compare {
public:
    bool operator()(LeftistNode* l, LeftistNode* r) {
        return l->key > r->key;
    }
};

// Utility function to merge two leftist trees
LeftistNode* merge(LeftistNode* a, LeftistNode* b) {
    if (!a) {
        return b;
    }
    if (!b) {
        return a;
    }

    if (a->key > b->key) {
        swap(a, b);
    }

    a->right = merge(a->right, b);

    if (!a->left || a->left->rank < a->right->rank) {
        swap(a->left, a->right);
    }

    a->rank = a->right ? a->right->rank + 1 : 0;

    return a;
}

// Function to insert a key into a leftist tree
LeftistNode* insert(LeftistNode* root, int key) {
    LeftistNode* newNode = new LeftistNode(key);
    return merge(root, newNode);
}

// Function to delete the minimum key from a leftist tree
LeftistNode* deleteMin(LeftistNode* root) {
    if (!root) {
        return nullptr;
    }

    LeftistNode* newRoot = merge(root->left, root->right);
    root->left = root->right = nullptr;
    delete root;

    return newRoot;
}

// Function to print the keys of a leftist tree in level order
void levelOrderTraversal(LeftistNode* root) {
    if (!root) {
        return;
    }

    queue<LeftistNode*> q;
    q.push(root);

    while (!q.empty()) {
        LeftistNode* node = q.front(); q.pop();
        cout << node->key << " ";

        if (node->left) {
            q.push(node->left);
        }

        if (node->right) {
            q.push(node->right);
        }
    }
}

int main() {
    LeftistNode* root = nullptr;

    root = insert(root, 3);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 5);

    cout << "Level order traversal before deleting minimum key: ";
    levelOrderTraversal(root);
    cout << endl;

    root = deleteMin(root);

    cout << "Level order traversal after deleting minimum key: ";
    levelOrderTraversal(root);
    cout << endl;

    delete root;
    return 0;
}

