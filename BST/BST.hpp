#pragma once
#include <iostream>
#include <ostream>
#include <stack>
#include <queue>
#include <map>
#include <functional>

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

enum Order { InOrder, PreOrder, PostOrder, LevelOrder };

template <typename T> class BST {
  Node<T> *root = nullptr;

public:
  BST() : root(nullptr) {}

  void constructFromInorderPreorder(const std::vector<T> &inorder,const std::vector<T> &preorder) {
    if (inorder.size() != preorder.size() || inorder.empty()) {
      std::cerr << "Invalid Input" << std::endl;
      return;
    }

    std::map<T, int> inorderMap;
    for (int i = 0; i < inorder.size(); i++) {
      inorderMap[inorder[i]] = i;
    }

    std::stack<Node<T> *> s;
    root = new Node<T>(preorder[0]);
    s.push(root);
    int inorderIndex = 0;

    for (int i = 1; i < preorder.size(); i++) {
      T currentValue = preorder[i];
      Node<T> *node = s.top();

      if (inorderMap[node->data] != inorderIndex) {
        node->left = new Node<T>(currentValue);
        s.push(node->left);
      } else {
        while (!s.empty() && inorderMap[s.top()->data] == inorderIndex) {
          node = s.top();
          s.pop();
          inorderIndex++;
        }
        node->right = new Node<T>(currentValue);
        s.push(node->right);
      }
    }
    
  }

  void constructFromInorderPostorder(const std::vector<T> &inorder,const std::vector<T> &postorder) {
    if (inorder.size() != postorder.size() || inorder.empty()) {
      std::cerr << "Invalid Input" << std::endl;
      return;
    }

    std::map<T, int> inorderMap;
    for (int i = 0; i < inorder.size(); i++) {
      inorderMap[inorder[i]] = i;
    }

    std::stack<Node<T> *> s;
    root = new Node<T>(postorder.back());
    s.push(root);
    int inorderIndex = inorder.size() - 1;

    for (int i = postorder.size() - 2; i >= 0; i--) {
      T currentValue = postorder[i];
      Node<T> *node = s.top();

      if (inorderMap[node->data] != inorderIndex) {
        node->right = new Node<T>(currentValue);
        s.push(node->right);
      } else {
        while (!s.empty() && inorderMap[s.top()->data] == inorderIndex) {
          node = s.top();
          s.pop();
          inorderIndex--;
        }
        node->left = new Node<T>(currentValue);
        s.push(node->left);
      }
    }
    
  }

  void insert(T key) {
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
   	else if(order == Order::PreOrder) {
      while (curr != nullptr || !dfs.empty()) {
        while (curr != nullptr) {
          std::cout << curr->data << ' ';
          dfs.push(curr);
          curr = curr->left;
        }
        curr = dfs.top();
        dfs.pop();
        curr = curr->right;
      }
    }
    else if(order == Order::LevelOrder) {
      std::queue<Node<T>*> bfs;
      bfs.push(root);
      while(!bfs.empty()){
        Node<T>* temp = bfs.front();
        bfs.pop();
        std::cout << temp->data << ' ';
        if(temp->left != nullptr)
          bfs.push(temp->left);
        if(temp->right != nullptr)
          bfs.push(temp->right);
      }
    }
    

    std::cout << std::endl;
  }

  bool search(T key, Node<T> *node = nullptr) {
    if (root == nullptr) {
      std::cerr << "Tree Empty" << std::endl;
      return false;
    }

    Node<T> *temp = root;

    while (temp != nullptr) {
      if (temp->data == key) {
        node = temp;
        return true;
      } else if (temp->data < key) {
        temp = temp->right;
      } else {
        temp = temp->left;
      }
    }

    return false;
  }

  void remove(T key){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return;
    }

    Node<T>* temp = root;
    Node<T>* parent = nullptr;
    while(temp != nullptr && temp->data != key){
      parent = temp;
      if(temp->data < key)
        temp = temp->right;
      else
        temp = temp->left;
    }

    if(temp == nullptr){
      std::cerr << "Key not found in the tree!!!" << std::endl;
      return;
    }

    if(temp->left == nullptr && temp->right == nullptr){
      if(parent == nullptr){
        delete root;
        root = nullptr;
      }
      else if(parent->left == temp){
        delete parent->left;
        parent->left = nullptr;
      }
      else{
        delete parent->right;
        parent->right = nullptr;
      }
    }
    else if(temp->left == nullptr || temp->right == nullptr){
      Node<T>* child = (temp->left != nullptr) ? temp->left : temp->right;
      if(parent == nullptr){
        delete root;
        root = child;
      }
      else if(parent->left == temp){
        delete parent->left;
        parent->left = child;
      }
      else{
        delete parent->right;
        parent->right = child;
      }
    }
    else{
      Node<T>* succParent = temp;
      Node<T>* succ = temp->right;
      while(succ->left != nullptr){
        succParent = succ;
        succ = succ->left;
      }
      temp->data = succ->data;
      if(succParent->left == succ){
        succParent->left = succ->right;
      }
      else{
        succParent->right = succ->right;
      }
      delete succ;
    }


  }

  T getMax(){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return T();
    }

    Node<T>* temp = root;
    while(temp->right != nullptr){
      temp = temp->right;
    }
    return temp->data;
  }

  T getMin(){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return T();
    }

    Node<T>* temp = root;
    while(temp->left != nullptr){
      temp = temp->left;
    }
    return temp->data;
  }

  T getSuccessor(T key){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return T();
    }

    Node<T>* temp = root;
    Node<T>* succ = nullptr;
    while(temp != nullptr){
      if(temp->data == key){
        break;
      }
      else if(temp->data < key){
        temp = temp->right;
      }
      else{
        succ = temp;
        temp = temp->left;
      }
    }

    if(temp == nullptr){
      std::cerr << "Key not found in the tree!!!" << std::endl;
      return T();
    }

    if(temp->right != nullptr){
      Node<T>* curr = temp->right;
      while(curr->left != nullptr){
        curr = curr->left;
      }
      succ = curr;
    }

    if(succ == nullptr){
      std::cerr << "No Successor found!!!" << std::endl;
      return T();
    }

    return succ->data;
  }

  void printDepths(){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return;
    }

    std::stack<std::pair<Node<T>*, int>> dfs;
    Node<T>* curr = root;
    int depth = 0;

    while(curr != nullptr || !dfs.empty()){
      while(curr != nullptr){
        dfs.push({curr, depth});
        curr = curr->left;
        depth++;
      }
      auto [node, d] = dfs.top();
      dfs.pop();
      std::cout << node->data << " : " << d << " , ";
      curr = node->right;
      depth = d + 1;
    }
    std::cout << std::endl;
  }
  
  void printHeights(){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return;
    }
    
    std::stack<Node<T>*> s1, s2;
    std::map<Node<T>*, int> heights;

    s1.push(root);
    while (!s1.empty()) {
        Node<T>* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) {
            s1.push(current->left);
        }
        if (current->right) {
            s1.push(current->right);
        }
    }

    while (!s2.empty()) {
        Node<T>* current = s2.top();
        s2.pop();

        int leftHeight = (current->left) ? heights[current->left] : -1;
        int rightHeight = (current->right) ? heights[current->right] : -1;

        int currentHeight = 1 + std::max(leftHeight, rightHeight);

        heights[current] = currentHeight;
        std::cout << current->data << " : " << currentHeight << " , ";
    }
    std::cout << std::endl; 
    
  }

  void deleteTree(){
    if (root == nullptr)
      return;

    std::stack<Node<T> *> dfs;
    dfs.push(root);

    while (!dfs.empty()) {
      Node<T> *temp = dfs.top();
      dfs.pop();

      if (temp->left != nullptr)
        dfs.push(temp->left);
      if (temp->right != nullptr)
        dfs.push(temp->right);

      delete temp;
    }

    root = nullptr; 
  }

  bool isBalanced(){
    if(root == nullptr){
      return true;
    }

    std::stack<Node<T>*> s1, s2;
    std::map<Node<T>*, int> heights;

    s1.push(root);
    while (!s1.empty()) {
        Node<T>* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) {
            s1.push(current->left);
        }
        if (current->right) {
            s1.push(current->right);
        }
    }

    while (!s2.empty()) {
        Node<T>* current = s2.top();
        s2.pop();

        int leftHeight = (current->left) ? heights[current->left] : -1;
        int rightHeight = (current->right) ? heights[current->right] : -1;

        if(std::abs(leftHeight - rightHeight) > 1){
          return false;
        }

        int currentHeight = 1 + std::max(leftHeight, rightHeight);

        heights[current] = currentHeight;
    }

    return true;    
  }

  Node<T>* getLowestCommmonAncestor(T val1, T val2){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return nullptr;
    }

    Node<T>* temp = root;
    while(temp != nullptr){
      if(temp->data > val1 && temp->data > val2){
        temp = temp->left;
      }
      else if(temp->data < val1 && temp->data < val2){
        temp = temp->right;
      }
      else{
        return temp;
      }
    }

    return nullptr;
  }

  int getDiameter(){
    if(root == nullptr){
      return 0;
    }

    int diameter = 0;
    std::function<int(Node<T>*)> height = [&](Node<T>* node) -> int {
      if(node == nullptr){
        return 0;
      }
      int leftHeight = height(node->left);
      int rightHeight = height(node->right);
      diameter = std::max(diameter, leftHeight + rightHeight);
      return 1 + std::max(leftHeight, rightHeight);
    };

    height(root);
    return diameter;
  }
  
  void serializePreOrder(){
    if(root == nullptr){
      std::cerr << "Tree Empty" << std::endl;
      return;
    }

    std::stack<Node<T>*> s;
    s.push(root);

    while(!s.empty()){
      Node<T>* temp = s.top();
      s.pop();

      if(temp == nullptr){
        std::cout << "# ";
        continue;
      }

      std::cout << temp->data << ' ';
      s.push(temp->right);
      s.push(temp->left);
    }

    std::cout << std::endl;
  }

  ~BST() {
    deleteTree();
  }

};
}