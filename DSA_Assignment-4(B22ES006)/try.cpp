#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Vehicle;
class Trip {
public:
    Trip(Vehicle* vehicle, string pick_up_location, string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    string getPickUpLocation() const {
        return pick_up_location;
    }

    string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(string location) {
        pick_up_location = location;
    }

    void setDropLocation(string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    string pick_up_location;
    string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

class TransportService {
public:
    TransportService(string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

void TransportService::add_trip(int departure_time, Trip* trip) {
    // If the BST is empty, set the new node as the head
    if (BSThead == nullptr) {
        BSThead = new BinaryTreeNode(departure_time, trip);
        return;
    }

    BinaryTreeNode* current = BSThead;
    BinaryTreeNode* parent = nullptr;

    // Traverse the BST to find the appropriate position to insert the new node
    while (current != nullptr) {
        parent = current;
        if (departure_time < current->getDepartureTime()) {
            current = current->getLeftPtr();
        } else {
            current = current->getRightPtr();
        }
    }

    // Insert the new node based on the departure time key
    if (departure_time < parent->getDepartureTime()) {
        parent->setLeftPtr(new BinaryTreeNode(departure_time, trip));
    } else {
        parent->setRightPtr(new BinaryTreeNode(departure_time, trip));
    }
}


private:
    string name;
    BinaryTreeNode* BSThead;
};

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class Vehicle {
public:
    Vehicle(string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    const vector <Trip*>getTrips() const{
        return trips;
    }

private:
    string vehicle_number;
    int seating_capacity;
    vector<Trip*> trips;
};

class Location {
public:
    Location(string name) : name(name) {}

    // Getter functions
    string getName() const {
        return name;
    }

    TransportService* getServicePtr(string droplocation) {
    // Iterate through existing services associated with this Location
    for (TransportService* service : serviceptrs) {
        if (service->getName() == droplocation) {
            return service; // Return the service with the matching drop location
        }
    }
    
    // Since a distinct service object is created for every distinct drop location,
    // and all services associated with a Location have the same pick-up location,
    // there is no need to return nullptr in this case.
    // Instead, create and return a new TransportService with the given drop location.
    TransportService* newService = new TransportService(droplocation);
    serviceptrs.push_back(newService);
    return newService; // Return the newly created service
}


    // Setter functions
    void setName(string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(string droplocation) {
    // Check if a Service with the given drop location already exists
    for (TransportService* service : serviceptrs) {
        if (service->getName() == droplocation) {
            return service; // Return the existing service
        }
    }

    // If not, create a new Service and add it to the serviceptrs vector
    TransportService* newService = new TransportService(droplocation);
    serviceptrs.push_back(newService);
    return newService; // Return the newly created service
}


    void add_trip(Trip* trip) {
        trips.push_back(trip);
    }

    vector <Trip*>getTrips() {
        return trips;
    }


private:
    string name;
    vector<TransportService* >serviceptrs;
    vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return 0; // Height of an empty tree is 0
    } else {
        // Recursively compute the height of the left and right subtrees
        int leftHeight = getHeight(node->getLeftPtr());
        int rightHeight = getHeight(node->getRightPtr());

        // Return the height of the tree, which is the maximum of left and right subtree heights, plus 1 (for the current node)
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    }

int getNumberOfNodes(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return 0; // Number of nodes in an empty tree is 0
    } else {
        // Recursively compute the number of nodes in the left and right subtrees
        int leftNodes = getNumberOfNodes(node->getLeftPtr());
        int rightNodes = getNumberOfNodes(node->getRightPtr());

        // Return the total number of nodes in the tree, which is the sum of nodes in the left and right subtrees, plus 1 (for the current node)
        return leftNodes + rightNodes + 1;
    }
}
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
    BinaryTreeNode* currentNode = root;

    // Traverse to the leftmost node (minimum key)
    while (currentNode != nullptr && currentNode->getLeftPtr() != nullptr) {
        currentNode = currentNode->getLeftPtr();
    }

    return currentNode;
}

    BinaryTreeNode* getElementWithMaximumKey() const {
    BinaryTreeNode* currentNode = root;

    // Traverse to the rightmost node (maximum key)
    while (currentNode != nullptr && currentNode->getRightPtr() != nullptr) {
        currentNode = currentNode->getRightPtr();
    }

    return currentNode;
}

    BinaryTreeNode* searchNodeWithKey(int key) const {
    BinaryTreeNode* currentNode = root;
    BinaryTreeNode* result = nullptr;

    while (currentNode != nullptr) {
        if (key < currentNode->getDepartureTime()) {
            // The key is smaller than the current node's key, go left
            result = currentNode;
            currentNode = currentNode->getLeftPtr();
        } else if (key > currentNode->getDepartureTime()) {
            // The key is larger than the current node's key, go right
            currentNode = currentNode->getRightPtr();
        } else {
            // Key matches the current node's key
            return currentNode;
        }
    }

    return result;
}

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return nullptr; // Invalid input
    }

    // Case 1: If the right subtree is not empty, find the leftmost node in the right subtree
    if (node->getRightPtr() != nullptr) {
        node = node->getRightPtr();
        while (node->getLeftPtr() != nullptr) {
            node = node->getLeftPtr();
        }
        return node;
    }

    // Case 2: If the right subtree is empty, backtrack to find the ancestor
    BinaryTreeNode* successor = nullptr;
    BinaryTreeNode* current = root;

    while (current != nullptr) {
        if (node->getDepartureTime() < current->getDepartureTime()) {
            successor = current;
            current = current->getLeftPtr();
        } else if (node->getDepartureTime() > current->getDepartureTime()) {
            current = current->getRightPtr();
        } else {
            break; // Node found, should not reach here
        }
    }

    return successor;
}

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
    BinaryTreeNode* currentNode = root;
    BinaryTreeNode* successor = nullptr;

    while (currentNode != nullptr) {
        if (key < currentNode->getDepartureTime()) {
            successor = currentNode; // Update successor as the current node
            currentNode = currentNode->getLeftPtr();
        } else if (key > currentNode->getDepartureTime()) {
            currentNode = currentNode->getRightPtr();
        } else {
            // Key matches the current node's key
            if (currentNode->getRightPtr() != nullptr) {
                // Case 1: If the right subtree is not empty, find the leftmost node in the right subtree
                currentNode = currentNode->getRightPtr();
                while (currentNode->getLeftPtr() != nullptr) {
                    currentNode = currentNode->getLeftPtr();
                }
                return currentNode;
            } else {
                // Case 2: If the right subtree is empty, return the last ancestor where we moved left
                return successor;
            }
        }
    }

    return nullptr; // Key not found
}

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return nullptr; // Invalid input
    }

    // Case 1: If the left subtree is not empty, find the rightmost node in the left subtree
    if (node->getLeftPtr() != nullptr) {
        node = node->getLeftPtr();
        while (node->getRightPtr() != nullptr) {
            node = node->getRightPtr();
        }
        return node;
    }

    // Case 2: If the left subtree is empty, backtrack to find the ancestor
    BinaryTreeNode* predecessor = nullptr;
    BinaryTreeNode* current = root;

    while (current != nullptr) {
        if (node->getDepartureTime() > current->getDepartureTime()) {
            predecessor = current;
            current = current->getRightPtr();
        } else if (node->getDepartureTime() < current->getDepartureTime()) {
            current = current->getLeftPtr();
        } else {
            break; // Node found, should not reach here
        }
    }

    return predecessor;
}

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
    BinaryTreeNode* currentNode = root;
    BinaryTreeNode* predecessor = nullptr;

    while (currentNode != nullptr) {
        if (key < currentNode->getDepartureTime()) {
            currentNode = currentNode->getLeftPtr();
        } else if (key > currentNode->getDepartureTime()) {
            predecessor = currentNode; // Update predecessor as the current node
            currentNode = currentNode->getRightPtr();
        } else {
            // Key matches the current node's key
            if (currentNode->getLeftPtr() != nullptr) {
                // Case 1: If the left subtree is not empty, find the rightmost node in the left subtree
                currentNode = currentNode->getLeftPtr();
                while (currentNode->getRightPtr() != nullptr) {
                    currentNode = currentNode->getRightPtr();
                }
                return currentNode;
            } else {
                // Case 2: If the left subtree is empty, return the last ancestor where we moved right
                return predecessor;
            }
        }
    }

    return nullptr; // Key not found
}
};

