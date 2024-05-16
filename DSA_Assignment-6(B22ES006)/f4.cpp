#include <bits/stdc++.h>
using namespace std;

using InnerMap = std::unordered_map<string, int>;
using HistogramMap = std::unordered_map<string, InnerMap>;
HistogramMap Histogram;

class HybridNode {
public:
 string key; // Word
 string element; // Chapter
 HybridNode* parent; // Parent node
 HybridNode* left_child; // Left child node
 HybridNode* right_child; // Right child node
 HybridNode* next_node; // Next node in the linked list
 string color = "red"; // Color of the node

 bool isOnLeft() {
    if (this->parent == nullptr){
        return false;
    }
    return this->parent->left_child == this;
}

 HybridNode* uncle() {
    if (parent == nullptr || parent->parent == nullptr) {
        return nullptr; // No parent or grandparent, so no uncle
    }

    HybridNode* grandparent = parent->parent;
    return (parent == grandparent->left_child) ? grandparent->right_child : grandparent->left_child;
}

 HybridNode* sibling() {
    if (parent == nullptr) {
        return nullptr; // No parent, so no sibling
    }
    
    return (this == parent->left_child) ? parent->right_child : parent->left_child;
}

 void moveDown(HybridNode *newParent) {
    if (parent) {
        if (isOnLeft()) {
            parent->left_child = newParent;
        } else {
            parent->right_child = newParent;
        }
    }

    if (newParent) {
        newParent->parent = parent;
    }
    
    parent = newParent;
}

bool hasRedChild() {
    return (left_child && left_child->color == "red") || (right_child && right_child->color == "red");
}

 HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

class RedBlackTree {
private:
 HybridNode* root; // Root node

public:
 RedBlackTree() : root(nullptr) {}

 void swapColors(HybridNode *x1, HybridNode *x2) {
    swap(x1->color, x2->color);
}
 void swapValues(HybridNode *u, HybridNode *v) {
    swap(u->key, v->key);
}

void leftRotate(HybridNode *x) {
    HybridNode *y = x->right_child;
    x->right_child = y->left_child;
    if (y->left_child != nullptr) {
        y->left_child->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left_child) {
        x->parent->left_child = y;
    } else {
        x->parent->right_child = y;
    }
    y->left_child = x;
    x->parent = y;
}

void rightRotate(HybridNode *y) {
    HybridNode *x = y->left_child;
    y->left_child = x->right_child;
    if (x->right_child != nullptr) {
        x->right_child->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left_child) {
        y->parent->left_child = x;
    } else {
        y->parent->right_child = x;
    }
    x->right_child = y;
    y->parent = x;
}

