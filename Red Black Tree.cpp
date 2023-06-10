#include <iostream>
#include <vector>

using namespace std;

enum Color {RED, BLACK};

struct Node {
    int val;
    Color color;
    Node *left, *right, *parent;

    Node(int val) : val(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;

    Node *insert(Node *node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }

        if (val < node->val) {
            node->left = insert(node->left, val);
            node->left->parent = node;
        } else {
            node->right = insert(node->right, val);
            node->right->parent = node;
        }

        if (node->right && node->right->color == RED && node->left && node->left->color == RED) {
            flipColors(node);
        }

        if (node->right && node->right->color == RED && (!node->left || node->left->color == BLACK)) {
            node = rotateLeft(node);
        }

        if (node->left && node->left->color == RED && node->left->left && node->left->left->color == RED) {
            node = rotateRight(node);
        }

        return node;
    }

    void flipColors(Node *node) {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }

    Node *rotateLeft(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        tmp->color = node->color;
        node->color = RED;
        return tmp;
    }

    Node *rotateRight(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        tmp->color = node->color;
        node->color = RED;
        return tmp;
    }

    void inorder(Node *node, vector<int> &result) {
        if (node == nullptr) {
            return;
        }

        inorder(node->left, result);
        result.push_back(node->val);
        inorder(node->right, result);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
        root->color = BLACK;
    }

    vector<int> inorder() {
        vector<int> result;
        inorder(root, result);
        return result;
    }
};
int main(){
    cout<<"Compiled";
    return 0;
}