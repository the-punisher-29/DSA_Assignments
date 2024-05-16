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

    void add_trip(int key, Trip* trip);

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
        return 0;
    } else {
        int leftHeight = getHeight(node->getLeftPtr());
        int rightHeight = getHeight(node->getRightPtr());
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    }

int getNumberOfNodes(BinaryTreeNode* node) const {
    if (node == nullptr) {
        return 0; 
    } else {
        int leftNodes = getNumberOfNodes(node->getLeftPtr());
        int rightNodes = getNumberOfNodes(node->getRightPtr());
        return leftNodes + rightNodes + 1;
    }
}
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
    BinaryTreeNode* currentNode = root;
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
            result = currentNode;
            currentNode = currentNode->getLeftPtr();
        } else if (key > currentNode->getDepartureTime()) {
            currentNode = currentNode->getRightPtr();
        } else {
            return currentNode;
        }
    }

    return result;
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
    void add_trip(string vehicle_number, int seating_capacity, string pick_up_location, string drop_location, int departure_time) {
        Vehicle * veh=NULL;
        for(int i=0;i<vehicles.size();++i){
            if(vehicles[i]->getVehicleNumber()==vehicle_number){
                veh=vehicles[i];
                break;
            }
        }
        if(veh==NULL){
            veh=new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(veh);
        }

        Trip * newtrip=new Trip(veh,pick_up_location,drop_location,departure_time);
        Location * demo=NULL;
        
        for(int i=0;i<locations.size();++i){
            if(locations[i]->getName()==pick_up_location){
                demo=locations[i];
                demo->add_trip(newtrip);
                break;
            }
        }
        if(demo==NULL){
            demo=new Location(pick_up_location);
            demo->add_trip(newtrip);
            locations.push_back(demo);
        }
        TransportService * juju=demo->getServicePtr(drop_location);
        if(juju==NULL){
            juju=demo->setServicePtr(drop_location);
            BinaryTreeNode * node=new BinaryTreeNode(departure_time);
            juju->setBSTHead(node);
            return ;
        }
        else{
            BinaryTreeNode * newnode=new BinaryTreeNode(departure_time);
            BinaryTreeNode * node=juju->getBSTHead();
            while(node->getRightPtr()!=NULL && node->getRightPtr()->getDepartureTime()<departure_time){
                node=node->getRightPtr();
            }
            BinaryTreeNode * storage=node->getRightPtr();
            
            newnode->setParentPtr(node);
            node->setRightPtr(newnode);
            newnode->setRightPtr(storage);
            if(storage!=NULL){
                storage->setParentPtr(newnode);
            }
        }
        return ;
    }

    vector<Trip*> show_trips(string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        Location * loc=NULL;
        for(int i=0;i<locations.size();++i){
            if(locations[i]->getName()==pick_up_location){
                loc=locations[i];
                break;
            }
        }
        vector<Trip*> result;
        if(loc==NULL){
            return result;
        }
        vector <Trip *> trips=loc->getTrips();
        for(int i=0;i<trips.size();i++){
            if(trips[i]->getDepartureTime()>after_time && trips[i]->getDepartureTime()<before_time){
                result.push_back(trips[i]);
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

    Trip* book_trip(string pick_up_location, string drop_location, string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        Location * loc=NULL;
        for(int i=0;i<locations.size();++i){
            if(locations[i]->getName()==pick_up_location){
                loc=locations[i];
                break;
            }
        }
        if(loc==NULL){
            return NULL;
        }
        vector <Trip *> trips=loc->getTrips();
        for(int i=0;i<trips.size();i++){
            if(trips[i]->getDropLocation()==drop_location && trips[i]->getVehicle()->getVehicleNumber()==vehicle_number && trips[i]->getDepartureTime()==departure_time && trips[i]->getBookedSeats()<trips[i]->getVehicle()->getSeatingCapacity()){
                trips[i]->setBookedSeats(trips[i]->getBookedSeats()+1);
                return trips[i];
            }
        }
        return NULL; // Placeholder
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