 void fixRed(HybridNode *x) {
    if (x == root) {
        x->color = "black";
        return;
    }

    HybridNode *parent = x->parent;
    HybridNode *grandparent = parent->parent;
    HybridNode *uncle = x->uncle();

    if (parent->color == "red") {
        if (uncle && uncle->color == "red") {
            handleRedUncle(parent, grandparent, uncle);
        } else {
            handleRotationAndRecoloring(x, parent, grandparent);
        }
    }
}

void handleRedUncle(HybridNode *parent, HybridNode *grandparent, HybridNode *uncle) {
    parent->color = "black";
    uncle->color = "black";
    grandparent->color = "red";
    fixRed(grandparent);
}

void handleRotationAndRecoloring(HybridNode *x, HybridNode *parent, HybridNode *grandparent) {
    if (parent->isOnLeft()) {
        if (x->isOnLeft()) {
            rotateAndSwapLeft(parent, grandparent);
        } else {
            leftRotate(parent);
            swapColors(x, grandparent);
        }
        rightRotate(grandparent);
    } else {
        if (x->isOnLeft()) {
            rightRotate(parent);
            swapColors(x, grandparent);
        } else {
            swapColors(parent, grandparent);
        }
        leftRotate(grandparent);
    }
}

void rotateAndSwapLeft(HybridNode *x, HybridNode *y) {
    swapColors(x, y);
    rightRotate(y);
}

HybridNode* successor(HybridNode* x) {
    while (x->left_child != nullptr) {
        x = x->left_child;
    }
    return x;
}

HybridNode* search(string key) {
    return searchHelper(getRoot(), key);
}
HybridNode* searchHelper(HybridNode* current, string key) {
    if (current == nullptr) {
        return nullptr;  // Node not found
    }

    if (key == current->key) {
        return current;  // Found the node with the given key
    } else if (key < current->key) {
        return searchHelper(current->left_child, key);  // Go left
    } else {
        return searchHelper(current->right_child, key);  // Go right
    }
}

bool present(string key) {
    return presentHelper(getRoot(), key);
}
bool presentHelper(HybridNode* root, string key) {
    if (root == nullptr) {
        return false;
    }

    if (root->key == key) {
        return true;
    } else if (root->key < key) {
        return presentHelper(root->right_child, key);
    } else {
        return presentHelper(root->left_child, key);
    }
}

HybridNode* minimum() {
    return minimumHelper(getRoot());
}
HybridNode* minimumHelper(HybridNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    while (root->left_child != nullptr) {
        root = root->left_child;
    }

    return root;
}

HybridNode* BSTreplace(HybridNode* x) {
    if (hasTwoChildren(x)) {
        return successor(x->right_child);
    } else if (isLeaf(x)) {
        return nullptr;
    } else {
        return (x->left_child != nullptr) ? x->left_child : x->right_child;
    }
}
bool hasTwoChildren(HybridNode* x) {
    return x->left_child != nullptr && x->right_child != nullptr;
}
bool isLeaf(HybridNode* x) {
    return x->left_child == nullptr && x->right_child == nullptr;
}

void fixDoubleBlack(HybridNode *x) {
    if (x == root) {
        // Reached root
        return;
    }

    HybridNode *sibling = x->sibling();
    HybridNode *parent = x->parent;

    if (sibling == nullptr) {
        // No sibling, double black pushed up
        fixDoubleBlackHelperNoSibling(parent);
    } else if (sibling->color == "red") {
        // Sibling red
        fixDoubleBlackHelperRedSibling(parent, sibling);
    } else {
        // Sibling black
        fixDoubleBlackHelperBlackSibling(x, parent, sibling);
    }
}

void fixDoubleBlackHelperNoSibling(HybridNode *parent) {
    if (parent) {
        if (parent->color == "red") {
            parent->color = "black";
        } else {
            fixDoubleBlack(parent);
        }
    }
}

void fixDoubleBlackHelperRedSibling(HybridNode *parent, HybridNode *sibling) {
    parent->color = "red";
    sibling->color = "black";

    if (sibling->isOnLeft()) {
        rightRotate(parent);
    } else {
        leftRotate(parent);
    }

    fixDoubleBlack(parent);
}

void fixDoubleBlackHelperBlackSibling(HybridNode *x, HybridNode *parent, HybridNode *sibling) {
    if (sibling->hasRedChild()) {
        if (sibling->left_child && sibling->left_child->color == "red") {
            if (sibling->isOnLeft()) {
                sibling->left_child->color = sibling->color;
                sibling->color = parent->color;
                rightRotate(parent);
            } else {
                sibling->left_child->color = parent->color;
                rightRotate(sibling);
                leftRotate(parent);
            }
        } else {
            if (sibling->isOnLeft()) {
                sibling->right_child->color = parent->color;
                leftRotate(sibling);
                rightRotate(parent);
            } else {
                sibling->right_child->color = sibling->color;
                sibling->color = parent->color;
                leftRotate(parent);
            }
        }
        parent->color = "black";
    } else {
        sibling->color = "red";
        if (parent->color == "black") {
            fixDoubleBlack(parent);
        } else {
            parent->color = "black";
        }
    }
}

 HybridNode* getRoot() {
 return root; // Return the root node
 }

