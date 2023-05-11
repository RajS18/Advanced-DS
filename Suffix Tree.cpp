#include <bits/stdc++.h>
#include <unordered_map>

class SuffixTree {
public:
    SuffixTree(std::string str) {
        root_ = new Node;
        for (int i = 0; i < str.length(); i++) {
            insert(str.substr(i), i);
        }
    }

    void insert(std::string suffix, int index) {
        Node* curr = root_;
        for (char c : suffix) {
            if (curr->children.count(c) == 0) {
                curr->children[c] = new Node;
            }
            curr = curr->children[c];
        }
        curr->indexes.push_back(index);
    }

    void print() {
        print(root_, 0);
    }

    bool search(std::string substr) {
        Node* curr = root_;
        for (char c : substr) {
            if (curr->children.count(c) == 0) {
                // If the substring character is not in the tree, start a new search from the root
                curr = root_;
                continue;
            }
            curr = curr->children[c];
            for (int index : curr->indexes) {
                if (index >= substr.length() - 1) {
                    // If the substring matches the end of a suffix, print the index
                    std::cout << "Found at index: " << index - substr.length() + 1 << std::endl;
                }
            }
        }
        return true;
    }

private:
    struct Node {
        std::unordered_map<char, Node*> children;
        std::vector<int> indexes;
    };

    Node* root_;

    void print(Node* node, int level) {
        for (auto child : node->children) {
            for (int i = 0; i < level; i++) {
                std::cout << " ";
            }
            std::cout << child.first << std::endl;
            print(child.second, level + 1);
        }
    }
};

int main() {
    std::string str = "banana";
    SuffixTree suffixTree(str);
    suffixTree.print();
    return 0;
}
