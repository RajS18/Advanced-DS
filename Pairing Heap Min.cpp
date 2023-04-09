#include <iostream>

template <typename T>
class PairingHeap {
public:
    struct Node {
        T value;
        Node* child;
        Node* sibling;

        Node(const T& value) : value(value), child(nullptr), sibling(nullptr) {}
    };

    PairingHeap() : root(nullptr) {}

    ~PairingHeap() {
        deleteSubtree(root);
    }

    bool empty() const {
        return root == nullptr;
    }

    void insert(const T& value) {
        Node* node = new Node(value);
        root = merge(root, node);
    }

    const T& findMin() const {
        return root->value;
    }

    void deleteMin() {
        Node* oldRoot = root;
        root = mergePairs(root->child);
        delete oldRoot;
    }

    void decreaseKey(Node* node, const T& newValue) {
        if (newValue < node->value) {
            node->value = newValue;
            if (node != root) {
                if (node->sibling) {
                    node->sibling->sibling = nullptr;
                }
                node->sibling = root->child;
                root->child = node;
                node = root;
                root = mergePairs(root->child);
                node->sibling = nullptr;
                root = merge(node, root);
            }
        }
    }

private:
    Node* root;

    void deleteSubtree(Node* node) {
        if (node) {
            deleteSubtree(node->child);
            deleteSubtree(node->sibling);
            delete node;
        }
    }

    Node* merge(Node* a, Node* b) {
        if (!a) {
            return b;
        } else if (!b) {
            return a;
        } else if (a->value < b->value) {
            b->sibling = a->child;
            a->child = b;
            return a;
        } else {
            a->sibling = b->child;
            b->child = a;
            return b;
        }
    }

    Node* mergePairs(Node* node) {
        if (!node || !node->sibling) {
            return node;
        } else {
            Node* a = node;
            Node* b = node->sibling;
            Node* c = b->sibling;
            a->sibling = nullptr;
            b->sibling = nullptr;
            return merge(merge(a, b), mergePairs(c));
        }
    }
};
