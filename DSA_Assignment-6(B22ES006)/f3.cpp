#include <bits/stdc++.h>

using namespace std;

unordered_map <string, unordered_map <string,int> > Histogram;

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "red";    // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
    
    bool isOnLeft() const { return this == parent->left_child; }

    HybridNode* sibling(){
    return (parent == nullptr) ? nullptr : (isOnLeft() ? parent->right_child : parent->left_child);
    }

    HybridNode* uncle() {
    if (parent == nullptr || parent->parent == nullptr) {
        return nullptr; // No parent or no grandparent, so no uncle
    }
    return (parent->isOnLeft()) ? parent->parent->right_child : parent->parent->left_child;
    }
    
    void moveDown(HybridNode* newParent) {
    if (parent != nullptr) {
        if (isOnLeft()) {
            parent->left_child = newParent;
        } else {
            parent->right_child = newParent;
        }
    }
    newParent->parent = parent;
    parent = newParent;
    }
    
    bool hasRedChild() const {
    return (left_child != nullptr && left_child->color == "red") ||
           (right_child != nullptr && right_child->color == "red");
    }
};

class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}
    
    void swapColors(HybridNode* x1, HybridNode* x2) {
    std::swap(x1->color, x2->color);
}

void swapValues(HybridNode* u, HybridNode* v) {
    swap(u->key, v->key);
}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }

void leftRotate(HybridNode* x) {
    HybridNode* y = x->right_child;
    x->right_child = y->left_child;
    if (y->left_child != nullptr)
        y->left_child->parent = x;
    y->moveDown(x->parent);
}

void rightRotate(HybridNode* y) {
    HybridNode* x = y->left_child;
    y->left_child = x->right_child;
    if (x->right_child != nullptr)
        x->right_child->parent = y;
    x->moveDown(y->parent);
}


void fixRedRed(HybridNode* x) {
    if (x == root) {
        x->color = "black";
        return;
    }

    HybridNode* parent = x->parent;

    if (parent->color == "black") {
        return;
    }

    HybridNode* grandparent = parent->parent;
    HybridNode* uncle = x->uncle();

    if (uncle != nullptr && uncle->color == "red") {
        recolor(parent, grandparent, uncle);
        fixRedRed(grandparent);
    } else {
        if (parent->isOnLeft()) {
            if (x->isOnLeft()) {
                performLRRotation(parent, grandparent);
            } else {
                leftRotate(parent);
                performLeftRightRotation(x, parent, grandparent);
            }
            rightRotate(grandparent);
        } else {
            if (x->isOnLeft()) {
                rightRotate(parent);
                performRightLeftRotation(x, parent, grandparent);
            } else {
                performRRRotation(parent, grandparent);
            }
            leftRotate(grandparent);
        }
    }
}

void recolor(HybridNode* parent, HybridNode* grandparent, HybridNode* uncle) {
    parent->color = "black";
    uncle->color = "black";
    grandparent->color = "red";
}

void performLRRotation(HybridNode* parent, HybridNode* grandparent) {
    swapColors(parent, grandparent);
}

void performLeftRightRotation(HybridNode* x, HybridNode* parent, HybridNode* grandparent) {
    leftRotate(parent);
    swapColors(x, grandparent);
}

void performRightLeftRotation(HybridNode* x, HybridNode* parent, HybridNode* grandparent) {
    rightRotate(parent);
    swapColors(x, grandparent);
}

void performRRRotation(HybridNode* parent, HybridNode* grandparent) {
    swapColors(parent, grandparent);
}

HybridNode* successor(HybridNode* x) {
    while (x->left_child != nullptr) {
        x = x->left_child;
    }
    return x;
}

HybridNode* BSTreplace(HybridNode* x) {
    if (x->left_child && x->right_child) {
        return successor(x->right_child);
    } else if (!x->left_child && !x->right_child) {
        return nullptr;
    } else {
        return (x->left_child) ? x->left_child : x->right_child;
    }
}

