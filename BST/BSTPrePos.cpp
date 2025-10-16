#include "BST.hpp"
#include <iostream>


struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char d) : data(d), left(nullptr), right(nullptr) {}
};


void preorder(Node* root) {
    if (!root) return;
    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << " ";
}

int main() {
    
    Node* tree1 = new Node('A');
    tree1->left = new Node('B');
    tree1->left->right = new Node('C');

    Node* tree2 = new Node('A');
    tree2->right = new Node('B');
    tree2->right->left = new Node('C');

    std::cout << "Tree 1 Preorder: ";
    preorder(tree1);
    std::cout << "\nTree 1 Postorder: ";
    postorder(tree1);

    std::cout << "\n\nTree 2 Preorder: ";
    preorder(tree2);
    std::cout << "\nTree 2 Postorder: ";
    postorder(tree2);

    std::cout << std::endl;
    return 0;
}