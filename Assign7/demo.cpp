#include <iostream>
#include <sstream>
#include "avl.hpp"

int main() {

    ASR::AvlTree tree;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "INSERT") {
            int x;
            ss >> x;
            tree.insertKey(x);
        } else if (command == "DELETE") {
            int x;
            ss >> x;
            tree.removeKey(x);
        } else if (command == "FIND") {
            int x;
            ss >> x;
            std::cout << (tree.findKey(x) ? "FOUND" : "NOTFOUND") << "\n";
        } else if (command == "PREV") {
            int x;
            ss >> x;
            tree.findPrev(x);
        } else if (command == "NEXT") {
            int x;
            ss >> x;
            tree.findNext(x);
        } else if (command == "PRINT") {
            std::string type;
            ss >> type;
            tree.printTree(type);
        } else if (command == "RANGE_COUNT") {
            int l, r;
            ss >> l >> r;
            tree.rangeCount(l, r);
        } else if (command == "RANK") {
            int x;
            ss >> x;
            tree.findRank(x);
        } else if (command == "SELECT") {
            int k;
            ss >> k;
            tree.selectKey(k);
        } else if (command == "RANGE_SUM") {
            int l, r;
            ss >> l >> r;
            tree.rangeSum(l, r);
        } else if (command == "EXIT"){
            return 0;

        }
        std::cout << std::endl;
    }

    return -1;
}