void fixDoubleBlack(HybridNode* x) {
    if (x == root) {
        return;
    }

    HybridNode* sibling = x->sibling();
    HybridNode* parent = x->parent;

    if (sibling == nullptr) {
        fixDoubleBlackNoSibling(parent);
    } else {
        if (sibling->color == "red") {
            fixDoubleBlackRedSibling(x, sibling, parent);
        } else {
            if (sibling->hasRedChild()) {
                fixDoubleBlackSiblingWithRedChild(x, sibling, parent);
            } else {
                fixDoubleBlackTwoBlackChildren(x, sibling, parent);
            }
        }
    }
}

void fixDoubleBlackNoSibling(HybridNode* parent) {
    fixDoubleBlack(parent);
}

void fixDoubleBlackRedSibling(HybridNode* x, HybridNode* sibling, HybridNode* parent) {
    parent->color = "red";
    sibling->color = "black";
    if (sibling->isOnLeft()) {
        rightRotate(parent);
    } else {
        leftRotate(parent);
    }
    fixDoubleBlack(x);
}

void fixDoubleBlackSiblingWithRedChild(HybridNode* x, HybridNode* sibling, HybridNode* parent) {
    if (sibling->isOnLeft()) {
        if (sibling->left_child != nullptr && sibling->left_child->color == "red") {
            fixDoubleBlackSiblingWithRedLeftChild(x, sibling, parent);
        } else {
            fixDoubleBlackSiblingWithRedRightChild(x, sibling, parent);
        }
    } else {
        if (sibling->right_child != nullptr && sibling->right_child->color == "red") {
            fixDoubleBlackSiblingWithRedRightChild(x, sibling, parent);
        } else {
            fixDoubleBlackSiblingWithRedLeftChild(x, sibling, parent);
        }
    }
}

void fixDoubleBlackSiblingWithRedLeftChild(HybridNode* x, HybridNode* sibling, HybridNode* parent) {
    sibling->left_child->color = sibling->color;
    sibling->color = parent->color;
    rightRotate(parent);
    parent->color = "black";
}

void fixDoubleBlackSiblingWithRedRightChild(HybridNode* x, HybridNode* sibling, HybridNode* parent) {
    sibling->right_child->color = parent->color;
    leftRotate(sibling);
    rightRotate(parent);
    parent->color = "black";
}


void fixDoubleBlackTwoBlackChildren(HybridNode* x, HybridNode* sibling, HybridNode* parent) {
    if (parent->color == "black") {
        fixDoubleBlackBlackParent(x, sibling, parent);
    } else {
        parent->color = "black";
    }
}

void fixDoubleBlackBlackParent(HybridNode* x, HybridNode* sibling, HybridNode* parent) {
    sibling->color = "red";
    fixDoubleBlack(parent);
}

bool present(HybridNode* root, string key) {
    while (root != nullptr) {
        if (root->key == key) {
            return true;
        }
        if (root->key < key) {
            root = root->right_child;
        } else {
            root = root->left_child;
        }
    }
    return false;
}

HybridNode* minimum(HybridNode* root) {
    if (root == nullptr) {
        return root;
    }
    
    if (root->left_child == nullptr) {
        return root;
    }
    
    return minimum(root->left_child);
}

void insertFixup(HybridNode* z) {
    while (z->parent && z->parent->color == "red") {
        HybridNode* parent = z->parent;
        HybridNode* grandparent = parent->parent;

        if (parent == grandparent->left_child) {
            HybridNode* uncle = grandparent->right_child;

            if (uncle && uncle->color == "red") {
                // Case 1: Uncle is red
                parent->color = "black";
                uncle->color = "black";
                grandparent->color = "red";
                z = grandparent;
            } else {
                if (z == parent->right_child) {
                    // Case 2: Uncle is black, and z is a right child
                    z = parent;
                    leftRotate(z);
                }

                // Case 3: Uncle is black, and z is a left child
                parent->color = "black";
                grandparent->color = "red";
                rightRotate(grandparent);
            }
        } else {
            // Symmetric cases for the right child
            HybridNode* uncle = grandparent->left_child;

            if (uncle && uncle->color == "red") {
                // Case 1: Uncle is red
                parent->color = "black";
                uncle->color = "black";
                grandparent->color = "red";
                z = grandparent;
            } else {
                if (z == parent->left_child) {
                    // Case 2: Uncle is black, and z is a left child
                    z = parent;
                    rightRotate(z);
                }

                // Case 3: Uncle is black, and z is a right child
                parent->color = "black";
                grandparent->color = "red";
                leftRotate(grandparent);
            }
        }
    }
    root->color = "black";
}

