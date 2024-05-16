#include <bits/stdc++.h>
using namespace std;

unordered_map <string, unordered_map <string,int> > Histogram;

class HybridNode {
public:
 string key; // Word
 string element; // Chapter
 HybridNode* parent; // Parent node
 HybridNode* left_child; // Left child node
 HybridNode* right_child; // Right child node
 HybridNode* next_node; // Next node in the linked list
 string color = "red"; // Color of the node

 bool isOnLeft() { return this == parent->left_child; }
 HybridNode *uncle(){
 // If no parent or grandparent, then no uncle
 if (parent == NULL or parent->parent == NULL)
 return NULL;

 if (parent->isOnLeft())
 // uncle on right
 return parent->parent->right_child;
 else
 // uncle on left
 return parent->parent->left_child;
 }

 HybridNode *sibling(){
 // sibling null if no parent
 if (parent == NULL)
 return NULL;

 if (isOnLeft())
 return parent->right_child;

 return parent->left_child;
 }

 void moveDown(HybridNode *nParent){
 if (parent != NULL){
 if (isOnLeft()){
 parent->left_child = nParent;
 }
 else{
 parent->right_child = nParent;
 }
 }
 nParent->parent = parent;
 parent = nParent;
 }

 bool hasRedChild(){
 return (left_child != NULL and left_child->color == "red") ||
 (right_child != NULL and right_child->color == "red");
 }

 HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

class RedBlackTree {
private:
 HybridNode* root; // Root node

public:
 RedBlackTree() : root(nullptr) {}

 void swapColors(HybridNode *x1, HybridNode *x2){
 string temp;
 temp = x1->color;
 x1->color = x2->color;
 x2->color = temp;
 }

 void swapValues(HybridNode *u, HybridNode *v){
 string temp;
 temp = u->key;
 u->key = v->key;
 v->key = temp;
 }

 void fixRedRed(HybridNode *x){
 // if x is root color it black and return
 if (x == root){
 x->color = "black";
 return;
 }

 // initialize parent, grandparent, uncle
 HybridNode *parent = x->parent, *grandparent = parent->parent,
 *uncle = x->uncle();

 if (parent->color != "black"){
 if (uncle != NULL && uncle->color == "red"){
 // uncle red, perform recoloring and recurse
 parent->color = "black";
 uncle->color = "black";
 grandparent->color = "red";
 fixRedRed(grandparent);
 }
 else{
 // Else perform LR, LL, RL, RR
 if (parent->isOnLeft()){
 if (x->isOnLeft()){
 // for left right
 swapColors(parent, grandparent);
 }
 else{
 leftRotate(parent);
 swapColors(x, grandparent);
 }
 // for left left and left right
 rightRotate(grandparent);
 }
 else{
 if (x->isOnLeft()){
 // for right left
 rightRotate(parent);
 swapColors(x, grandparent);
 }
 else{
 swapColors(parent, grandparent);
 }

 // for right right and right left
 leftRotate(grandparent);
 }
 }
 }
 }

 HybridNode *successor(HybridNode *x){
 HybridNode *temp = x;

 while (temp->left_child != NULL)
 temp = temp->left_child;

 return temp;
 }

 HybridNode *BSTreplace(HybridNode *x){
 // when node have 2 children
 if (x->left_child != NULL and x->right_child != NULL)
 return successor(x->right_child);

 // when leaf
 if (x->left_child == NULL and x->right_child == NULL)
 return NULL;

 // when single child
 if (x->left_child != NULL)
 return x->left_child;
 else
 return x->right_child;
 }

 void fixDoubleBlack(HybridNode *x){
 if (x == root)
 // Reached root
 return;

 HybridNode *sibling = x->sibling(), *parent = x->parent;
 if (sibling == NULL){
 // No sibling, double black pushed up
 fixDoubleBlack(parent);
 }
 else{
 if (sibling->color == "red"){
 // Sibling red
 parent->color = "red";
 sibling->color = "black";
 if (sibling->isOnLeft()){
 // left case
 rightRotate(parent);
 }
 else{
 // right case
 leftRotate(parent);
 }
 fixDoubleBlack(x);
 }
 else{
 // Sibling black
 if (sibling->hasRedChild()){
 // at least 1 red children
 if (sibling->left_child != NULL and sibling->left_child->color == "red"){
 if (sibling->isOnLeft()){
 // left left
 sibling->left_child->color = sibling->color;
 sibling->color = parent->color;
 rightRotate(parent);
 }
 else{
 // right left
 sibling->left_child->color = parent->color;
 rightRotate(sibling);
 leftRotate(parent);
 }
 }
 else{
 if (sibling->isOnLeft()){
 // left right
 sibling->right_child->color = parent->color;
 leftRotate(sibling);
 rightRotate(parent);
 }
 else{
 // right right
 sibling->right_child->color = sibling->color;
 sibling->color = parent->color;
 leftRotate(parent);
 }
 }
 parent->color = "black";
 }
 else{
 // 2 black children
 sibling->color = "red";
 if (parent->color == "black")
 fixDoubleBlack(parent);
 else
 parent->color = "black";
 }
 }
 }
 }

 HybridNode* search(string key) {
 HybridNode *current = getRoot(); // Start at the root
 while (current != nullptr){
 if (key == current->key){
 return current; // Found the node with the given key
 }
 else if (key < current->key){
 current = current->left_child; // Go left
 }
 else{
 current = current->right_child; // Go right
 }
 }
 return nullptr;
 }

