/* Order Book  */

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
#include <iostream>
#include <vector>
#include <algorithm>

struct Order {
    int id;
    bool is_buy; // true for buy orders, false for sell orders
    double price;
    int quantity;
};

class OrderBook {
public:
    void add_order(Order order) {
        if (order.is_buy) {
            buy_orders_.push_back(order);
            std::sort(buy_orders_.begin(), buy_orders_.end(), [](const Order& a, const Order& b) { return a.price > b.price; });
        } else {
            sell_orders_.push_back(order);
            std::sort(sell_orders_.begin(), sell_orders_.end(), [](const Order& a, const Order& b) { return a.price < b.price; });
        }
    }

    void remove_order(int order_id) {
        auto it = std::find_if(buy_orders_.begin(), buy_orders_.end(), [order_id](const Order& order) { return order.id == order_id; });
        if (it != buy_orders_.end()) {
            buy_orders_.erase(it);
        } else {
            it = std::find_if(sell_orders_.begin(), sell_orders_.end(), [order_id](const Order& order) { return order.id == order_id; });
            if (it != sell_orders_.end()) {
                sell_orders_.erase(it);
            }
        }
    }

    double get_best_bid_price() const {
        if (buy_orders_.empty()) {
            return 0;
        }
        return buy_orders_.front().price;
    }

    int get_best_bid_quantity() const {
        if (buy_orders_.empty()) {
            return 0;
        }
        int quantity = 0;
        for (const auto& order : buy_orders_) {
            quantity += order.quantity;
        }
        return quantity;
    }

    double get_best_ask_price() const {
        if (sell_orders_.empty()) {
            return 0;
        }
        return sell_orders_.front().price;
    }

    int get_best_ask_quantity() const {
        if (sell_orders_.empty()) {
            return 0;
        }
        int quantity = 0;
        for (const auto& order : sell_orders_) {
            quantity += order.quantity;
        }
        return quantity;
    }

private:
    std::vector<Order> buy_orders_;
    std::vector<Order> sell_orders_;
};

int main() {
    OrderBook order_book;

    // add some orders
    order_book.add_order({1, true, 100.0, 10});
    return 0;
}


