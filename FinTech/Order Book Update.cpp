#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
// Assumptions:

// The CSV file has headers.
// The order side is represented by a single character ('B' for Buy, 'S' for Sell).
// The order quantity is an integer.
// The CSV file has no error or malformed data.
using namespace std;

// Define Order struct
struct Order {
    char side; // 'B' for Buy, 'S' for Sell
    double price;
    int quantity;
};

// Define Order Book struct
struct OrderBook {
    map<double, int> bids; // Bid prices and their quantities
    map<double, int> asks; // Ask prices and their quantities

    // Function to add an order to the book
    void addOrder(Order order) {
        if (order.side == 'B') {
            bids[order.price] += order.quantity; // Increase bid quantity at price level
        } else if (order.side == 'A') {
            asks[order.price] += order.quantity; // Increase ask quantity at price level
        }
    }

    // Function to remove an order from the book
    void removeOrder(Order order) {
        if (order.side == 'B') {
            bids[order.price] -= order.quantity; // Decrease bid quantity at price level
            if (bids[order.price] == 0) {
                bids.erase(order.price); // Remove price level if quantity becomes 0
            }
        } else if (order.side == 'A') {
            asks[order.price] -= order.quantity; // Decrease ask quantity at price level
            if (asks[order.price] == 0) {
                asks.erase(order.price); // Remove price level if quantity becomes 0
            }
        }
    }

    // Function to print the order book
    void printBook() {
        cout << "BIDS:" << endl;
        for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
            cout << it->first << " " << it->second << endl; // Print bid prices and quantities in descending order
        }
        cout << "ASKS:" << endl;
        for (auto it = asks.begin(); it != asks.end(); ++it) {
            cout << it->first << " " << it->second << endl; // Print ask prices and quantities in ascending order
        }
    }
};

// Function to parse CSV file and update order book
void updateOrderBook(string filename, OrderBook& book) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string timestamp, side, price_str, quantity_str;
        getline(ss, timestamp, ',');
        getline(ss, side, ',');
        getline(ss, price_str, ',');
        getline(ss, quantity_str, ',');
        Order order = { side[0], stod(price_str), stoi(quantity_str) };
        if (timestamp.empty()) {
            book.removeOrder(order); // If timestamp is empty, remove order from book
        } else {
            book.addOrder(order); // Otherwise, add order to book
        }
    }
    file.close();
}

int main() {
    OrderBook book;
    updateOrderBook("orders.csv", book);
    book.printBook();
    return 0;
}
