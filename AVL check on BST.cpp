/*  AVL check non optimized */

#include<bits/stdc++.h>

#define MAX 1000000000+7
#define PI 3.14159265358
#define ll long long
#define endl '\n'
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define display(x) for(auto x1:x)cout<<x1<<" ";
using namespace std;

ll add(ll x,ll y){ll res = x+y;return (res>=MAX?res-MAX:res);}
ll mul(ll x,ll y){ll res = x*y;return (res>=MAX?res%MAX:res);}
ll power(ll x,ll y){
   ll res=1;x%=MAX;
   while(y){
   		if(y&1) {
   			res=mul(res,x);
			y=y-1;
		}
		else {
			y>>=1;
			x=mul(x,x);
		}
	}
   return res;
}
void solve(){

}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root == NULL) return true;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right))
            return true;

        return false;
    }

    int height(TreeNode* node) {
        if (node == NULL) return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    }
};

int main() {
    // construct the binary search tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    Solution sol;
    if (sol.isBalanced(root))
        cout << "The BST is an AVL tree" << endl;
    else
        cout << "The BST is not an AVL tree" << endl;

    return 0;
}



