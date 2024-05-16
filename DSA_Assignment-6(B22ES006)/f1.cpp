#include <bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "black";    // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }
    
    HybridNode* insert(string key, string element) {
    HybridNode* node = new HybridNode(key, element);

    // Perform a standard BST insert
    HybridNode* parent = nullptr;
    HybridNode* current = root;
    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left_child;
        } else if (key > current->key) {
            current = current->right_child;
        } else {
            // Word already exists in the tree, update element
            current->element = element;
            delete node; // Clean up the new node
            return current; // Return the existing node
        }
    }

    // Link the new node to its parent
    node->parent = parent;

    if (parent == nullptr) {
        // If the tree is empty, make the new node the root
        root = node;
    } else if (key < parent->key) {
        parent->left_child = node;
    } else {
        parent->right_child = node;
    }

    // TODO: Implement Red-Black Tree balancing
    fixInsertion(node);
    return node;
}

// Function to fix the Red-Black Tree violations after insertion
void fixInsertion(HybridNode* node) {
    while (node != root && node->parent->color == "red") {
        HybridNode* parent = node->parent;
        HybridNode* grandparent = node->parent->parent;

        if (parent == grandparent->left_child) {
            HybridNode* uncle = grandparent->right_child;

            if (uncle != nullptr && uncle->color == "red") {
                // Case 1: Uncle is red
                parent->color = "black";
                uncle->color = "black";
                grandparent->color = "red";
                node = grandparent;
            } else {
                if (node == parent->right_child) {
                    // Case 2: Node is the right child
                    node = parent;
                    leftRotate(node);
                    parent = node->parent;
                }

                // Case 3: Node is the left child
                parent->color = "black";
                grandparent->color = "red";
                rightRotate(grandparent);
            }
        } else {
            // Symmetric to the above cases
            // ...
        }
    }

    root->color = "black";
}

// Left rotate a node
void leftRotate(HybridNode* node) {
    HybridNode* rightChild = node->right_child;
    node->right_child = rightChild->left_child;

    if (rightChild->left_child != nullptr) {
        rightChild->left_child->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left_child) {
        node->parent->left_child = rightChild;
    } else {
        node->parent->right_child = rightChild;
    }

    rightChild->left_child = node;
    node->parent = rightChild;
}

// Right rotate a node (symmetric to left rotation)
void rightRotate(HybridNode* node) {
    HybridNode* leftChild = node->left_child;
    node->left_child = leftChild->right_child;

    if (leftChild->right_child != nullptr) {
        leftChild->right_child->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right_child) {
        node->parent->right_child = leftChild;
    } else {
        node->parent->left_child = leftChild;
    }

    leftChild->right_child = node;
    node->parent = leftChild;
}



    bool deleteNode(string key) {
    // Find the node to delete (similar to a standard BST delete)
    HybridNode* nodeToDelete = search(key);
    if (nodeToDelete == nullptr) {
        return false; // Node not found, cannot delete
    }

    // Determine the replacement node (successor or predecessor)
    HybridNode* replacement = nullptr;

    if (nodeToDelete->left_child == nullptr || nodeToDelete->right_child == nullptr) {
        replacement = nodeToDelete;
    } else {
        replacement = getSuccessor(nodeToDelete);
    }

    // Get the child of the replacement node (there can be at most one child)
    HybridNode* child = nullptr;
    if (replacement->left_child != nullptr) {
        child = replacement->left_child;
    } else {
        child = replacement->right_child;
    }

    // Perform the actual deletion
    if (child != nullptr) {
        // Splice out the replacement node and replace it with the child
        child->parent = replacement->parent;

        if (replacement->parent == nullptr) {
            root = child;
        } else if (replacement == replacement->parent->left_child) {
            replacement->parent->left_child = child;
        } else {
            replacement->parent->right_child = child;
        }

        // If the replacement node is not the node to be deleted, replace the node with the replacement
        if (replacement != nodeToDelete) {
            nodeToDelete->key = replacement->key;
            nodeToDelete->element = replacement->element;
        }

        // If the replacement node is black, it may violate RB properties, so fix it
        if (replacement->color == "black") {
            fixDeletion(child);
        }
    } else if (replacement->color == "black") {
        fixDeletion(replacement);
    }

    // Free memory and return success
    delete replacement;
    return true;
}

