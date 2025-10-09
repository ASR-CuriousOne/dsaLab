#pragma once
#include <iostream>
#include <ostream>
#include <stack>

namespace ASR {
template <typename T> struct Node {
  T data;
  Node *left = nullptr;
  Node *right = nullptr;

  Node() = default;
  Node(T data) : data(data), left(nullptr), right(nullptr) {}
  Node(T data, Node<T> *left, Node<T> *right)
      : data(data), left(left), right(right) {}
};

enum Order { InOrder, PreOrder, PostOrder };

template <typename T> class BST {
  Node<T> *root = nullptr;

public:
  BST() : root(nullptr) {}

  void Insert(T key) {
    if (root == nullptr) {
      root = new Node<T>(key);
      return;
    }

    Node<T> *temp = root;

    while (true) {
      if (temp->data < key) {
        if (temp->right == nullptr) {
          temp->right = new Node<T>(key);
          break;
        }
        temp = temp->right;
      } else if (temp->data > key) {
        if (temp->left == nullptr) {
          temp->left = new Node<T>(key);
          break;
        }
        temp = temp->left;
      } else {
        std::cerr << "Key already exists in the tree!!!" << std::endl;
        break;
      }
    }
  }

  void print(Order order = Order::InOrder) {
    if (root == nullptr) {
      std::cerr << "Tree Empty" << std::endl;
      return;
    }
    std::stack<Node<T> *> dfs;

    Node<T> *curr = root;

    
    if(order == Order::InOrder) {
      while (curr != nullptr || !dfs.empty()) {
        while (curr != nullptr) {
          dfs.push(curr);
          curr = curr->left;
        }
        curr = dfs.top();
        dfs.pop();
        std::cout << curr->data << ' ';
        curr = curr->right;
      }
    }
		else if(order == Order::PostOrder) {
			while(true){
				while(curr != nullptr){
					dfs.push(curr);
					dfs.push(curr);
					curr = curr->left;
				}
				if(dfs.empty())
					break;
				curr = dfs.top(); dfs.pop();
				if(!dfs.empty() && dfs.top() == curr){
					curr = curr->right;
				}
				else{
					std::cout << curr->data << ' ';
					curr = nullptr;
				}
			}									
    }
   	else if(order == Order::PreOrder) {
			
      while (curr != nullptr || !dfs.empty()) {
        if (curr != nullptr) {
          dfs.push(curr);
          curr = curr->left;
        } else {
          Node<T> *temp = dfs.top()->right;
          if (temp == nullptr) {
            temp = dfs.top();
            dfs.pop();
            std::cout << temp->data << ' ';
            while (!dfs.empty() && temp == (dfs.top())->right) {
              temp = dfs.top();
              dfs.pop();
              std::cout << temp->data << ' ';
            }
          } else {
            curr = temp;
          }
        }
      }
    }
    

    std::cout << std::endl;
  }
};
} // namespace ASR