void setLeftChild(HybridNode* parent, HybridNode* child) {
    parent->left_child = child;
}

void setRightChild(HybridNode* parent, HybridNode* child) {
    parent->right_child = child;
}

    HybridNode* insert(string key, string element) {
    // Create a new node and initialize the histogram
    Histogram[key][element]++;
    HybridNode* z = new HybridNode(key, element);

    // Initialize parent and current node
    HybridNode* parent = nullptr;
    HybridNode* current = getRoot();

    while (current != nullptr) {
        parent = current;
        if (key == current->key) {
            return root;
        }
        if (key < current->key) {
            current = current->left_child;
        } else {
            current = current->right_child;
        }
    }

    // Set parent for the new node
    z->parent = parent;

    // Set the new node as the root if the tree was empty
    if (parent == nullptr) {
        setRoot(z);
    } else {
        if (key < parent->key) {
            setLeftChild(parent, z);
        } else {
            setRightChild(parent, z);
        }
    }

    // Perform the Red-Black Tree fixup
    insertFixup(z);

    return z;
}

void deleteHelper(HybridNode* v) {
    HybridNode* u = BSTreplace(v);

    bool uvBlack = ((u == nullptr || u->color == "black") && (v->color == "black"));
    HybridNode* parent = v->parent;

    if (u == nullptr) {
        handleLeafNodeDeletion(v, parent);
    } else if (v->left_child == nullptr || v->right_child == nullptr) {
        handleNodeWithOneChildDeletion(v, u, parent, uvBlack);
    } else {
        swapValuesAndRecursivelyDelete(u, v);
    }
}

void handleLeafNodeDeletion(HybridNode* v, HybridNode* parent) {
    if (v == root) {
        handleRootLeafDeletion();
    } else {
        HybridNode* u = BSTreplace(v);
        bool uvBlack = ((u == nullptr || u->color == "black") && (v->color == "black"));
        if (uvBlack) {
            handleDoubleBlackAtLeafNode(v);
        } else {
            handleRedSiblingAtLeafNode(v);
        }

        deleteNodeFromTree(v, parent);
    }
}

void handleRootLeafDeletion() {
    root = nullptr;
}

void handleDoubleBlackAtLeafNode(HybridNode* v) {
    fixDoubleBlack(v);
}

void handleRedSiblingAtLeafNode(HybridNode* v) {
    if (v->sibling() != nullptr) {
        v->sibling()->color = "red";
    }
}

void deleteNodeFromTree(HybridNode* v, HybridNode* parent) {
    if (v->isOnLeft()) {
        parent->left_child = nullptr;
    } else {
        parent->right_child = nullptr;
    }

    delete v;
}

void handleNodeWithOneChildDeletion(HybridNode* v, HybridNode* u, HybridNode* parent, bool uvBlack) {
    if (v == root) {
        handleRootNodeWithOneChildDeletion(v, u);
    } else {
        detachNodeAndMoveUp(v, u, parent);
        deleteNodeAndUpdateColor(u, parent, uvBlack);
    }
}

void handleRootNodeWithOneChildDeletion(HybridNode* v, HybridNode* u) {
    v->key = u->key;
    v->left_child = v->right_child = nullptr;
    delete u;
}

void detachNodeAndMoveUp(HybridNode* v, HybridNode* u, HybridNode* parent) {
    if (v->isOnLeft()) {
        parent->left_child = u;
    } else {
        parent->right_child = u;
    }

    u->parent = parent;
}