 void setRoot(HybridNode* node) {
 root = node; // Set the root node
 }

void makeBlack(HybridNode* node) {
    if (node) {
        node->color = "black";
    }
}

void makeRed(HybridNode* node) {
    if (node) {
        node->color = "red";
    }
}

bool isRed(HybridNode* node) {
    return (node && node->color == "red");
}

void insertFix(HybridNode* z) {
    while (isRed(z->parent)) {
        if (z->parent == z->parent->parent->left_child) {
            HybridNode* y = z->parent->parent->right_child;
            if (isRed(y)) {
                makeBlack(z->parent);
                makeBlack(y);
                makeRed(z->parent->parent);
                z = z->parent->parent;
            } else {
                if (z == z->parent->right_child) {
                    z = z->parent;
                    leftRotate(z);
                }
                makeBlack(z->parent);
                makeRed(z->parent->parent);
                rightRotate(z->parent->parent);
            }
        } else {
            HybridNode* y = z->parent->parent->left_child;
            if (isRed(y)) {
                makeBlack(z->parent);
                makeBlack(y);
                makeRed(z->parent->parent);
                z = z->parent->parent;
            } else {
                if (z == z->parent->left_child) {
                    z = z->parent;
                    rightRotate(z);
                }
                makeBlack(z->parent);
                makeRed(z->parent->parent);
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = "black";
}

 HybridNode* insert(string key, string element) {
    // Increase the count in the Histogram
    Histogram[key][element]++;
    
    HybridNode* z = new HybridNode(key, element);
    HybridNode* parent = nullptr;
    HybridNode* current = getRoot();

    while (current) {
        parent = current;
        if (key == current->key) {
            return root;
        }
        current = (key < current->key) ? current->left_child : current->right_child;
    }

    z->parent = parent;
    if (!parent) {
        setRoot(z);
    } else if (key < parent->key) {
        parent->left_child = z;
    } else {
        parent->right_child = z;
    }

    insertFix(z);
    return z;
}

HybridNode* findSuccessor(HybridNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->right_child) {
        node = node->right_child;
        while (node->left_child) {
            node = node->left_child;
        }
        return node;
    }

    HybridNode* parent = node->parent;
    while (parent && node == parent->right_child) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void deleteHelper(HybridNode* v) {
    if (v == nullptr) {
        return;
    }

    HybridNode* u = BSTreplace(v);
    bool bothBlack = (u == nullptr || u->color == "black") && (v->color == "black");
    HybridNode* parent = v->parent;

    if (u == nullptr) {
        // Case 1: v is a leaf node
        if (v == root) {
            root = nullptr;
        } else {
            handleLeafNodeDeletion(v, parent, bothBlack);
        }
        delete v;
    } else if (v->left_child == nullptr || v->right_child == nullptr) {
        // Case 2: v has one child
        handleNodeWithOneChild(v, parent, u, bothBlack);
        delete v;
    } else {
        // Case 3: v has two children
        HybridNode* successor = findSuccessor(v);
        swapValues(u, v);
        deleteHelper(successor);
    }
}

void handleLeafNodeDeletion(HybridNode* v, HybridNode* parent, bool bothBlack) {
    if (bothBlack) {
        fixDoubleBlack(v);
    } else {
        if (v->sibling() != nullptr) {
            v->sibling()->color = "red";
        }
    }

    if (v->isOnLeft()) {
        parent->left_child = nullptr;
    } else {
        parent->right_child = nullptr;
    }
}

void handleNodeWithOneChild(HybridNode* v, HybridNode* parent, HybridNode* u, bool bothBlack) {
    if (v == root) {
        v->key = u->key;
        v->left_child = v->right_child = nullptr;
        delete u;
    } else {
        if (v->isOnLeft()) {
            parent->left_child = u;
        } else {
            parent->right_child = u;
        }
        u->parent = parent;

        if (bothBlack) {
            fixDoubleBlack(u);
        } else {
            u->color = "black";
        }
    }
}

bool deleteNode(string key) {
    HybridNode* to_be_del = search(key);

    if (to_be_del) {
        deleteHelper(to_be_del);
        return true;
    }

    return false;
}

vector<HybridNode*> traverseUp(HybridNode* node) {
    vector<HybridNode*> path; // Create a vector to store the nodes in the path

    while (node != nullptr) {
        path.push_back(node); // Add the current node to the path
        node = node->parent; // Move to the parent node
    }

    // The path vector now contains nodes from the given node to the root
    return path;
    }

vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
    vector<HybridNode*> path; // Create a vector to store the nodes in the path
    HybridNode* current = node;

    for (char bit : bit_sequence) {
        if (bit == '0' && current->left_child != nullptr) {
            current = current->left_child;
        } else if (bit == '1' && current->right_child != nullptr) {
            current = current->right_child;
        } else {
            // Invalid bit sequence or missing child node
            return path;
        }
        path.push_back(current); // Add the current node to the path
    }
    // The path vector now contains nodes based on the provided bit sequence
    return path;
    }

vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
    vector<HybridNode*> result;

    if (node == nullptr || depth < 0) {
        return result;
    }

    result.push_back(node);
    if (depth > 0) {
        vector<HybridNode*> left = preOrderTraversal(node->left_child, depth - 1);
        vector<HybridNode*> right = preOrderTraversal(node->right_child, depth - 1);
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
    }

    return result;
}

 int blackheight(HybridNode* node) {
    int bh = 0; // Initialize black height to 0

    while (node != nullptr) {
        if (node->color == "black") {
            bh++; // Increase black height for black nodes
        }
        node = node->left_child; // Move to the left child
    }

    return bh;
}

};

class IndexEntry {
private:
 string word;
 vector<pair<string, int>> chapter_word_counts; // List of (chapter, word_count) tuples

public:
 IndexEntry(string word_val) : word(word_val) {}

 void setWord(string word_val) { // Set the word
 word = word_val;
 }

 string getWord() { // Get the word
 return word;
 }

 void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) { // Set the list of (chapter, word_count) tuples
 chapter_word_counts = chapter_word_counts_val;
 }

