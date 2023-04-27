#include <iostream>

class BinaryTrie {
private:
    struct Node {
        char value;
        Node* left;
        Node* right;
        Node(char value) : value(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    BinaryTrie() : root(nullptr) {}

    void insert(char value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* curr = root;
        for (int i = 7; i >= 0; --i) {
            if ((value >> i) & 1) {
                if (!curr->right) {
                    curr->right = new Node(value);
                }
                curr = curr->right;
            } else {
                if (!curr->left) {
                    curr->left = new Node(value);
                }
                curr = curr->left;
            }
        }
    }

    bool contains(char value) const {
        Node* curr = root;
        for (int i = 7; i >= 0; --i) {
            if ((value >> i) & 1) {
                if (!curr->right) {
                    return false;
                }
                curr = curr->right;
            } else {
                if (!curr->left) {
                    return false;
                }
                curr = curr->left;
            }
        }
        return true;
    }

    void remove(char value) {
        if (!root) {
            return;
        }
        remove_recursive(root, value, 7);
    }

private:
    void remove_recursive(Node* node, char value, int bit) {
        if (bit < 0) {
            delete node;
            node = nullptr;
            return;
        }
        if ((value >> bit) & 1) {
            remove_recursive(node->right, value, bit - 1);
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
        } else {
            remove_recursive(node->left, value, bit - 1);
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
        }
    }
};
int main(){
    return 0;
}