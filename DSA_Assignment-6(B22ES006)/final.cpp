#include <bits/stdc++.h>
#include <vector>
using namespace std;

class HybridNode {
public:
    string key;  
    string element;  
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;
    string color = "";

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

class RedBlackTree {
private:
    HybridNode* root;

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;
    }

    void setRoot(HybridNode* node) {
        root = node;
    }

    bool isLeftChild(HybridNode* node) {
    return node->parent && node->parent->left_child == node;
    }

    HybridNode* insert(string key, string element) {
    HybridNode* newNode = new HybridNode(key, element);

    // Insert the new node as in a standard Binary Search Tree
    HybridNode* parent = nullptr;
    HybridNode* current = root;
    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left_child;
        } else {
            current = current->right_child;
        }
    }

    newNode->parent = parent;

    if (parent == nullptr) {
        // Tree is empty, newNode becomes the root
        root = newNode;
    } else if (key < parent->key) {
        parent->left_child = newNode;
    } else {
        parent->right_child = newNode;
    }

    // Perform Red-Black Tree fixing
    insertFixup(newNode);
    
    return newNode;
}

void insertFixup(HybridNode* node) {
    // Implement the Red-Black Tree fixing
    while (node->parent != nullptr && node->parent->color == "red") {
        if (node->parent == node->parent->parent->left_child) {
            HybridNode* uncle = node->parent->parent->right_child;

            if (uncle != nullptr && uncle->color == "red") {
                // Case 1: Uncle is red
                node->parent->color = "black";
                uncle->color = "black";
                node->parent->parent->color = "red";
                node = node->parent->parent;
            } else {
                if (node == node->parent->right_child) {
                    // Case 2: Uncle is black, and node is a right child
                    node = node->parent;
                    leftRotate(node);
                }
                // Case 3: Uncle is black, and node is a left child
                node->parent->color = "black";
                node->parent->parent->color = "red";
                rightRotate(node->parent->parent);
            }
        } else {
            HybridNode* uncle = node->parent->parent->left_child;  // Symmetric to the left child cases

            if (uncle != nullptr && uncle->color == "red") {
                // Case 1: Uncle is red, so we need to recolor
                node->parent->color = "black";
                uncle->color = "black";
                node->parent->parent->color = "red";
                node = node->parent->parent;
            } else {
                if (isLeftChild(node)) {
                    // Case 2: Uncle is black, and node is a left child, so we need to right-rotate
                    node = node->parent;
                    rightRotate(node);
                }

                // Case 3: Uncle is black, and node is a right child, so we need to left-rotate and recolor
                node->parent->color = "black";
                node->parent->parent->color = "red";
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = "black"; // Ensure root is black
}

void leftRotate(HybridNode* node) {
    HybridNode* rightChild = node->right_child;
    
    // Update the right child
    node->right_child = rightChild->left_child;
    if (rightChild->left_child != nullptr) {
        rightChild->left_child->parent = node;
    }
    
    // Update the parent
    rightChild->parent = node->parent;
    if (node->parent == nullptr) {
        // If node is the root, set rightChild as the new root
        root = rightChild;
    } else if (node == node->parent->left_child) {
        // If node is a left child, update the parent's left child
        node->parent->left_child = rightChild;
    } else {
        // If node is a right child, update the parent's right child
        node->parent->right_child = rightChild;
    }
    
    // Update the links between node and rightChild
    rightChild->left_child = node;
    node->parent = rightChild;
}

void rightRotate(HybridNode* node) {
    HybridNode* leftChild = node->left_child;
    
    // Update the left child
    node->left_child = leftChild->right_child;
    if (leftChild->right_child != nullptr) {
        leftChild->right_child->parent = node;
    }
    
    // Update the parent
    leftChild->parent = node->parent;
    if (node->parent == nullptr) {
        // If node is the root, set leftChild as the new root
        root = leftChild;
    } else if (node == node->parent->right_child) {
        // If node is a right child, update the parent's right child
        node->parent->right_child = leftChild;
    } else {
        // If node is a left child, update the parent's left child
        node->parent->left_child = leftChild;
    }
    
    // Update the links between node and leftChild
    leftChild->right_child = node;
    node->parent = leftChild;
}


    bool deleteNode(string key) {
    // Step 1: Find the node to delete
    HybridNode* nodeToDelete = search(key);

    if (nodeToDelete == nullptr) {
        // Key not found
        return false;
    }

    // Step 2: Perform standard binary search tree deletion
    HybridNode* parent = nodeToDelete->parent;
    HybridNode* successor = nullptr;

    if (nodeToDelete->left_child == nullptr || nodeToDelete->right_child == nullptr) {
        successor = nodeToDelete;  // Node has 0 or 1 child
    } else {
        successor = findSuccessor(nodeToDelete);
        nodeToDelete->key = successor->key;
        nodeToDelete->element = successor->element;
    }

    HybridNode* child = (successor->left_child != nullptr) ? successor->left_child : successor->right_child;

    if (child != nullptr) {
        child->parent = parent;
    }

    if (parent == nullptr) {
        // The deleted node was the root
        root = child;
    } else if (nodeToDelete == parent->left_child) {
        parent->left_child = child;
    } else {
        parent->right_child = child;
    }

    // Step 3: Fix Red-Black Tree properties
    if (successor->color == "black") {
        deleteFixup(child, parent);
    }

    delete successor;  // Free the memory

    return true;
}

HybridNode* findSuccessor(HybridNode* node) {
    // Helper function to find the in-order successor
    HybridNode* current = node->right_child;
    while (current->left_child != nullptr) {
        current = current->left_child;
    }
    return current;
}

void deleteFixup(HybridNode* node, HybridNode* parent) {
    // Implement Red-Black Tree fixing after deletion
    while (node != root && (node == nullptr || node->color == "black")) {
        HybridNode* sibling = (node == parent->left_child) ? parent->right_child : parent->left_child;

        if (sibling->color == "red") {
            sibling->color = "black";
            parent->color = "red";
            if (node == parent->left_child) {
                leftRotate(parent);
                sibling = parent->right_child;
            } else {
                rightRotate(parent);
                sibling = parent->left_child;
            }
        }

        if ((sibling->left_child == nullptr || sibling->left_child->color == "black") &&
            (sibling->right_child == nullptr || sibling->right_child->color == "black")) {
            sibling->color = "red";
            node = parent;
            parent = node->parent;
        } else {
            if (node == parent->left_child && (sibling->right_child == nullptr || sibling->right_child->color == "black")) {
                sibling->color = "red";
                sibling->left_child->color = "black";
                rightRotate(sibling);
                sibling = parent->right_child;
            } else if (node == parent->right_child && (sibling->left_child == nullptr || sibling->left_child->color == "black")) {
                sibling->color = "red";
                sibling->right_child->color = "black";
                leftRotate(sibling);
                sibling = parent->left_child;
            }

            sibling->color = parent->color;
            parent->color = "black";

            if (node == parent->left_child) {
                sibling->right_child->color = "black";
                leftRotate(parent);
            } else {
                sibling->left_child->color = "black";
                rightRotate(parent);
            }

            node = root;
        }
    }

    if (node != nullptr) {
        node->color = "black";
    }
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
    
    HybridNode* current = node;
    for (char bit : bit_sequence) {
        if (bit == '0' && current->left_child != nullptr) {
            current = current->left_child;
        } else if (bit == '1' && current->right_child != nullptr) {
            current = current->right_child;
        } else {
            // Invalid bit or child node is null, terminate the traversal
            break;
        }
        path.push_back(current);
    }
    
    return path;
}


    vector<string> preOrderTraversal(HybridNode* node, int depth, int currentDepth = 0) {
    vector<string> result;

    if (node == nullptr) {
        return result;
    }

    if (currentDepth < depth) {
        // Visit the current node
        result.push_back(node->element);

        // Traverse the left subtree
        vector<string> leftSubtree = preOrderTraversal(node->left_child, depth, currentDepth + 1);
        result.insert(result.end(), leftSubtree.begin(), leftSubtree.end());

        // Traverse the right subtree
        vector<string> rightSubtree = preOrderTraversal(node->right_child, depth, currentDepth + 1);
        result.insert(result.end(), rightSubtree.begin(), rightSubtree.end());
    }

    return result;
}


    HybridNode* search(string key) {
    HybridNode* current = root;  // Start the search at the root

    // Continue the search until we reach a leaf node or find the key
    while (current != nullptr) {
        if (key == current->key) {
            return current;  // Key found, return the node
        } else if (key < current->key) {
            current = current->left_child;  // Key is smaller, go left
        } else {
            current = current->right_child;  // Key is larger, go right
        }
    }

    return nullptr;  // Key not found, return nullptr
}

    
    int blackheight(HybridNode* node) {
    if (node == nullptr) {
        return 0;  // Base case: null nodes are black by convention and contribute 0 to black height
    }

    // Initialize variables to count black nodes for the left and right subtrees
    int leftBlackHeight = 0;
    int rightBlackHeight = 0;

    if (node->color == "black") {
        // If the current node is black, increment the count
        leftBlackHeight = 1;
        rightBlackHeight = 1;
    }

    // Recursively calculate black height for the left and right subtrees
    leftBlackHeight += blackheight(node->left_child);
    rightBlackHeight += blackheight(node->right_child);

    // Ensure that the left and right subtrees have the same black height
    if (leftBlackHeight != rightBlackHeight) {
        // Handle black height violation (e.g., return an error code or throw an exception)
    }

    // Return the black height for this subtree
    return leftBlackHeight;
}

};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {
        word = word_val;
    }

    string getWord() {
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {
        return chapter_word_counts;
    }

    void addOccurrence(string chapter, int word_count) {
        for (auto& entry : chapter_word_counts) {
            if (entry.first == chapter) {
                // Update the word count for the existing chapter
                entry.second = word_count;
                return; // Exit the function
            }
        }
        
        // If the chapter doesn't exist, add a new chapter-word count pair
        chapter_word_counts.push_back(make_pair(chapter, word_count));
    }

    string toString() {
    // Return a string representation of the IndexEntry
    string result = "Word: " + word + "\n";
    
    for (const auto& entry : chapter_word_counts) {
        result += "Chapter: " + entry.first + ", Word Count: " + to_string(entry.second) + "\n";
    }

    return result;
}

};

class Lexicon {
private:
    RedBlackTree red_black_tree;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {
        return red_black_tree;
    }

    void readChapter(string chapter_name, vector<string> words) {




    }


    void pruneRedBlackTree(HybridNode* node, const std::vector<std::string>& all_chapters) {


    };

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
    }
    
};

extern Lexicon lexicon;