#include <iostream>
#include <string>
#include <vector>
#include <sstream>
int main() {
    std::string input = "This is a test string.";
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(input);
    while (iss >> token) {
        tokens.push_back(token);
    }
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }
    return 0;
}
