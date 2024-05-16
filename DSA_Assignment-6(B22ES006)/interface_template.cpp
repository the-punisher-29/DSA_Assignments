#include <bits/stdc++.h>
#include <vector>
using namespace std;

enum class Color { RED, BLACK };//change

class HybridNode {
public:
    string key;  
    string element;  
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;
    Color color;//change

    HybridNode(string key_val, string element_val,Color node_color) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr),color(node_color) {}
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

    void leftRotate(HybridNode* node) {
    HybridNode* right_child = node->right_child;

    // Step 1: Update the right child
    node->right_child = right_child->left_child;
    if (right_child->left_child != nullptr) {
        right_child->left_child->parent = node;
    }

    // Step 2: Update the parent of right_child
    right_child->parent = node->parent;

    if (node->parent == nullptr) {
        root = right_child;  // Update the root if node was the root
    } else if (node == node->parent->left_child) {
        node->parent->left_child = right_child;
    } else {
        node->parent->right_child = right_child;
    }

    // Step 3: Move node to the left of right_child
    right_child->left_child = node;
    node->parent = right_child;
}

void rightRotate(HybridNode* node) {
    HybridNode* left_child = node->left_child;

    // Step 1: Update the left child
    node->left_child = left_child->right_child;
    if (left_child->right_child != nullptr) {
        left_child->right_child->parent = node;
    }

    // Step 2: Update the parent of left_child
    left_child->parent = node->parent;

    if (node->parent == nullptr) {
        root = left_child;  // Update the root if node was the root
    } else if (node == node->parent->left_child) {
        node->parent->left_child = left_child;
    } else {
        node->parent->right_child = left_child;
    }

    // Step 3: Move node to the right of left_child
    left_child->right_child = node;
    node->parent = left_child;
}


    void insertFixup(HybridNode* node) {
    while (node != root && node->parent->color == Color::RED) {
        if (isLeftChild(node->parent)) {
            HybridNode* uncle = node->parent->parent->right_child;

            if (uncle != nullptr && uncle->color == Color::RED) {
                // Case 1: Uncle is red, so we need to recolor
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else {
                if (!isLeftChild(node)) {
                    // Case 2: Uncle is black, and node is a right child, so we need to left-rotate
                    node = node->parent;
                    leftRotate(node);
                }

                // Case 3: Uncle is black, and node is a left child, so we need to right-rotate and recolor
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rightRotate(node->parent->parent);
            }
        } else {
            HybridNode* uncle = node->parent->parent->left_child;  // Symmetric to the left child cases

            if (uncle != nullptr && uncle->color == Color::RED) {
                // Case 1: Uncle is red, so we need to recolor
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else {
                if (isLeftChild(node)) {
                    // Case 2: Uncle is black, and node is a left child, so we need to right-rotate
                    node = node->parent;
                    rightRotate(node);
                }

                // Case 3: Uncle is black, and node is a right child, so we need to left-rotate and recolor
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                leftRotate(node->parent->parent);
            }
        }
    }

    root->color = Color::BLACK;  // Ensure the root is black
    }
    
    HybridNode* insert(string key, string element) {
    Color node_color=Color::RED;
    HybridNode* new_node = new HybridNode(key, element, node_color);

    if (root == nullptr) {
        // Case 1: If the tree is empty, the new node becomes the root, and its color is set to black.
        new_node->color = Color::BLACK;
        root = new_node;
    } else {
        // Otherwise, we perform a standard binary search tree insertion.
        HybridNode* parent = nullptr;
        HybridNode* current = root;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) {
                current = current->left_child;
            } else if (key > current->key) {
                current = current->right_child;
            } else {
                // Handle duplicate keys (you need to define your logic)
                // In this example, we ignore duplicates.
                delete new_node;  // Deallocate memory for the new node
                return nullptr;  // Return nullptr for duplicates
            }
        }

        new_node->parent = parent;
        if (key < parent->key) {
            parent->left_child = new_node;
        } else {
            parent->right_child = new_node;
        }

        // Step 2: After insertion, we need to fix any potential violations of Red-Black Tree properties.
        insertFixup(new_node);
    }

    return new_node;  // Return the newly inserted node
}

