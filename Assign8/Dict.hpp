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
    int values[3]; 
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


    void removeKey(int index) {
        for (int i = index; i < numKeys - 1; ++i) {
            keys[i] = keys[i + 1];
            values[i] = values[i + 1]; 
        }
        numKeys--;
    }
};

class Dict {
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
        newSibling->values[0] = child->values[2]; 

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
            parent->values[j + 1] = parent->values[j]; 
        }
        
        parent->keys[childIndex] = child->keys[1];
        parent->values[childIndex] = child->values[1]; 
        parent->numKeys++;
    }

    void insertNonFull(Node* node, int x, int val) {
        int i = node->findKeyIndex(x);

        if (node->isLeaf) {
            for (int j = node->numKeys; j > i; j--) {
                node->keys[j] = node->keys[j - 1];
                node->values[j] = node->values[j - 1]; 
            }
            node->keys[i] = x;
            node->values[i] = val; 
            node->numKeys++;
        } else {
            if (node->children[i]->numKeys == 3) {
                splitChild(node, i);
                if (x > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], x, val); 
        }
    }

    Node* findMaxNode(Node* node) {
        while (!node->isLeaf) {
            node = node->children[node->numKeys];
        }
        return node;
    }

    Node* findMinNode(Node* node) {
        while (!node->isLeaf) {
            node = node->children[0];
        }
        return node;
    }

    void borrowFromLeft(Node* parent, int childIndex) {
        Node* child = parent->children[childIndex];
        Node* leftSib = parent->children[childIndex - 1];

        for (int i = child->numKeys; i > 0; --i) {
            child->keys[i] = child->keys[i - 1];
            child->values[i] = child->values[i - 1];
        }
        if (!child->isLeaf) {
            for (int i = child->numKeys + 1; i > 0; --i) {
                child->children[i] = child->children[i - 1];
            }
        }

        child->keys[0] = parent->keys[childIndex - 1];
        child->values[0] = parent->values[childIndex - 1];
        
        if (!child->isLeaf) {
            child->children[0] = leftSib->children[leftSib->numKeys];
            if(child->children[0]) child->children[0]->parent = child;
        }

        parent->keys[childIndex - 1] = leftSib->keys[leftSib->numKeys - 1];
        parent->values[childIndex - 1] = leftSib->values[leftSib->numKeys - 1];

        child->numKeys++;
        leftSib->numKeys--;
    }

    void borrowFromRight(Node* parent, int childIndex) {
        Node* child = parent->children[childIndex];
        Node* rightSib = parent->children[childIndex + 1];

        child->keys[child->numKeys] = parent->keys[childIndex];
        child->values[child->numKeys] = parent->values[childIndex];

        if (!child->isLeaf) {
            child->children[child->numKeys + 1] = rightSib->children[0];
            if(child->children[child->numKeys + 1]) 
                child->children[child->numKeys + 1]->parent = child;
        }

        parent->keys[childIndex] = rightSib->keys[0];
        parent->values[childIndex] = rightSib->values[0];

        for (int i = 0; i < rightSib->numKeys - 1; ++i) {
            rightSib->keys[i] = rightSib->keys[i + 1];
            rightSib->values[i] = rightSib->values[i + 1];
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
        leftChild->values[leftChild->numKeys] = parent->values[i];
        
        for (int j = 0; j < rightChild->numKeys; ++j) {
            leftChild->keys[leftChild->numKeys + 1 + j] = rightChild->keys[j];
            leftChild->values[leftChild->numKeys + 1 + j] = rightChild->values[j];
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
            parent->values[j] = parent->values[j + 1];
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
            if (childIndex > 0) mergeChildren(node, childIndex - 1);
            else mergeChildren(node, childIndex);
        }
    }

    void deleteInternal(Node* node, int x) {
        int i = node->findKeyIndex(x);

        if (i < node->numKeys && node->keys[i] == x) {
            if (node->isLeaf) {
                node->removeKey(i);
            } else {
                Node* leftChild = node->children[i];
                Node* rightChild = node->children[i + 1];

                if (leftChild->numKeys > 1) {
                    Node* predNode = findMaxNode(leftChild);
                    int predKey = predNode->keys[predNode->numKeys - 1];
                    int predVal = predNode->values[predNode->numKeys - 1];
                    node->keys[i] = predKey;
                    node->values[i] = predVal; // Copy value
                    deleteInternal(leftChild, predKey);
                } else if (rightChild->numKeys > 1) {
                    Node* succNode = findMinNode(rightChild);
                    int succKey = succNode->keys[0];
                    int succVal = succNode->values[0];
                    node->keys[i] = succKey;
                    node->values[i] = succVal; // Copy value
                    deleteInternal(rightChild, succKey);
                } else {
                    mergeChildren(node, i);
                    deleteInternal(node->children[i], x);
                }
            }
        } 
        else {
            if (node->isLeaf) return;
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

    void insert(int x, int val) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys[0] = x;
            root->values[0] = val;
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
        insertNonFull(root, x, val);
    }

    void rangeRecursive(Node* node, int L, int R, bool& found) {
        if (!node) return;

        for (int i = 0; i <= node->numKeys; ++i) {
            if (!node->isLeaf) {
                rangeRecursive(node->children[i], L, R, found);
            }
            
            if (i < node->numKeys) {
                int key = node->keys[i];
                if (key > R) {
                    return; 
                }
                if (key >= L) {
                    std::cout << key << ":" << node->values[i] << std::endl;
                    found = true;
                }
            }
        }
    }

public:
    Dict() : root(nullptr) {}
    ~Dict() { clear(root); }

    void get(int x) {
        Node* node = root;
        while (node != nullptr) {
            int i = node->findKeyIndex(x);
            if (i < node->numKeys && node->keys[i] == x) {
                std::cout << node->values[i] << std::endl;
                return;
            }
            if (node->isLeaf) {
                break;
            }
            node = node->children[i];
        }
        std::cout << "NOTFOUND" << std::endl;
    }

    void put(int key, int val) {
        Node* node = root;
        while (node != nullptr) {
            int i = node->findKeyIndex(key);
            if (i < node->numKeys && node->keys[i] == key) {
                node->values[i] = val; 
                return;
            }
            if (node->isLeaf) {
                break; 
            }
            node = node->children[i];
        }
        
        insert(key, val);
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

    void range(int L, int R) {
        bool found = false;
        rangeRecursive(root, L, R, found);
        if (!found) {
            std::cout << "EMPTY" << std::endl;
        }
    }

    void batchDelete(const std::vector<int>& keys) {
        for (int key : keys) {
            deleteKey(key); 
        }
    }
};

} // namespace ASR