 bool present(HybridNode * root,string key){
 if(root==NULL){
 return 0;
 }
 if(root->key==key){
 return 1;
 }
 if(root->key<key){
 return present(root->right_child,key);
 }
 return present(root->left_child,key);
 }
 void leftRotate(HybridNode* x) {
 HybridNode* y = x->right_child;
 x->right_child = y->left_child;
 if (y->left_child != nullptr)
 y->left_child->parent = x;
 y->parent = x->parent;
 if (x->parent == nullptr)
 root = y;
 else if (x == x->parent->left_child)
 x->parent->left_child = y;
 else
 x->parent->right_child = y;
 y->left_child = x;
 x->parent = y;
 }

 void rightRotate(HybridNode* y) {
 HybridNode* x = y->left_child;
 y->left_child = x->right_child;
 if (x->right_child != nullptr)
 x->right_child->parent = y;
 x->parent = y->parent;
 if (y->parent == nullptr)
 root = x;
 else if (y == y->parent->left_child)
 y->parent->left_child = x;
 else
 y->parent->right_child = x;
 x->right_child = y;
 y->parent = x;
 }

 HybridNode * minimum(HybridNode * root){
 if(root==NULL){
 return root;
 }
 while(root->left_child!=NULL){
 root=root->left_child;
 }
 return root;
 }

 void insertFixup(HybridNode* z) {
 while (z->parent && z->parent->color == "red") {
 if (z->parent == z->parent->parent->left_child) {
 HybridNode* y = z->parent->parent->right_child;
 if (y && y->color == "red") {
 z->parent->color = "black";
 y->color = "black";
 z->parent->parent->color = "red";
 z = z->parent->parent;
 } else {
 if (z == z->parent->right_child) {
 z = z->parent;
 leftRotate(z);
 }
 z->parent->color = "black";
 z->parent->parent->color = "red";
 rightRotate(z->parent->parent);
 }
 } else {
 HybridNode* y = z->parent->parent->left_child;
 if (y && y->color == "red") {
 z->parent->color = "black";
 y->color = "black";
 z->parent->parent->color = "red";
 z = z->parent->parent;
 } else {
 if (z == z->parent->left_child) {
 z = z->parent;
 rightRotate(z);
 }
 z->parent->color = "black";
 z->parent->parent->color = "red";
 leftRotate(z->parent->parent);
 }
 }
 }
 root->color = "black";
 }

 HybridNode* getRoot() {
 return root; // Return the root node
 }

 void setRoot(HybridNode* node) {
 root = node; // Set the root node
 }

 HybridNode* insert(string key, string element) {
 // Implement Red-Black Tree insertion
 Histogram[key][element]++;
 HybridNode* z = new HybridNode(key, element);
 HybridNode* y = nullptr;
 HybridNode* x = getRoot(); // Get the current root

 while (x != nullptr) {
 y = x;
 if(key==x->key){
 return root;
 }
 if (key < x->key)
 x = x->left_child;
 else
 x = x->right_child;
 }
 z->parent = y;
 if (y == nullptr)
 setRoot(z); // Set the new node as the root if the tree was empty
 else if (key < y->key)
 y->left_child = z;
 else
 y->right_child = z;

 insertFixup(z);
 return z;
 }

 void deleteHelper(HybridNode* v) {
 // Implement Red-Black Tree deletion
 HybridNode *u = BSTreplace(v);

 // True when u and v are both black
 bool uvBlack = ((u == NULL or u->color == "black") and (v->color == "black"));
 HybridNode *parent = v->parent;

 if (u == NULL){
 // u is NULL therefore v is leaf
 if (v == root){
 // v is root, making root null
 root = NULL;
 }
 else{
 if (uvBlack){
 // u and v both black
 // v is leaf, fix double black at v
 fixDoubleBlack(v);
 }
 else{
 // u or v is red
 if (v->sibling() != NULL)
 // sibling is not null, make it red"
 v->sibling()->color = "red";
 }

 // delete v from the tree
 if (v->isOnLeft()){
 parent->left_child = NULL;
 }
 else{
 parent->right_child = NULL;
 }
 }
 delete v;
 return;
 }

 if (v->left_child == NULL or v->right_child == NULL){
 // v has 1 child
 if (v == root){
 // v is root, assign the value of u to v, and delete u
 v->key = u->key;
 v->left_child = v->right_child = NULL;
 delete u;
 }
 else{
 // Detach v from tree and move u up
 if (v->isOnLeft())
 {
 parent->left_child = u;
 }
 else
 {
 parent->right_child = u;
 }
 delete v;
 u->parent = parent;
 if (uvBlack)
 {
 // u and v both black, fix double black at u
 fixDoubleBlack(u);
 }
 else
 {
 // u or v red, color u black
 u->color = "black";
 }
 }
 return;
 }

 // v has 2 children, swap values with successor and recurse
 swapValues(u, v);
 deleteHelper(u);
 }

 bool deleteNode(string key){
 HybridNode * to_be_del = search(key);
 deleteHelper(to_be_del);

 return 1;
 }
 vector<HybridNode*> traverseUp(HybridNode* node) {
 // Traverse up the tree from the given node to the root
 // Return the vector of nodes in the path
 }

 vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
 // Traverse down the tree based on the bit sequence
 // Return the vector of nodes in the path
 }
 void prehelper(HybridNode * node,vector <HybridNode *> &result,int depth){
 if(node==NULL || depth==-1){
 return ;
 }
 result.push_back(node);
 prehelper(node->left_child,result,depth-1);
 prehelper(node->right_child,result,depth-1);

 return ;
 }
 vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
 // Perform pre-order traversal staying within specified depth
 vector <HybridNode *> result;
 prehelper(node,result,depth);

 return result;

 }
 
 int blackheight(HybridNode* node){
 // Implement blackheight
 if(node==NULL){
 return 0;
 }
 if(node->color=="black"){
 return 1+blackheight(node->left_child);
 }
 return blackheight(node->left_child);
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
 std::vector<std::string> words;
 std::ifstream file(chapterName);
 std::string word;

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
}