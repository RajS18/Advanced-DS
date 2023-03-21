/*  Order Book  Using Map of Vectors  */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Order {
    string id;
    string symbol;
    double price;
    int quantity;
    string side;
};

class OrderBook {
public:
    void addOrder(Order order) {
        if (order.side == "buy") {
            buyOrders[order.price].push_back(order);
        } else if (order.side == "sell") {
            sellOrders[order.price].push_back(order);
        }
    }

    void printOrderBook() {
        cout << "Buy Orders:" << endl;
        for (auto it = buyOrders.rbegin(); it != buyOrders.rend(); it++) {
            for (auto order : it->second) {
                cout << order.id << " " << order.symbol << " " << order.price << " " << order.quantity << " " << order.side << endl;
            }
        }

        cout << "Sell Orders:" << endl;
        for (auto it = sellOrders.begin(); it != sellOrders.end(); it++) {
            for (auto order : it->second) {
                cout << order.id << " " << order.symbol << " " << order.price << " " << order.quantity << " " << order.side << endl;
            }
        }
    }

private:
    map<double, vector<Order> > buyOrders;
    map<double, vector<Order> > sellOrders;
};

int main() {
	cout<<"HI"<<endl;
    OrderBook orderBook;
    Order order1 = {"order1", "AAPL", 100.0, 100, "buy"};
    Order order2 = {"order2", "AAPL", 99.0, 200, "buy"};
    Order order3 = {"order3", "AAPL", 101.0, 50, "sell"};
    orderBook.addOrder(order1);
    orderBook.addOrder(order2);
    orderBook.addOrder(order3);
    cout<<"Hello";
    orderBook.printOrderBook();
    return 1;
}


