#include <iostream>
#include <vector>
#include <map>
#include<queue>

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

    void addTrip(int key, Trip* trip){
        
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

    TransportService* getServicePtr(string droplocation) const {
        for (TransportService* service : serviceptrs) {
        if (service->getName() == droplocation) {
            return service; // Return the found TransportService
        }
        }
        return nullptr;
    }

    // Setter functions
    void setName(string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(string droplocation) {
     // Check if a TransportService with the given drop location already exists
    for (TransportService* service : serviceptrs) {
        if (service->getName() == droplocation) {
            return service; // Return the existing service
        }
    }

    // If not, create a new TransportService and add it to the serviceptrs vector
    TransportService* newService = new TransportService(droplocation);
    serviceptrs.push_back(newService);
    return newService; // Return the newly created service
    }

    void addTrip(Trip* trip) {
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

    int getHeight() const {
    if (root == NULL) {
        return 0;
    }

    int height = 0;
    queue<BinaryTreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            BinaryTreeNode* node = q.front();
            q.pop();

            if (node->getLeftPtr() != NULL) {
                q.push(node->getLeftPtr());
            }
            if (node->getRightPtr() != NULL) {
                q.push(node->getRightPtr());
            }
        }

        // Increment the height for each level
        height++;
    }

    return height;
    }
int gnon_help(BinaryTreeNode * root) const {
    if (root == NULL) {
        return 0;
    }

    return 1 + gnon_help(root->getLeftPtr()) + gnon_help(root->getRightPtr());
}
int getNumberOfNodes() const {
    return gnon_help(root);
}
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
    BinaryTreeNode* currentNode = root;
    while (currentNode != NULL && currentNode->getLeftPtr() != NULL) {
        currentNode = currentNode->getLeftPtr();
    }

    return currentNode;
}

    BinaryTreeNode* getElementWithMaximumKey() const {
    BinaryTreeNode* currentNode = root;

    // Traverse to the rightmost node (maximum key)
    while (currentNode != NULL && currentNode->getRightPtr() != NULL) {
        currentNode = currentNode->getRightPtr();
    }

    return currentNode;
}

BinaryTreeNode* searchNodeWithKey(int key) const {
    BinaryTreeNode* currentNode = root;
    while (currentNode != nullptr) {
        if (key == currentNode->getDepartureTime()) {
            return currentNode; // Key found, return the node
        } else if (key < currentNode->getDepartureTime()) {
            currentNode = currentNode->getLeftPtr();
        } else {
            currentNode = currentNode->getRightPtr();
        }
    }
    
    return nullptr; // Key not found, return nullptr
}



    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->getRightPtr() != nullptr) {
        node = node->getRightPtr();
        while (node->getLeftPtr() != nullptr) {
            node = node->getLeftPtr();
        }
        return node;
    }
    BinaryTreeNode* successor = nullptr;
    BinaryTreeNode* current = root;

    while (current != nullptr) {
        if (node->getDepartureTime() < current->getDepartureTime()) {
            successor = current;
            current = current->getLeftPtr();
        } else if (node->getDepartureTime() > current->getDepartureTime()) {
            current = current->getRightPtr();
        } else {
            break;
        }
    }

    return successor;
}

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
    BinaryTreeNode* currentNode = root;
    BinaryTreeNode* successor = nullptr;

    while (currentNode != nullptr) {
        if (key < currentNode->getDepartureTime()) {
            successor = currentNode; 
            currentNode = currentNode->getLeftPtr();
        } else if (key > currentNode->getDepartureTime()) {
            currentNode = currentNode->getRightPtr();
        } else {
            if (currentNode->getRightPtr() != nullptr) {
                currentNode = currentNode->getRightPtr();
                while (currentNode->getLeftPtr() != nullptr) {
                    currentNode = currentNode->getLeftPtr();
                }
                return currentNode;
            } else {
                return successor;
            }
        }
    }

    return nullptr;
}

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->getLeftPtr() != nullptr) {
        node = node->getLeftPtr();
        while (node->getRightPtr() != nullptr) {
            node = node->getRightPtr();
        }
        return node;
    }
    BinaryTreeNode* predecessor = nullptr;
    BinaryTreeNode* current = root;

    while (current != nullptr) {
        if (node->getDepartureTime() > current->getDepartureTime()) {
            predecessor = current;
            current = current->getRightPtr();
        } else if (node->getDepartureTime() < current->getDepartureTime()) {
            current = current->getLeftPtr();
        } else {
            break;
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
            predecessor = currentNode;
            currentNode = currentNode->getRightPtr();
        } else {
            if (currentNode->getLeftPtr() != nullptr) {
                currentNode = currentNode->getLeftPtr();
                while (currentNode->getRightPtr() != nullptr) {
                    currentNode = currentNode->getRightPtr();
                }
                return currentNode;
            } else {
                return predecessor;
            }
        }
    }

    return nullptr;
}
};