void deleteFixup(HybridNode* node) {
    while (node != root && node->color == Color::BLACK) {
        if (isLeftChild(node)) {
            HybridNode* sibling = node->parent->right_child;

            if (sibling->color == Color::RED) {
                // Case 1: Sibling is red
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                leftRotate(node->parent);
                sibling = node->parent->right_child;
            }

            if ((sibling->left_child == nullptr || sibling->left_child->color == Color::BLACK) &&
                (sibling->right_child == nullptr || sibling->right_child->color == Color::BLACK)) {
                // Case 2: Sibling is black, and both sibling's children are black
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                if (sibling->right_child == nullptr || sibling->right_child->color == Color::BLACK) {
                    // Case 3: Sibling is black, sibling's left child is red, and right child is black
                    sibling->left_child->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rightRotate(sibling);
                    sibling = node->parent->right_child;
                }

                // Case 4: Sibling is black, sibling's right child is red
                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                sibling->right_child->color = Color::BLACK;
                leftRotate(node->parent);
                node = root;  // Terminate the loop
            }
        } else {
               HybridNode* sibling = node->parent->left_child;  // Symmetric to the left child cases

            if (sibling->color == Color::RED) {
                // Case 1: Sibling is red
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                rightRotate(node->parent);
                sibling = node->parent->left_child;
            }

            if ((sibling->right_child == nullptr || sibling->right_child->color == Color::BLACK) &&
                (sibling->left_child == nullptr || sibling->left_child->color == Color::BLACK)) {
                // Case 2: Sibling is black, and both sibling's children are black
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                if (sibling->left_child == nullptr || sibling->left_child->color == Color::BLACK) {
                    // Case 3: Sibling is black, sibling's right child is red, and left child is black
                    sibling->right_child->color = Color::BLACK;
                    sibling->color = Color::RED;
                    leftRotate(sibling);
                    sibling = node->parent->left_child;
                }

                // Case 4: Sibling is black, sibling's left child is red
                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                sibling->left_child->color = Color::BLACK;
                rightRotate(node->parent);
                node = root;  // Terminate the loop
            }
        }
    }

    node->color = Color::BLACK;
}

void transplant(HybridNode* u, HybridNode* v) {
    if (u->parent == nullptr) {
        root = v;  // If u is the root, replace it with v
    } else if (u == u->parent->left_child) {
        u->parent->left_child = v;
    } else {
        u->parent->right_child = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

HybridNode* findSuccessor(HybridNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->right_child != nullptr) {
        // If the right child is not null, the successor is the leftmost node in the right subtree
        return findMin(node->right_child);
    }

    // If there's no right child, we need to find the ancestor whose left child is also an ancestor of the node.
    HybridNode* ancestor = node->parent;
    while (ancestor != nullptr && node == ancestor->right_child) {
        node = ancestor;
        ancestor = ancestor->parent;
    }

    return ancestor;
}

HybridNode* findMin(HybridNode* node) {
    while (node->left_child != nullptr) {
        node = node->left_child;
    }
    return node;
}

void swapNodeValues(HybridNode* node1, HybridNode* node2) {
    if (node1 == nullptr || node2 == nullptr) {
        return;  // Handle null nodes if needed
    }

    swap(node1->key, node2->key);
    swap(node1->element, node2->element);
    // You can swap any other data you have in the node as needed
}

    bool deleteNode(string key) {
    HybridNode* node_to_delete = search(key);  // Search for the node with the specified key

    if (node_to_delete == nullptr) {
        return false;  // The key was not found in the tree
    }

    // Perform standard BST deletion (can be recursive or iterative)
    if (node_to_delete->left_child == nullptr || node_to_delete->right_child == nullptr) {
        // Node has 0 or 1 child
        HybridNode* child = (node_to_delete->left_child) ? node_to_delete->left_child : node_to_delete->right_child;
        if (node_to_delete->color == Color::BLACK) {
            // Case 1: Node is black and has a black child
            deleteFixup(node_to_delete);
        }
        transplant(node_to_delete, child);
        if (node_to_delete->color == Color::BLACK && child != nullptr) {
            // Case 2: Node is black, has a red child, and that child replaces it
            child->color = Color::BLACK;
        }
        delete node_to_delete;
    } else {
        // Node has 2 children, find the successor or predecessor
        HybridNode* successor = findSuccessor(node_to_delete);
        swapNodeValues(node_to_delete, successor);
        deleteNode(successor->key);
    }

    return true;  // Node was successfully deleted
}


    void traverseUp(HybridNode* node) {
    while (node != nullptr) {
        // Process the current node, for example, print or perform some action
        // Here, we'll print the node's key and element
        //cout << "Key: " << node->key << ", Element: " << node->element << endl;

        node = node->parent; // Move up to the parent node
    }
}


void traverseDown(HybridNode* node, string bit_sequence) {
    for (char bit : bit_sequence) {
        if (bit == '0') {
            if (node->left_child != nullptr) {
                node = node->left_child;
            } else {
                // Handle the case where the path leads to a null left child (if needed)
                throw std::runtime_error("Path leads to a null left child");
                break;
            }
        } else if (bit == '1') {
            if (node->right_child != nullptr) {
                node = node->right_child;
            } else {
                // Handle the case where the path leads to a null right child (if needed)
                throw std::runtime_error("Path leads to a null right child");
                break;
            }
        }
        // Optionally, process the node at this level
    }

    // After processing the bit sequence, 'node' now points to the final node along the path.
}


vector<string> preOrderTraversal(HybridNode* node, int depth) {
    vector<string> result;
    preOrderRecursive(node, depth, result);
    return result;
}

void preOrderRecursive(HybridNode* node, int depth, vector<string>& result) {
    if (node == nullptr || depth < 0) {
        return;
    }

    // Process the current node (e.g., add its key to the result)
    result.push_back(node->key);

    // Recursively traverse the left and right subtrees with reduced depth
    preOrderRecursive(node->left_child, depth - 1, result);
    preOrderRecursive(node->right_child, depth - 1, result);
}


HybridNode* search(string key) {
    return searchRecursive(root, key);
}

HybridNode* searchRecursive(HybridNode* node, string key) {
    if (node == nullptr || key == node->key) {
        return node;
    }

    if (key < node->key) {
        return searchRecursive(node->left_child, key);
    } else {
        return searchRecursive(node->right_child, key);
    }
}

    
int blackheight(HybridNode* node) {
    int blackHeight = 0;
    while (node != nullptr) {
        if (node->color == Color::BLACK) {
            blackHeight++;
        }
        node = node->left_child; // Traverse along the left children since they have the same black height
    }
    return blackHeight;
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
    string result = "Word: " + word + "\n";
    for (const auto& pair : chapter_word_counts) {
        result += "Chapter: " + pair.first + ", Word Count: " + to_string(pair.second) + "\n";
    }
    return result;
}

};

