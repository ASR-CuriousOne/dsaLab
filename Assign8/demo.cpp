#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Include the 2-3-4 Tree class definition
#include "Tree234.hpp"

// Use the namespace defined in the header
using namespace ASR;

int main() {
    // Use the new class name
    ASR::Tree234 tree;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "INSERT") {
            int x;
            while (ss >> x) {
                tree.insert(x);
            }
        } else if (command == "DELETE") {
            int x;
            ss >> x;
            tree.deleteKey(x);
        } else if (command == "FIND") {
            int x;
            ss >> x;
            tree.find(x);
        } else if (command == "PRINT") {
            std::string type;
            ss >> type;
            if (type == "LEVEL") {
                tree.printLevel();
            } else if (type == "IN") {
                tree.printIn();
            }
        } else if (command == "BULK") {
            int n;
            ss >> n;
            std::vector<int> keys(n);
            for (int i = 0; i < n; ++i) {
                ss >> keys[i];
            }
            tree.bulkLoad(keys);
        }
    }

    return 0;
}