 vector<pair<string, int>> getChapterWordCounts() { // Get the list of (chapter, word_count) tuples
 return chapter_word_counts;
 }

};

class Lexicon {
private:
 RedBlackTree red_black_tree; // Red-Black Tree

public:
 Lexicon() {}
 
 vector <string> get_words_from_chapter(string chapterName){
 vector<std::string> words;

 ifstream file(chapterName);
 string word;
 if (file.is_open()){
 while (file >> word){
 // Replace punctuation marks with spaces
 std::replace_if(
 word.begin(), word.end(), [](char c)
 { return std::ispunct(c); },
 ' ');

 // Remove trailing spaces
 word.erase(std::remove(word.begin(), word.end(), ' '), word.end());

 // Add the word to the vector if it's not empty
 if (!word.empty()){
 words.push_back(word);
 }
 }
 file.close();
 }
 else{
 std::cerr << "Unable to open file: " << chapterName << std::endl;
 }
 return words;
 }
 
 void setRedBlackTree(RedBlackTree tree) { // Set the Red-Black Tree
 red_black_tree = tree;
 }

 RedBlackTree getRedBlackTree() { // Get the Red-Black Tree
 return red_black_tree;
 }

 vector <string> chapters;
 void readChapters(vector<string> chapter_names) {
    chapters = chapter_names;

    // Process words from each chapter and update the Red-Black Tree
    for (int i = 0; i < chapter_names.size(); i++) {
        processChapter(chapter_names[i]);
    }

    pruneRedundantWords(chapter_names);
}

void processChapter(const string& chapter_name) {
    vector<string> chapterWords = get_words_from_chapter(chapter_name);

    for (int j = 0; j < chapterWords.size(); j++) {
        red_black_tree.insert(chapterWords[j], chapter_name.substr(0, chapter_name.size() - 4));
    }
}

void pruneRedundantWords(const vector<string>& chapter_names) {
    vector<string> to_be_pruned;

    for (auto it = Histogram.begin(); it != Histogram.end(); it++) {
        if (it->second.size() == chapter_names.size()) {
            unordered_map<string, int> changed;
            to_be_pruned.push_back(it->first);
        }
    }

    for (int i = 0; i < to_be_pruned.size(); i++) {
        red_black_tree.deleteNode(to_be_pruned[i]);
    }
}

int countNodes(HybridNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int count = 1; // Initialize with the root node
    count += countNodes(root->left_child);
    count += countNodes(root->right_child);

    return count;
}
void levelOrder(HybridNode* root) {
    if (root == nullptr) {
        return;
    }

    queue<HybridNode*> nodesQueue;
    nodesQueue.push(root);

    while (!nodesQueue.empty()) {
        int levelSize = nodesQueue.size();

        for (int i = 0; i < levelSize; i++) {
            HybridNode* currentNode = nodesQueue.front();
            nodesQueue.pop();

            cout << currentNode->key << " ";

            if (currentNode->left_child) {
                nodesQueue.push(currentNode->left_child);
            }

            if (currentNode->right_child) {
                nodesQueue.push(currentNode->right_child);
            }
        }

        cout << endl;
    }
}

 vector<IndexEntry> buildIndex() {
    vector<IndexEntry> result;
    for (auto histogramIterator = Histogram.begin(); histogramIterator != Histogram.end(); ++histogramIterator) {
        if (isChapterCountMismatch(histogramIterator)) {
            IndexEntry indexEntry = createIndexEntry(histogramIterator);
            result.push_back(indexEntry);
        }
    }
    return result;
}

bool isChapterCountMismatch(auto& histogramIterator) {
    return histogramIterator->second.size() != chapters.size();
}

IndexEntry createIndexEntry(auto& histogramIterator) {
    string word = histogramIterator->first;
    IndexEntry indexEntry(word);
    unordered_map<string, int> wordCountMap = histogramIterator->second;
    vector<pair<string, int>> chapterWordCounts = buildChapterWordCounts(wordCountMap);
    indexEntry.setChapterWordCounts(chapterWordCounts);
    return indexEntry;
}

vector<pair<string, int>> buildChapterWordCounts(unordered_map<string, int>& wordCountMap) {
    vector<pair<string, int>> chapterWordCounts;
    for (int i = 0; i < chapters.size(); ++i) {
        pair<string, int> chapterWordCount = getChapterWordCount(i, wordCountMap);
        chapterWordCounts.push_back(chapterWordCount);
    }
    return chapterWordCounts;
}

pair<string, int> getChapterWordCount(int chapterIndex, unordered_map<string, int>& wordCountMap) {
    string chapterName = chapters[chapterIndex].substr(0, chapters[chapterIndex].size() - 4);
    pair<string, int> chapterWordCount(chapterName, wordCountMap[chapterName]);
    return chapterWordCount;
}

};
