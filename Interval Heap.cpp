/*  Interval Heap  */

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
#include <iostream>
#include <vector>

template <typename T>
class IntervalHeap {
private:
    std::vector<std::pair<T, T> > heap;

    bool is_min_level(int index) const {
        int level = 0;
        while (index > 0) {
            index >>= 1;
            level++;
        }
        return level % 2 == 0;
    }

    bool compare(const std::pair<T, T>& a, const std::pair<T, T>& b) const {
        return a.second < b.second;
    }

    void bubble_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (compare(heap[index], heap[parent])) {
                std::swap(heap[index], heap[parent]);
            }
            index = parent;
        }
    }

    void bubble_down(int index) {
        while (index < heap.size()) {
            int left_child = 2 * index + 1;
            int right_child = 2 * index + 2;
            int min_child = index;

            if (left_child < heap.size() && compare(heap[left_child], heap[min_child])) {
                min_child = left_child;
            }
            if (right_child < heap.size() && compare(heap[right_child], heap[min_child])) {
                min_child = right_child;
            }

            if (min_child != index) {
                std::swap(heap[index], heap[min_child]);
                index = min_child;
            } else {
                break;
            }
        }
    }

public:
    IntervalHeap() {}

    bool empty() const {
        return heap.empty();
    }

    void insert(const std::pair<T, T>& interval) {
        heap.push_back(interval);
        bubble_up(heap.size() - 1);
    }

    std::pair<T, T> get_min() const {
        if (empty()) {
            throw std::runtime_error("Heap is empty.");
        }
        return heap[0];
    }

    void delete_min() {
        if (empty()) {
            throw std::runtime_error("Heap is empty.");
        }
        heap[0] = heap.back();
        heap.pop_back();
        bubble_down(0);
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
	//Create Interval Heap instance Here.
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