class TravelDesk {
public:
void addTrip(string vehicle_number, int seating_capacity, string pick_up_location, string drop_location, int departure_time) {
    // Step 1: Check if the vehicle with the given number already exists
    Vehicle* vehicle = nullptr;
    for (Vehicle* existingVehicle : vehicles) {
        if (existingVehicle->getVehicleNumber() == vehicle_number) {
            vehicle = existingVehicle;
            break;
        }
    }

    // Step 2: If the vehicle doesn't exist, create a new vehicle and add it to the list
    if (vehicle == nullptr) {
        vehicle = new Vehicle(vehicle_number, seating_capacity);
        vehicles.push_back(vehicle);
    }

    // Step 3: Create a new trip object
    Trip* newTrip = new Trip(vehicle, pick_up_location, drop_location, departure_time);

    // Step 4: Find the Location object associated with the pick-up location
    Location* pickUpLocationObject = getLocation(pick_up_location);

    // Step 5: Add the trip to the vehicle
    vehicle->addTrip(newTrip);

    // Step 6: Add the trip to the Location object associated with the pick-up location
    if (pickUpLocationObject != nullptr) {
        pickUpLocationObject->add_trip(newTrip);
    } else {
        // If the Location object doesn't exist, create it and add the trip
        pickUpLocationObject = new Location(pick_up_location);
        pickUpLocationObject->add_trip(newTrip);
        locations.push_back(pickUpLocationObject);
    }

    // Step 7: Find the Service object corresponding to the pickup-drop location pair
    TransportService* service = pickUpLocationObject->setServicePtr(drop_location);

    // Step 8: Create a new BinaryTreeNode for the trip and insert it into the BST
    BinaryTreeNode* newNode = new BinaryTreeNode(departure_time, newTrip);
    
    // Perform the BST insert operation using the departure time as the key
    // (You might need to implement this logic in the TransportService class)
    service->add_trip(departure_time, newnode);
}


std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
    std::vector<Trip*> result;

