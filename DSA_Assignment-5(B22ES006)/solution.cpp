
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int totalStops = 0;
    MetroStop* currentStop = node;

    // Traverse the linked list and count the stops
    while (currentStop != nullptr) {
        totalStops++;
        currentStop = currentStop->getNextStop();
    }

    return totalStops;
}


void MetroLine::populateLine(std::string filename) {
    ifstream inputFile(filename); // Open the file
    if (!inputFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) { // Read lines one by one
        size_t spacePos = line.find_last_of(' '); // Find the last space character
        if (spacePos != std::string::npos && spacePos < line.length() - 1) {
            // Extract station name and fare from the line
            std::string stationName = line.substr(0, spacePos);
            int fare = std::stoi(line.substr(spacePos + 1));

            // Create a new MetroStop object for each station
            MetroStop* newStop = new MetroStop(stationName, this, fare);

            // Link the newStop to the end of the current line
            if (node == nullptr) {
                // If the line is empty, set the newStop as the first node
                node = newStop;
            } else {
                // Otherwise, find the last stop and link the newStop to it
                MetroStop* lastStop = node;
                while (lastStop->getNextStop() != nullptr) {
                    lastStop = lastStop->getNextStop();
                }
                lastStop->setNextStop(newStop);
                newStop->setPrevStop(lastStop);
            }
        }
    }

    inputFile.close(); // Close the file
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    AVLNode* rt=root;

    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    AVLNode* inserth(AVLNode* node, string key,AVLNode * newNode,MetroStop * linenode) {
        if (node == NULL) return newNode;

        if (stringCompare(key,node->getStopName())<0) {
            node->setLeft(inserth(node->getLeft(), key,newNode,linenode));
            node->getLeft()->setParent(node);
        }
        else if (stringCompare(key,node->getStopName())>0) {
            node->setRight(inserth(node->getRight(), key,newNode,linenode)) ;
            node->getRight()->setParent(node);
        }
        else{
            node->addMetroStop(linenode);
            return node;
        }
        int balance = balanceFactor(node);

        // Left Heavy
        if (balance > 1 && stringCompare(key,node->getLeft()->getStopName())<0)
            return rotateRight(node);

        // Right Heavy
        if (balance < -1 && stringCompare(key,node->getRight()->getStopName())>0)
            return rotateLeft(node);

        // Left Right Heavy
        if (balance > 1 && stringCompare(key,node->getLeft()->getStopName())>0) {
            node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }

        // Right Left Heavy
        if (balance < -1 && stringCompare(key,node->getRight()->getStopName())<0) {
            node->setRight(rotateRight(node->getRight())) ;
            return rotateLeft(node);
        }
        return node;
    }    
    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);

    AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->getLeft();
    AVLNode* T = x->getRight();

    x->setRight(y);
    y->setLeft(T);

    y->setParent(x);
    T ? T->setParent(y) : void();

    return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->getRight();
    AVLNode* T = y->getLeft();

    y->setLeft(x);
    x->setRight(T);

    x->setParent(y);
    T ? T->setParent(x) : void();

    return y;
    }


    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node,MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if (node == nullptr) {
        return 0; // Height of an empty tree is 0
    }

    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());

    return 1 + max(leftHeight, rightHeight);
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    int leftHeight, rightHeight;

    if (node->getLeft() != nullptr) {
        leftHeight = height(node->getLeft());
    } else {
        leftHeight = 0;
    }

    if (node->getRight() != nullptr) {
        rightHeight = height(node->getRight());
    } else {
        rightHeight = 0;
    }

    return leftHeight - rightHeight;
}

// void AVLTree::balance(AVLNode* node) {

// }

void AVLTree::insert(AVLNode* newNode, MetroStop* metroStop) {
    MetroStop* linenode=metroStop->getLine()->getNode();
    newNode->addMetroStop(metroStop);
    setRoot(inserth(root,newNode->getStopName(),newNode,metroStop));
    return ;
}

void AVLTree::populateTree(MetroLine* metroLine) {
    vector<AVLNode*> nodes;
    MetroStop* currentNode = metroLine->getNode();

    while (currentNode != nullptr) {
        AVLNode* newNode = new AVLNode(currentNode->getStopName());
        insert(newNode, currentNode);
        nodes.push_back(newNode);  // Add the newly created node to the vector

        currentNode = currentNode->getNextStop();
    }

    // Now, if you need to access the nodes later, you can use the 'nodes' vector.
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively traverse the left subtree
    inOrderTraversal(node->getLeft());

    // Process the current node (e.g., print its value or perform some other operation)
    cout << node->getStopName() << endl;

    // Recursively traverse the right subtree
    inOrderTraversal(node->getRight());
}


int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0; // Base case: an empty subtree has 0 nodes
    }

    // Recursively count nodes in the left and right subtrees
    int leftCount = getTotalNodes(node->getLeft());
    int rightCount = getTotalNodes(node->getRight());

    // Add 1 for the current node itself
    return 1 + leftCount + rightCount;
}


AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* currentNode = getRoot();

    while (currentNode != nullptr) {
        int cmp = stringCompare(stopName, currentNode->getStopName());

        if (cmp == 0) {
            // Found a node with the matching stop name
            return currentNode;
        } else if (cmp < 0) {
            // Search in the left subtree
            currentNode = currentNode->getLeft();
        } else {
            // Search in the right subtree
            currentNode = currentNode->getRight();
        }
    }

    // Stop name not found in the AVL tree
    return nullptr;
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();
    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    void setStops(vector<MetroStop*>demo){
        stops=demo;
        return;
    }

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    void createAVLTree();
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    Path* findPath(std::string origin, std::string destination);
    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree=avlTree;
    lines=metroLines;

}
AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    AVLTree* demotree = new AVLTree();

    // Initialize the tree's root as nullptr
    demotree->setRoot(nullptr);

    for (MetroLine* line : lines) {
        demotree->setRoot(demotree->getRoot() == nullptr ? new AVLNode(line->getNode()->getStopName()) : demotree->getRoot());
        // Populate the tree with stops from the current MetroLine
        demotree->populateTree(line);
    }

    // Set the AVL tree as the tree for PathFinder
    tree->setRoot(demotree->getRoot());
}

Path* PathFinder::findPath(string origin, string destination) {
    AVLNode* ori = tree->searchStop(origin);
    AVLNode* dest = tree->searchStop(destination);

    (ori == nullptr || dest == nullptr) ? (cout << "Invalid origin or destination stop." << endl, nullptr) : nullptr;

    map<Path*, int> paths;
    Trip* initialTrip = new Trip(ori->getStops()[0], nullptr);
    Exploration* explore = new Exploration();
    explore->enqueue(initialTrip);
    map<MetroStop*, int> visited;

    while (!explore->isEmpty()) {
    Trip* currentTrip = explore->dequeue();
    MetroStop* currentStop = currentTrip->getNode();

    if (currentStop == nullptr || visited[currentStop] == 1) {
        continue;
    }
    if (currentStop == dest->getStops()[0]) {
        Path* path = new Path();
        Trip* temp = currentTrip;

        while (temp != nullptr) {
            path->addStop(temp->getNode());
            temp = temp->getPrev();
        }

        vector<MetroStop*> demo = path->getStops();
        path->setStops(demo);

        int totalFare = 0;
        for (int i = 1; i < demo.size(); i++) {
            if (demo[i]->getLine() == demo[i - 1]->getLine()) {
                totalFare += abs(demo[i]->getFare() - demo[i - 1]->getFare());
            } else {
                string stop1 = demo[i]->getStopName();
                string stop2 = demo[i - 1]->getStopName();
                int found = 0;

                for (int j = 0; j < lines.size() && found == 0; j++) {
                    MetroStop* first = nullptr;
                    MetroStop* second = nullptr;
                    MetroStop* hehe = lines[j]->getNode();

                    while (hehe != nullptr) {
                        if (hehe->getStopName() == stop1) {
                            first = hehe;
                        }
                        if (hehe->getStopName() == stop2) {
                            second = hehe;
                        }
                        hehe = hehe->getNextStop();
                    }

                    if (first != nullptr && second != nullptr) {
                        totalFare += abs(first->getFare() - second->getFare());
                        found = 1;
                    }
                }
            }
        }

        path->setTotalFare(totalFare);
        paths[path] = totalFare;
        continue;
    }

    if (tree->searchStop(currentStop->getStopName())->getStops().size() == 1) {
        MetroStop* nextStop = currentStop->getNextStop();
        MetroStop* prevStop = currentTrip->getNode()->getPrevStop();

        if (visited[nextStop] == 0 && nextStop != nullptr) {
            Trip* nextTripForward = new Trip(nextStop, currentTrip);
            explore->enqueue(nextTripForward);
        }
        if (visited[prevStop] == 0 && prevStop != nullptr) {
            Trip* nextTripBackward = new Trip(prevStop, currentTrip);
            explore->enqueue(nextTripBackward);
        }
    }

    if (tree->searchStop(currentStop->getStopName())->getStops().size() > 1) {
    vector<MetroStop*> stops = tree->searchStop(currentStop->getStopName())->getStops();
    for (int i = 0; i < stops.size(); i++) {
        auto nextStop = stops[i]->getNextStop();
        auto prevStop = stops[i]->getPrevStop();

        auto isVisitedNext = (nextStop != nullptr && visited[nextStop] == 0);
        auto isVisitedPrev = (prevStop != nullptr && visited[prevStop] == 0);

        if (isVisitedNext) {
            explore->enqueue(new Trip(nextStop, currentTrip));
        }
        if (isVisitedPrev) {
            explore->enqueue(new Trip(prevStop, currentTrip));
        }
    }
}
    visited[currentStop] = 1;
}
    Path* result = nullptr;
    int min_fare = 1000;

    for (const auto& entry : paths) {
    const Path* path = entry.first;
    int fare = entry.second;

    vector<MetroStop*> stops = path->getStops();
    for (const MetroStop* stop : stops) {
    }

    if (fare < min_fare) {
        min_fare = fare;
        result = const_cast<Path*>(path);  // Cast away const for assignment
    }
    }


    return result;
}
vector<MetroLine*> lines;

