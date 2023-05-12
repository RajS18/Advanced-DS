#include <iostream>
#include <list>
#include <cmath>
//Collision handled by chaining
template <typename KeyType, typename ValueType>
class HashTable {
private:
    std::list<std::pair<KeyType, ValueType>>* table;
    int size;
    int large_prime = 1000000007;
    int hashFunction(KeyType key) {
        return key % size;
    }
    //String Based Hash Functions
    //Universal Hash: This function takes two additional parameters a and b, which are chosen randomly from a large prime number.
    //It then multiplies the sum of the character codes of the key by a, adds b, and takes the remainder of the result divided by a 
    //large prime number. Finally, it takes the remainder of the result divided by the size of the hash table.

    unsigned int hash1(const std::string& key, unsigned int size, unsigned int a, unsigned int b) {
        unsigned int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return ((a * sum + b) % large_prime) % size;
    }
    //Polynomial Hash: This function treats the key as a polynomial with coefficients equal to the character codes of the key. It then evaluates 
    //the polynomial at x = 31 (a prime number) and takes the remainder of the result divided by the size of the hash table.
    
    unsigned int hash2(const std::string& key, unsigned int size) {
        unsigned int sum = 0;
        unsigned int p = 1;
        for (char c : key) {
            sum += c * p;
            p *= 31;  // a prime number
        }
        return sum % size;
    }
    //Multiplication Hash: This function multiplies the sum of the character codes of the key by a constant value A 
    //(which is the inverse of the golden ratio), and takes the fractional part of the result times the size of the hash table.

    unsigned int hash3(const std::string& key, unsigned int size) {
        const double A = 0.6180339887;
        double sum = 0;
        for (char c : key) {
            sum = sum * 256 + c;
        }
        return std::floor(size * std::fmod(sum * A, 1));
    }
    
    //Simple Hash: simply adds up the character codes of the key and takes the remainder of the sum divided by the size of the hash table.
    unsigned int hash4(const std::string& key, unsigned int size) {
        unsigned int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % size;
    }

public:
    HashTable(int tableSize) {
        table = new std::list<std::pair<KeyType, ValueType>>[tableSize];
        size = tableSize;
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(KeyType key, ValueType value) {
        int index = hashFunction(key);
        table[index].push_back(std::make_pair(key, value));
    }

    bool search(KeyType key, ValueType& value) {
        int index = hashFunction(key);
        for (auto itr = table[index].begin(); itr != table[index].end(); ++itr) {
            if (itr->first == key) {
                value = itr->second;
                return true;
            }
        }
        return false;
    }

    bool remove(KeyType key) {
        int index = hashFunction(key);
        for (auto itr = table[index].begin(); itr != table[index].end(); ++itr) {
            if (itr->first == key) {
                table[index].erase(itr);
                return true;
            }
        }
        return false;
    }
};

int main() {
    HashTable<int, std::string> myHashTable(10);

    myHashTable.insert(5, "hello");
    myHashTable.insert(15, "world");
    myHashTable.insert(25, "foo");
    myHashTable.insert(35, "bar");

    std::string value;
    if (myHashTable.search(25, value)) {
        std::cout << "Value found: " << value << std::endl;
    } else {
        std::cout << "Value not found" << std::endl;
    }

    if (myHashTable.remove(35)) {
        std::cout << "Key removed" << std::endl;
    } else {
        std::cout << "Key not found" << std::endl;
    }

    return 0;
}
