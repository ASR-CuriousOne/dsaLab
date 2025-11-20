#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

namespace ASR {

struct Node {
    int numKeys;
    int keys[3];
    Node* children[4];
    Node* parent;
    bool isLeaf;

    Node(bool leaf, Node* p = nullptr) : numKeys(0), parent(p), isLeaf(leaf) {
        for (int i = 0; i < 4; ++i) {
            children[i] = nullptr;
        }
    }

    int findKeyIndex(int x) {
        int i = 0;
        while (i < numKeys && keys[i] < x) {
            i++;
        }
        return i;
    }

    void removeFromLeaf(int index) {
        for (int i = index; i < numKeys - 1; ++i) {
            keys[i] = keys[i + 1];
        }
        numKeys--;
    }

    void removeFromInternal(int index) {
        removeFromLeaf(index);
    }
};

class Tree234 {
private:
    Node* root;

    void clear(Node* node) {
        if (node) {
            if (!node->isLeaf) {
                for (int i = 0; i <= node->numKeys; ++i) {
                    clear(node->children[i]);
                }
            }
            delete node;
        }
    }

    void splitChild(Node* parent, int childIndex) {
        Node* child = parent->children[childIndex];
        Node* newSibling = new Node(child->isLeaf, parent);
        
        newSibling->numKeys = 1;
        newSibling->keys[0] = child->keys[2];

        if (!child->isLeaf) {
            newSibling->children[0] = child->children[2];
            newSibling->children[1] = child->children[3];
            if(newSibling->children[0]) newSibling->children[0]->parent = newSibling;
            if(newSibling->children[1]) newSibling->children[1]->parent = newSibling;
        }

        child->numKeys = 1;

        for (int j = parent->numKeys; j > childIndex; j--) {
            parent->children[j + 1] = parent->children[j];
        }
        parent->children[childIndex + 1] = newSibling;

        for (int j = parent->numKeys - 1; j >= childIndex; j--) {
            parent->keys[j + 1] = parent->keys[j];
        }
        
        parent->keys[childIndex] = child->keys[1];
        parent->numKeys++;
    }

    void insertNonFull(Node* node, int x) {
        int i = node->findKeyIndex(x);

        if (node->isLeaf) {
            for (int j = node->numKeys; j > i; j--) {
                node->keys[j] = node->keys[j - 1];
            }
            node->keys[i] = x;
            node->numKeys++;
        } else {
            if (node->children[i]->numKeys == 3) {
                splitChild(node, i);
                
                if (x > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], x);
        }
    }

    int findMin(Node* node) {
        while (!node->isLeaf) {
            node = node->children[0];
        }
        return node->keys[0];
    }

    int findMax(Node* node) {
        while (!node->isLeaf) {
            node = node->children[node->numKeys];
        }
        return node->keys[node->numKeys - 1];
    }

    void borrowFromLeft(Node* parent, int childIndex) {
        Node* child = parent->children[childIndex];
        Node* leftSib = parent->children[childIndex - 1];

        for (int i = child->numKeys; i > 0; --i) {
            child->keys[i] = child->keys[i - 1];
        }
        if (!child->isLeaf) {
            for (int i = child->numKeys + 1; i > 0; --i) {
                child->children[i] = child->children[i - 1];
            }
        }

        child->keys[0] = parent->keys[childIndex - 1];
        
        if (!child->isLeaf) {
            child->children[0] = leftSib->children[leftSib->numKeys];
            if(child->children[0]) child->children[0]->parent = child;
        }

        parent->keys[childIndex - 1] = leftSib->keys[leftSib->numKeys - 1];

        child->numKeys++;
        leftSib->numKeys--;
    }