HybridNode* getSuccessor(HybridNode* node) {
    if (node->right_child != nullptr) {
        node = node->right_child;
        while (node->left_child != nullptr) {
            node = node->left_child;
        }
        return node;
    }

    HybridNode* parent = node->parent;
    while (parent != nullptr && node == parent->right_child) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void fixDeletion(HybridNode* node) {
    while (node != root && node->color == "black") {
        if (node == node->parent->left_child) {
            HybridNode* sibling = node->parent->right_child;

            if (sibling->color == "red") {
                // Case 1: Sibling is red
                sibling->color = "black";
                node->parent->color = "red";
                leftRotate(node->parent);
                sibling = node->parent->right_child;
            }

            if (sibling->left_child->color == "black" && sibling->right_child->color == "black") {
                // Case 2: Sibling and both of its children are black
                sibling->color = "red";
                node = node->parent;
            } else {
                if (sibling->right_child->color == "black") {
                    // Case 3: Sibling is black, sibling's left child is red, and sibling's right child is black
                    sibling->left_child->color = "black";
                    sibling->color = "red";
                    rightRotate(sibling);
                    sibling = node->parent->right_child;
                }

                // Case 4: Sibling is black, sibling's right child is red
                sibling->color = node->parent->color;
                node->parent->color = "black";
                sibling->right_child->color = "black";
                leftRotate(node->parent);
                node = root; // Exit the loop
            }
        } else {
            HybridNode* sibling = node->parent->left_child;

            if (sibling->color == "red") {
                // Case 1 (Symmetric): Sibling is red
                sibling->color = "black";
                node->parent->color = "red";
                rightRotate(node->parent);
                sibling = node->parent->left_child;
            }

            if (sibling->right_child->color == "black" && sibling->left_child->color == "black") {
                // Case 2 (Symmetric): Sibling and both of its children are black
                sibling->color = "red";
                node = node->parent;
            } else {
                if (sibling->left_child->color == "black") {
                    // Case 3 (Symmetric): Sibling is black, sibling's right child is red, and sibling's left child is black
                    sibling->right_child->color = "black";
                    sibling->color = "red";
                    leftRotate(sibling);
                    sibling = node->parent->left_child;
                }

                // Case 4 (Symmetric): Sibling is black, sibling's left child is red
                sibling->color = node->parent->color;
                node->parent->color = "black";
                sibling->left_child->color = "black";
                rightRotate(node->parent);
                node = root; // Exit the loop
            }
        }
    }

    node->color = "black";
}


    vector<HybridNode*> traverseUp(HybridNode* node) {
    vector<HybridNode*> path;
    while (node != nullptr) {
        path.push_back(node);
        node = node->parent;
    }
    return path;
    }


    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
    vector<HybridNode*> path;
    
    for (char bit : bit_sequence) {
        if (bit == '0' && node->left_child != nullptr) {
            node = node->left_child;
        } else if (bit == '1' && node->right_child != nullptr) {
            node = node->right_child;
        } else {
            // Invalid bit in the sequence or node has no child in the specified direction
            // You can handle this case according to your needs (e.g., throw an error, return an empty vector)
            return path;
        }
        path.push_back(node);
    }
    
    return path;
    }


    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
    vector<HybridNode*> nodes;

    // Recursive helper function for pre-order traversal
    function<void(HybridNode*, int)> preOrderHelper = [&](HybridNode* currentNode, int currentDepth) {
        if (currentNode == nullptr || currentDepth > depth) {
            return;
        }

        nodes.push_back(currentNode);

        preOrderHelper(currentNode->left_child, currentDepth + 1);
        preOrderHelper(currentNode->right_child, currentDepth + 1);
    };

    preOrderHelper(node, 0);

    return nodes;
}


    HybridNode* search(string key) {
    HybridNode* current = root;

    while (current != nullptr) {
        if (key == current->key) {
            return current;  // Found the node with the given key
        } else if (key < current->key) {
            current = current->left_child;
        } else {
            current = current->right_child;
        }
    }

    return nullptr;  // Key not found in the tree
}

    
    int blackheight(HybridNode* node) {
    if (node == nullptr) {
        return 0;  // Base case: Null nodes are considered black.
    }

    int leftBlackHeight = blackheight(node->left_child);
    int rightBlackHeight = blackheight(node->right_child);

    // Check if there is a violation in the red-black tree property
    if (leftBlackHeight != rightBlackHeight || leftBlackHeight == -1 || rightBlackHeight == -1) {
        // Violation detected, return -1 to indicate an error
        return -1;
    }

    // Return the black height of the current node, adding 1 if the current node is black
    return (node->color == "black") ? leftBlackHeight + 1 : leftBlackHeight;
}
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;  // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
    }
};
int countNodes(HybridNode* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftCount = countNodes(node->left_child);
    int rightCount = countNodes(node->right_child);
    return 1 + leftCount + rightCount;
}
int main() {
    RedBlackTree rbTree;
    rbTree.insert("b22", "CSE");
    rbTree.insert("b21", "EE");
    rbTree.insert("b20", "ES");
    rbTree.insert("abc","Afk");
    rbTree.deleteNode("b22");

    int totalNodeCount = countNodes(rbTree.getRoot());

    cout << "Total number of nodes in the Red-Black Tree: " << totalNodeCount << endl;

    return 0;
}


