#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), height(1), left(NULL), right(NULL) {}
};

class Solution {
public:
    int height(TreeNode* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    int getBalance(TreeNode* node) {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        // perform rotation
        x->right = y;
        y->left = T2;

        // update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        // perform rotation
        y->left = x;
        x->right = T2;

        // update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    TreeNode* insert(TreeNode* node, int val) {
        if (node == NULL) return new TreeNode(val);

        if (val < node->val)
            node->left = insert(node->left, val);
        else if (val > node->val)
            node->right = insert(node->right, val);
        else // val already exists
            return node;

        // update height of the ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // check the balance factor of the node
        int balance = getBalance(node);

        // if the node becomes unbalanced, there are 4 cases to consider

        // left left case
        if (balance > 1 && val < node->left->val)
            return rightRotate(node);

        // right right case
        if (balance < -1 && val > node->right->val)
            return leftRotate(node);

        // left right case
        if (balance > 1 && val > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // right left case
        if (balance < -1 && val < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(TreeNode* node) {
        if (node == NULL) return;
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }
};

int main() {
    Solution sol;
    TreeNode* root = NULL;
//manual insert
    root = sol.insert(root, 10);
    root = sol.insert(root, 20);
    root = sol.insert(root, 30);
    root = sol.insert(root, 40);
    root = sol.insert(root, 50);
    root = sol.insert(root, 25);
    cout << "Inorder traversal of the AVL tree: ";
    sol.inOrder(root);
    cout << endl;

    return 0;
}