class HistogramBin {
public:
    string chapterName;
    int wordCount;
    
    HistogramBin* prev;
    HistogramBin* next;
    
    HistogramBin(const string& chapter) : chapterName(chapter), wordCount(0), prev(nullptr), next(nullptr) {}
};

class MRU {
private:
    unordered_map<string, HistogramBin*> wordToBin;
    HistogramBin* head;
    HistogramBin* tail;
    int getTotalWordCount() {
        int total = 0;
        for (const auto& entry : chapterCounts) {
            total += entry.second;  // Sum up word counts from all chapters
        }
        return total;
    }
    void updateChapterCount(const string& chapter) {
        if (chapterName == chapter) {
            // Increment the word count for the specified chapter
            wordCount++;
        }
    }

public:
    MRU() : head(nullptr), tail(nullptr) {}

    void updateBin(const string& word, const string& chapterName) {
    // Step 1: Check if the word is in the wordToBin map
    if (wordToBin.find(word) == wordToBin.end()) {
        // Word not found, create a new bin
        HistogramBin* newBin = new HistogramBin(chapterName);
        wordToBin[word] = newBin;

        // Update the doubly-linked list (MRU)
        if (!head) {
            head = newBin;
            tail = newBin;
        } else {
            newBin->next = head;
            head->prev = newBin;
            head = newBin;
        }
    } else {
        // Word found, update the bin
        HistogramBin* bin = wordToBin[word];

        // Update the word count for the chapter
        // (You need to implement a suitable method in HistogramBin)
        bin->updateChapterCount(chapterName);

        // Update the MRU list if the bin is not already the head
        if (bin != head) {
            if (bin == tail) {
                tail = bin->prev;
                tail->next = nullptr;
            } else {
                bin->prev->next = bin->next;
                bin->next->prev = bin->prev;
            }
            bin->prev = nullptr;
            bin->next = head;
            head->prev = bin;
            head = bin;
        }
    }
}


    int getTotalWordCount(const string& word) {
    if (wordToBin.find(word) == wordToBin.end()) {
        return 0;  // Word not found, return 0
    } else {
        // Word found, retrieve the total word count from the bin
        HistogramBin* bin = wordToBin[word];
        return bin->getTotalWordCount(); // Implement a suitable method in HistogramBin
    }
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
        // Process words from a chapter and update the Red-Black Tree
    }

    void pruneRedBlackTree() {
        // Prune the Red-Black Tree by deleting common words
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
    }
};

extern Lexicon lexicon;