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
        // Implement Red-Black Tree insertion
    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
    }

    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        // Perform pre-order traversal staying within specified depth
    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
    }
    
    int blackheight(HybridNode* node){
        // Implement blackheight
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