class TravelDesk {
public:
    void addTrip(std::string vehicleNumber, int seatingCapacity, std::string pickUpLocation, std::string dropLocation, int departureTime) {
    Vehicle* vehicle = findOrCreateVehicle(vehicleNumber, seatingCapacity);
    Trip* newTrip = new Trip(vehicle, pickUpLocation, dropLocation, departureTime);
    Location* pickUpLocationPtr = findOrCreatePickUpLocation(pickUpLocation, newTrip);
    addOrUpdateService(pickUpLocationPtr, dropLocation, departureTime, newTrip);
}

Vehicle* findOrCreateVehicle(std::string vehicleNumber, int seatingCapacity) {
    for (Vehicle* v : vehicles) {
        if (v->getVehicleNumber() == vehicleNumber) {
            return v;
        }
    }
    Vehicle* newVehicle = new Vehicle(vehicleNumber, seatingCapacity);
    vehicles.push_back(newVehicle);
    return newVehicle;
}

Location* findOrCreatePickUpLocation(std::string pickUpLocation, Trip* newTrip) {
    for (Location* loc : locations) {
        if (loc->getName() == pickUpLocation) {
            loc->addTrip(newTrip);
            return loc;
        }
    }
    Location* newLocation = new Location(pickUpLocation);
    newLocation->addTrip(newTrip);
    locations.push_back(newLocation);
    return newLocation;
}

void addOrUpdateService(Location* pickUpLocationPtr, std::string dropLocation, int departureTime, Trip* newTrip) {
    TransportService* dropLocationService = pickUpLocationPtr->getServicePtr(dropLocation);
    
    if (dropLocationService == nullptr) {
        dropLocationService = pickUpLocationPtr->setServicePtr(dropLocation);
        BinaryTreeNode* newNode = new BinaryTreeNode(departureTime);
        newNode->setTripNodePtr(newTrip);
        dropLocationService->setBSTHead(newNode);
    } else {
        insertIntoBST(dropLocationService->getBSTHead(), departureTime, newTrip);
    }
}

void insertIntoBST(BinaryTreeNode* currentNode, int departureTime, Trip* newTrip) {
    BinaryTreeNode* newNode = new BinaryTreeNode(departureTime);
    newNode->setTripNodePtr(newTrip);

    while (true) {
        if (currentNode->getDepartureTime() < departureTime) {
            if (currentNode->getRightPtr() == nullptr) {
                currentNode->setRightPtr(newNode);
                newNode->setParentPtr(currentNode);
                break;
            }
            currentNode = currentNode->getRightPtr();
        } else {
            if (currentNode->getLeftPtr() == nullptr) {
                currentNode->setLeftPtr(newNode);
                newNode->setParentPtr(currentNode);
                break;
            }
            currentNode = currentNode->getLeftPtr();
        }
    }
}

    vector<Trip*> showTrips(const std::string& pickupLocation, int afterTime, int beforeTime) {
    Location* pickupLocationPtr = nullptr;

    // Find the pickup location
    for (Location* loc : locations) {
        if (loc->getName() == pickupLocation) {
            pickupLocationPtr = loc;
            break;
        }
    }

    std::vector<Trip*> resultTrips;

    if (pickupLocationPtr == nullptr) {
        return resultTrips;
    }

    std::vector<Trip*> allTrips = pickupLocationPtr->getTrips();

    for (Trip* trip : allTrips) {
        int departureTime = trip->getDepartureTime();

        if (departureTime > afterTime && departureTime < beforeTime) {
            resultTrips.push_back(trip);
        }
    }

    return resultTrips;
}


    vector<Trip*> showTripsbydestination(const std::string& pickupLocation, const std::string& destination, int afterTime, int beforeTime) {
    Location* pickupLocationPtr = nullptr;

    // Find the pickup location
    for (Location* loc : locations) {
        if (loc->getName() == pickupLocation) {
            pickupLocationPtr = loc;
            break;
        }
    }

    std::vector<Trip*> resultTrips;

    if (pickupLocationPtr == nullptr) {
        return resultTrips;
    }

    std::vector<Trip*> allTrips = pickupLocationPtr->getTrips();

    for (Trip* trip : allTrips) {
        if (trip->getDropLocation() == destination) {
            int departureTime = trip->getDepartureTime();

            if (departureTime > afterTime && departureTime < beforeTime) {
                resultTrips.push_back(trip);
            }
        }
    }

    return resultTrips;
}


    Trip* bookTrip(const std::string& pickupLocation, const std::string& dropLocation, const std::string& vehicleNumber, int departureTime) {
    Location* pickupLocationPtr = getLocation(pickupLocation);
    
    if (pickupLocationPtr == nullptr) {
        return nullptr;
    }

    std::vector<Trip*> trips = pickupLocationPtr->getTrips();
    for (Trip* trip : trips) {
        if (trip->getDropLocation() == dropLocation && trip->getVehicle()->getVehicleNumber() == vehicleNumber &&
            trip->getDepartureTime() == departureTime && trip->getBookedSeats() < trip->getVehicle()->getSeatingCapacity()) {
            trip->setBookedSeats(trip->getBookedSeats() + 1);
            return trip;
        }
    }

    return nullptr;
}

Location* getLocation(const std::string& location) {
    for (Location* loc : locations) {
        if (loc->getName() == location) {
            return loc;
        }
    }
    return nullptr;
}
private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};