    void borrowFromRight(Node* parent, int childIndex) {
        Node* child = parent->children[childIndex];
        Node* rightSib = parent->children[childIndex + 1];

        child->keys[child->numKeys] = parent->keys[childIndex];

        if (!child->isLeaf) {
            child->children[child->numKeys + 1] = rightSib->children[0];
            if(child->children[child->numKeys + 1]) 
                child->children[child->numKeys + 1]->parent = child;
        }

        parent->keys[childIndex] = rightSib->keys[0];

        for (int i = 0; i < rightSib->numKeys - 1; ++i) {
            rightSib->keys[i] = rightSib->keys[i + 1];
        }
        if (!rightSib->isLeaf) {
            for (int i = 0; i < rightSib->numKeys; ++i) {
                rightSib->children[i] = rightSib->children[i + 1];
            }
        }

        child->numKeys++;
        rightSib->numKeys--;
    }

    void mergeChildren(Node* parent, int i) {
        Node* leftChild = parent->children[i];
        Node* rightChild = parent->children[i + 1];

        leftChild->keys[leftChild->numKeys] = parent->keys[i];
        
        for (int j = 0; j < rightChild->numKeys; ++j) {
            leftChild->keys[leftChild->numKeys + 1 + j] = rightChild->keys[j];
        }

        if (!leftChild->isLeaf) {
            for (int j = 0; j <= rightChild->numKeys; ++j) {
                leftChild->children[leftChild->numKeys + 1 + j] = rightChild->children[j];
                if(leftChild->children[leftChild->numKeys + 1 + j])
                    leftChild->children[leftChild->numKeys + 1 + j]->parent = leftChild;
            }
        }

        leftChild->numKeys += 1 + rightChild->numKeys;

        for (int j = i; j < parent->numKeys - 1; ++j) {
            parent->keys[j] = parent->keys[j + 1];
        }
        for (int j = i + 1; j < parent->numKeys; ++j) {
            parent->children[j] = parent->children[j + 1];
        }
        
        parent->numKeys--;
        delete rightChild;
    }

    void fixDeficientChild(Node* node, int childIndex) {
        Node* child = node->children[childIndex];
        
        if (child->numKeys > 1) return;

        if (childIndex > 0 && node->children[childIndex - 1]->numKeys > 1) {
            borrowFromLeft(node, childIndex);
        }
        else if (childIndex < node->numKeys && node->children[childIndex + 1]->numKeys > 1) {
            borrowFromRight(node, childIndex);
        }
        else {
            if (childIndex > 0) {
                mergeChildren(node, childIndex - 1);
            } else {
                mergeChildren(node, childIndex);
            }
        }
    }

    void deleteInternal(Node* node, int x) {
        int i = node->findKeyIndex(x);

        if (i < node->numKeys && node->keys[i] == x) {
            if (node->isLeaf) {
                node->removeFromLeaf(i);
            } else {
                Node* leftChild = node->children[i];
                Node* rightChild = node->children[i + 1];

                if (leftChild->numKeys > 1) {
                    int predecessor = findMax(leftChild);
                    node->keys[i] = predecessor;
                    deleteInternal(leftChild, predecessor);
                } else if (rightChild->numKeys > 1) {
                    int successor = findMin(rightChild);
                    node->keys[i] = successor;
                    deleteInternal(rightChild, successor);
                } else {
                    mergeChildren(node, i);
                    deleteInternal(node->children[i], x);
                }
            }
        } 
        else {
            if (node->isLeaf) {
                return;
            }

            bool wasMerged = (i > 0 && node->children[i]->numKeys == 1 && node->children[i-1]->numKeys == 1) ||
                             (i < node->numKeys && node->children[i]->numKeys == 1 && node->children[i+1]->numKeys == 1);

            fixDeficientChild(node, i);

            if (wasMerged && i > 0 && node->children[i-1]->findKeyIndex(x) <= node->children[i-1]->numKeys) {
                 deleteInternal(node->children[i-1], x);
            } else {
                 deleteInternal(node->children[i], x);
            }
        }
    }

    void printInOrderRecursive(Node* node) {
        if (!node) return;

        if (node->isLeaf) {
            for (int i = 0; i < node->numKeys; ++i) {
                std::cout << node->keys[i] << " ";
            }
        } else {
            printInOrderRecursive(node->children[0]);
            for (int i = 0; i < node->numKeys; ++i) {
                std::cout << node->keys[i] << " ";
                printInOrderRecursive(node->children[i + 1]);
            }
        }
    }

