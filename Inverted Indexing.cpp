#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

// function to tokenize a string into individual terms
vector<string> tokenize(string str) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    // initialize hash table for inverted index
    unordered_map<string, vector<int>> invertedIndex;

    // read in documents from file
    ifstream inFile("documents.txt");
    string line;
    int docID = 0;
    while (getline(inFile, line)) {
        // tokenize the document into individual terms
        vector<string> terms = tokenize(line);
        docID++;

        // add each term to the inverted index and associate it with the document ID
        for (string term : terms) {
            invertedIndex[term].push_back(docID);
        }
    }

    // print out the inverted index
    for (auto entry : invertedIndex) {
        cout << entry.first << ": ";
        for (int docID : entry.second) {
            cout << docID << " ";
        }
        cout << endl;
    }

    return 0;
}