    // Step 1: Identify the Location object for the pick-up location
    Location* pickupLocation = getLocation(pick_up_location);

    if (pickupLocation != nullptr) {
        // Step 2: Access the TransportService object for the destination (e.g., Poata)
        TransportService* transportService = pickupLocation->getServicePtr("Poata");

        if (transportService != nullptr) {
            // Step 3: Find the node with the indicated begin time (after_time)
            BinaryTreeNode* currentNode = transportService->getBSTHead();
            while (currentNode != nullptr && currentNode->getDepartureTime() < after_time) {
                currentNode = transportService->getSuccessorNode(currentNode);
            }

            // Step 4: Repeatedly call successor function until departure time is after end time
            while (currentNode != nullptr && currentNode->getDepartureTime() <= before_time) {
                result.push_back(currentNode->getTripNodePtr());
                currentNode = transportService->getSuccessorNode(currentNode);
            }
        }
    }

    return result;
}


    // Helper function for in-order traversal of the BST
    void inOrderTraversal(BinaryTreeNode* node, int after_time, int before_time, vector<Trip*>& result) {
    if (node == nullptr) {
        return;
    }

    // Recursively traverse the left subtree
    inOrderTraversal(node->getLeftPtr(), after_time, before_time, result);

    // Check if the departure time falls within the specified time range
    int departure_time = node->getDepartureTime();
    if (departure_time >= after_time && departure_time <= before_time) {
        result.push_back(node->getTripNodePtr());
    }

    // Recursively traverse the right subtree
    inOrderTraversal(node->getRightPtr(), after_time, before_time, result);
    }

    vector<Trip*> showTripsbydestination(string pick_up_location, string destination, int after_time, int before_time) {
    vector<Trip*> result;

    // Step 1: Identify the Location object for the pick-up location
    Location* pickupLocation = getLocation(pick_up_location);

    if (pickupLocation != nullptr) {
        // Step 2: Access the TransportService object for the destination
        TransportService* transportService = pickupLocation->getServicePtr(destination);

        if (transportService != nullptr) {
            // Step 3: Perform in-order traversal of the BST within the TransportService object
            inOrderTraversal(transportService->getBSTHead(), after_time, before_time, result);
        }
    }

    return result;
}

Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
    // Step 1: Find the Location object for the pick-up location
    Location* pickupLocation = getLocation(pick_up_location);

    if (pickupLocation != nullptr) {
        // Step 2: Search for the trip with the provided details
        std::vector<Trip*> trips = pickupLocation->getTrips();
        for (Trip* trip : trips) {
            if (trip->getDropLocation() == drop_location &&
                trip->getVehicle()->getVehicleNumber() == vehicle_number &&
                trip->getDepartureTime() == departure_time &&
                trip->getBookedSeats() < trip->getVehicle()->getSeatingCapacity()) {
                // Step 3: Increase the number of booked seats for the trip
                trip->setBookedSeats(trip->getBookedSeats() + 1);

                // Step 4: Check if the booked seats reached the vehicle's carrying capacity
                if (trip->getBookedSeats() == trip->getVehicle()->getSeatingCapacity()) {
                    // If so, remove the corresponding node from the BST
                    Location* dropLocation = getLocation(drop_location);
                    if (dropLocation != nullptr) {
                        TransportService* transportService = dropLocation->getServicePtr(drop_location);
                        if (transportService != nullptr) {
                            transportService->remove_trip(departure_time);
                        }
                    }
                }

                // Step 5: Return the modified trip object
                return trip;
            }
        }
    }

    // Step 6: If no matching trip is found, return nullptr
    return nullptr;
}

    Location* getLocation(string location){
        for(int i=0;i<locations.size();++i){
            if(locations[i]->getName()==location){
                return locations[i];
            }
        }
        return nullptr;
    }

private:
    vector<Vehicle*> vehicles;
    vector<Location*> locations;
};

