#include<bits/stdc++.h>
#include<unordered_map>
#define MAX 1000000000+7
#define nullptr NULL
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


template <typename T>
struct HuffmanNode {
    T data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(const T& d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}

    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

template <typename T>
struct HuffmanNodeCompare {
    bool operator()(const HuffmanNode<T>* a, const HuffmanNode<T>* b) const {
        return a->frequency > b->frequency;
    }
};

template <typename T>
class HuffmanTree {
private:
    HuffmanNode<T>* root;

    void build_tree(unordered_map< T, int> & frequency_table) {
        std::priority_queue<HuffmanNode<T>*, std::vector<HuffmanNode<T>*>, HuffmanNodeCompare<T>> pq;
        for (const auto& p : frequency_table) {
            pq.push(new HuffmanNode<T>(p.first, p.second));
        }

        while (pq.size() > 1) {
            HuffmanNode<T>* left = pq.top();
            pq.pop();
            HuffmanNode<T>* right = pq.top();
            pq.pop();
            HuffmanNode<T>* parent = new HuffmanNode<T>(T(), left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;
            pq.push(parent);
        }

        root = pq.top();
    }

public:
    HuffmanTree(unordered_map<T, int>& frequency_table) : root(nullptr) {
        build_tree(frequency_table);
    }

    ~HuffmanTree() {
        delete root;
    }

    std::unordered_map<T, std::string> get_codes() const {
        std::unordered_map<T, std::string> codes;
        std::function<void(const HuffmanNode<T>*, std::string)> traverse = [&](const HuffmanNode<T>* node, std::string code) {
            if (node->left == nullptr && node->right == nullptr) {
                codes[node->data] = code;
            } else {
                traverse(node->left, code + "0");
                traverse(node->right, code + "1");
            }
        };
        traverse(root, "");
        return codes;
    }
};

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
	//Use Huffman tree template class here
}
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	//Testcases
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}

