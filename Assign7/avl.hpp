#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

namespace ASR {

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    int size;
    long long sum;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1), size(1), sum(k) {}
};

class AvlTree {
private:
    Node *root;

    int getHeight(Node *n) {
        return n ? n->height : 0;
    }

    int getBalance(Node *n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        updateNode(y);
        updateNode(x);

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *t2 = y->left;

        y->left = x;
        x->right = t2;

        updateNode(x);
        updateNode(y);

        return y;
    }

    int getSize(Node *n) {
        return n ? n->size : 0;
    }
    
    long long getSum(Node *n) {
        return n ? n->sum : 0LL;
    }

    void updateNode(Node *n) {
        if (n) {
            n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
            n->size = 1 + getSize(n->left) + getSize(n->right);
            n->sum = n->key + getSum(n->left) + getSum(n->right);
        }
    }

    Node *findMin(Node *node) {
        Node *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *insertNode(Node *node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        updateNode(node);
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *removeNode(Node *node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->key)
            node->left = removeNode(node->left, key);
        else if (key > node->key)
            node->right = removeNode(node->right, key);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node *temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node *temp = findMin(node->right);
                node->key = temp->key;
                node->right = removeNode(node->right, temp->key);
            }
        }

        if (node == nullptr)
            return node;

        updateNode(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void printIn(Node *node, std::vector<int> &keys) {
        if (node == nullptr) return;
        printIn(node->left, keys);
        keys.push_back(node->key);
        printIn(node->right, keys);
    }

    void printPre(Node *node, std::vector<int> &keys) {
        if (node == nullptr) return;
        keys.push_back(node->key);
        printPre(node->left, keys);
        printPre(node->right, keys);
    }

    void printPost(Node *node, std::vector<int> &keys) {
        if (node == nullptr) return;
        printPost(node->left, keys);
        printPost(node->right, keys);
        keys.push_back(node->key);
    }

    void printLevel(Node *node, std::vector<int> &keys) {
        if (node == nullptr) return;
        std::queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            keys.push_back(current->key);
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    void clearTree(Node *node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
    
    int countLe(Node *node, int k) {
        int count = 0;
        Node *current = node;
        while (current) {
            if (current->key == k) {
                count += getSize(current->left) + 1;
                break;
            } else if (current->key > k) {
                current = current->left;
            } else {
                count += getSize(current->left) + 1;
                current = current->right;
            }
        }
        return count;
    }

    int countLt(Node *node, int k) {
        int count = 0;
        Node *current = node;
        while (current) {
            if (current->key == k) {
                count += getSize(current->left);
                break;
            } else if (current->key > k) {
                current = current->left;
            } else {
                count += getSize(current->left) + 1;
                current = current->right;
            }
        }
        return count;
    }
    
    int select(Node* node, int k) {
        int rankOfRoot = getSize(node->left) + 1;

        if (k == rankOfRoot)
            return node->key;
        if (k < rankOfRoot)
            return select(node->left, k);
        else
            return select(node->right, k - rankOfRoot);
    }
    
    long long sumLe(Node *node, int k) {
        long long totalSum = 0LL;
        Node *current = node;
        while (current) {
            if (current->key == k) {
                totalSum += getSum(current->left) + current->key;
                break;
            } else if (current->key > k) {
                current = current->left;
            } else {
                totalSum += getSum(current->left) + current->key;
                current = current->right;
            }
        }
        return totalSum;
    }

    long long sumLt(Node *node, int k) {
        long long totalSum = 0LL;
        Node *current = node;
        while (current) {
            if (current->key == k) {
                totalSum += getSum(current->left);
                break;
            } else if (current->key > k) {
                current = current->left;
            } else {
                totalSum += getSum(current->left) + current->key;
                current = current->right;
            }
        }
        return totalSum;
    }

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        clearTree(root);
    }

    void insertKey(int key) {
        root = insertNode(root, key);
    }

    void removeKey(int key) {
        root = removeNode(root, key);
    }

    bool findKey(int key) {
        if (findKeyRecursive(root, key))
            return true;
        else
            return false;
    }
    
    bool findKeyRecursive(Node *node, int key) {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return findKeyRecursive(node->left, key);
        else
            return findKeyRecursive(node->right, key);
    }

    void findPrev(int key) {
        Node *current = root;
        Node *predecessor = nullptr;
        while (current) {
            if (current->key < key) {
                predecessor = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        if (predecessor)
            std::cout << predecessor->key << std::endl;
        else
            std::cout << "NONE" << std::endl;
    }

    void findNext(int key) {
        Node *current = root;
        Node *successor = nullptr;
        while (current) {
            if (current->key > key) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (successor)
            std::cout << successor->key << std::endl;
        else
            std::cout << "NONE" << std::endl;
    }

    void printTree(const std::string &order) {
        if (root == nullptr) {
            std::cout << "EMPTY" << std::endl;
            return;
        }

        std::vector<int> keys;
        if (order == "IN") printIn(root, keys);
        else if (order == "PRE") printPre(root, keys);
        else if (order == "POST") printPost(root, keys);
        else if (order == "LEVEL") printLevel(root, keys);

        for (size_t i = 0; i < keys.size(); ++i) {
            std::cout << keys[i] << (i == keys.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    void rangeCount(int l, int r) {
        int countR = countLe(root, r);
        int countL = countLt(root, l);
        std::cout << (countR - countL) << std::endl;
    }
    
    void findRank(int x) {
        std::cout << countLt(root, x) << std::endl;
    }
    
    void selectKey(int k) {
        if (k < 1 || k > getSize(root)) {
            std::cout << "INVALID" << std::endl;
            return;
        }
        std::cout << select(root, k) << std::endl;
    }
    
    void rangeSum(int l, int r) {
        long long sumR = sumLe(root, r);
        long long sumL = sumLt(root, l);
        std::cout << (sumR - sumL) << std::endl;
    }
};

}