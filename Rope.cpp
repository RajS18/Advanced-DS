#include <iostream>
#include <string>

using namespace std;

class Rope {
private:
    class Node {
    public:
        string data;
        int weight;
        Node* left;
        Node* right;
        Node(string str) {
            data = str;
            weight = str.length();
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    void split(Node* node, int index) {
        if (index == node->weight) {
            return;
        }
        if (index == 0) {
            root = node;
            return;
        }
        if (index < node->left->weight) {
            split(node->left, index);
            Node* new_node = new Node("");
            new_node->right = node->right;
            new_node->left = node->left->right;
            node->left->right = new_node;
            node->right = nullptr;
            node->left->weight = node->left->data.length();
            node->weight = node->left->weight + (node->left->right ? node->left->right->weight : 0);
        } else {
            split(node->right, index - node->left->weight);
            Node* new_node = new Node("");
            new_node->left = node->left;
            new_node->right = node->right->left;
            node->right->left = new_node;
            node->left = nullptr;
            node->right->weight = node->right->data.length();
            node->weight = (node->left ? node->left->weight : 0) + node->right->weight;
        }
    }

    string concatenate(Node* node) {
        if (!node) {
            return "";
        }
        return concatenate(node->left) + node->data + concatenate(node->right);
    }

    void print(Node* node) {
        if (!node) {
            return;
        }
        print(node->left);
        cout << node->data << " ";
        print(node->right);
    }

public:
    Rope(string str) {
        root = new Node(str);
    }

    void insert(string str, int index) {
        split(root, index);
        Node* new_node = new Node(str);
        new_node->left = root->right;
        new_node->right = nullptr;
        root->right = new_node;
        root->weight = root->left->data.length() + (root->left->right ? root->left->right->weight : 0);
    }

    void erase(int start_index, int end_index) {
        split(root, start_index);
        Node* end_node = root->right;
        split(end_node, end_index - start_index);
        root->right = end_node->right;
        root->weight = root->left->data.length() + (root->left->right ? root->left->right->weight : 0);
        delete end_node;
    }

    string substring(int start_index, int end_index) {
        split(root, start_index);
        Node* end_node = root->right;
        split(end_node, end_index - start_index);
        string result = end_node->data;
        root->right = end_node;
        root->weight = root->left->data.length() + (root->left->right ? root->left->right->weight : 0);
        return result;
    }

    string concatenate() {
        return concatenate(root);
    }

    void print() {
        print(root);
    }
};
int main(){
    return 0;
}