#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Dict.hpp"

// Use the namespace defined in the header
using namespace ASR;

int main() {
    // Use the new class name
    Dict tree;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "PUT") {
            int key, val;
            ss >> key >> val;
            tree.put(key, val);
        } else if (command == "GET") {
            int key;
            ss >> key;
            tree.get(key);
        } else if (command == "RANGE") {
            int L, R;
            ss >> L >> R;
            tree.range(L, R);
        } else if (command == "BATCH_DELETE") {
            int m;
            ss >> m;
            std::vector<int> keys(m);
            for (int i = 0; i < m; ++i) {
                ss >> keys[i];
            }
            tree.batchDelete(keys);
        }
    }

    return 0;
}