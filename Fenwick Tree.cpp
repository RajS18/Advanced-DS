#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, BIT[N];

void update(int x, int val) {
    for (int i = x; i <= n; i += i & -i) {
        BIT[i] += val;
    }
}

int query(int x) {
    int sum = 0;
    for (int i = x; i > 0; i -= i & -i) {
        sum += BIT[i];
    }
    return sum;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        update(i, x);
    }

    // Example usage of query
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << query(r) - query(l-1) << endl;
    }

    return 0;
}