    Node* bulkLoadRecursive(const std::vector<int>& A, int start, int end, Node* p) {
        int n = end - start + 1;
        if (n <= 0) return nullptr;

        Node* node = new Node(false, p);

        if (n <= 3) {
            node->isLeaf = true;
            for (int i = 0; i < n; ++i) {
                node->keys[i] = A[start + i];
            }
            node->numKeys = n;
            return node;
        }

        int k; 
        int m; 

        if (n == 4) {
            k = 1; 
        } else if (n <= 6) { 
            k = 2; 
        } else { 
            k = 3; 
        }
        m = k + 1;
        
        int n_items_for_children = n - k;
        int child_base_size = n_items_for_children / m;
        int remainder = n_items_for_children % m;

        std::vector<int> child_sizes(m, child_base_size);
        for (int i = 0; i < remainder; ++i) {
            child_sizes[i]++;
        }

        int current_idx = start;
        for (int i = 0; i < m; ++i) {
            int child_end = current_idx + child_sizes[i] - 1;
            node->children[i] = bulkLoadRecursive(A, current_idx, child_end, node);
            current_idx += child_sizes[i];

            if (i < k) {
                node->keys[i] = A[current_idx];
                current_idx++;
            }
        }
        
        node->numKeys = k;
        return node;
    }


public:
    Tree234() : root(nullptr) {}
    ~Tree234() { clear(root); }

    void find(int x) {
        Node* node = root;
        while (node != nullptr) {
            int i = node->findKeyIndex(x);
            
            if (i < node->numKeys && node->keys[i] == x) {
                std::cout << "FOUND" << std::endl;
                return;
            }
            if (node->isLeaf) {
                std::cout << "NOTFOUND" << std::endl;
                return;
            }
            node = node->children[i];
        }
        std::cout << "NOTFOUND" << std::endl;
    }

    void insert(int x) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys[0] = x;
            root->numKeys = 1;
            return;
        }

        if (root->numKeys == 3) {
            Node* newRoot = new Node(false);
            newRoot->children[0] = root;
            root->parent = newRoot;
            splitChild(newRoot, 0);
            root = newRoot;
        }
        
        insertNonFull(root, x);
    }

    void deleteKey(int x) {
        if (!root) return;

        if (root->numKeys == 1 && !root->isLeaf &&
            root->children[0]->numKeys == 1 && root->children[1]->numKeys == 1) 
        {
            mergeChildren(root, 0);
            Node* oldRoot = root;
            root = root->children[0];
            root->parent = nullptr;
            delete oldRoot;
        }

        deleteInternal(root, x);

        if (root->numKeys == 0 && !root->isLeaf) {
            Node* oldRoot = root;
            root = root->children[0];
            if(root) root->parent = nullptr;
            delete oldRoot;
        }
    }

    void printLevel() {
        if (root == nullptr) {
            std::cout << "EMPTY" << std::endl;
            return;
        }

        std::queue<Node*> q;
        q.push(root);
        q.push(nullptr);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr == nullptr) {
                std::cout << std::endl;
                if (!q.empty()) {
                    q.push(nullptr);
                }
            } else {
                std::cout << "[";
                for (int i = 0; i < curr->numKeys; ++i) {
                    std::cout << curr->keys[i];
                    if (i < curr->numKeys - 1) std::cout << " ";
                }
                std::cout << "] ";

                if (!curr->isLeaf) {
                    for (int i = 0; i <= curr->numKeys; ++i) {
                        if (curr->children[i]) {
                            q.push(curr->children[i]);
                        }
                    }
                }
            }
        }
    }

    void printIn() {
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }
        printInOrderRecursive(root);
        std::cout << std::endl;
    }

    void bulkLoad(const std::vector<int>& sortedKeys) {
        clear(root);
        root = bulkLoadRecursive(sortedKeys, 0, sortedKeys.size() - 1, nullptr);
    }
};

}