void deleteNodeAndUpdateColor(HybridNode* u, HybridNode* parent, bool uvBlack) {
    if (uvBlack) {
        fixDoubleBlack(u);
    } else {
        u->color = "black";
    }
}

void swapValuesAndRecursivelyDelete(HybridNode* u, HybridNode* v) {
    swapValues(u, v);
    deleteHelper(u);
}

    bool deleteNode(string key){
     HybridNode * to_be_del = search(key);
    deleteHelper(to_be_del);
    return 1;
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
    preOrderHelper(node, result, depth);
    return result;
    }

void preOrderHelper(HybridNode* node, vector<HybridNode*>& result, int depth) {
    if (node == nullptr || depth < 0) {
        return;
    }

    result.push_back(node);
    preOrderHelper(node->left_child, result, depth - 1);
    preOrderHelper(node->right_child, result, depth - 1);
}


    HybridNode* search(string key) {
    HybridNode* current = getRoot(); // Start at the root

    while (current != nullptr && key != current->key) {
        current = (key < current->key) ? current->left_child : current->right_child;
    }

    return current;
}

    
    int blackheight(HybridNode* node) {
    if (node == nullptr) {
        return 0; // The black height of a null node is 0
    }

    int blackHeight = 0;
    HybridNode* current = node;

    while (current != nullptr) {
        if (current->color == "black") {
            blackHeight++; // Increment the black height when the node is black
        }
        current = current->left_child; // Traverse down the left child
    }

    // Now, 'blackHeight' contains the black height of the given node
    return blackHeight;
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
    
     vector <string> get_words_from_chapter(string chapterName){
     vector<string> words;
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

    vector <string> chapters;

    void readChapters(vector<string> chapter_names) { 
 chapters = chapter_names;
 // Process words from a chapter and update the Red-Black Tree
 // chapter_names is a vector of chapter names
 for(int i=0;i<chapter_names.size();i++){
 vector <string> chapterWords = get_words_from_chapter(chapter_names[i]);
 for(int j=0;j<chapterWords.size();j++){
 red_black_tree.insert(chapterWords[j],chapter_names[i].substr(0,chapter_names[i].size()-4));
 }
 }


 vector <string> to_be_pruned;
 
 auto it=Histogram.begin();
 while(it!=Histogram.end()){
 if(it->second.size()==chapter_names.size()){
 unordered_map <string,int> changed;
 to_be_pruned.push_back(it->first);
 }
 it++;
 }
 for(int i=0;i<to_be_pruned.size();i++){
 red_black_tree.deleteNode(to_be_pruned[i]);
 }
 return ;
 }

 vector<IndexEntry> buildIndex() {
 vector <IndexEntry> result;
 auto it = Histogram.begin();
 while(it!=Histogram.end()){
 if(it->second.size()!=chapters.size()){
 string word = it->first;
 IndexEntry result_part(word);
 unordered_map<string, int> visu = it->second;
 vector<pair<string, int>> huji;
 for(int i=0;i<chapters.size();i++){
 pair <string,int> paired (chapters[i].substr(0,chapters[i].size()-4),visu[chapters[i].substr(0,chapters[i].size()-4)]);
 huji.push_back(paired);
 }
 result_part.setChapterWordCounts(huji);
 result.push_back(result_part);
 }
 it++;
 }
 return result;
 }
};

void inorder(HybridNode * root,int &count){
 if(root==NULL){
 return ;
 }
 count++;
 inorder(root->left_child,count);
 // cout<<root->key<<endl;
 inorder(root->right_child,count);
 return ;
}

void level_order (HybridNode* root){
 queue <HybridNode*> demo;
 cout<<root->key<<endl;
 demo.push(root);
 while(demo.size()!=0){
 int size=demo.size();
 for(int i=0;i<size;i++){
 HybridNode * first=demo.front();
 if(first->left_child!=NULL){
 demo.push(first->left_child);
 cout<<first->left_child->key<<" ";
 }
 if(first->right_child!=NULL){
 demo.push(first->right_child);
 cout<<first->right_child->key<<" ";
 }
 demo.pop();
 }
 cout<<endl;
 }
 return ;
};

