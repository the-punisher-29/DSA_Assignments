#include<bits/stdc++.h>

using namespace std;

class Parcel {
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority) {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap {
public:
    std::vector<Parcel*> heap;

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return 2 * i + 1;
    }

    int right(int i) {
        return 2 * i + 2;
    }

    Parcel* get_max() {
        if (!is_empty()) {
            return heap[0];
        }
        return nullptr; // Or handle as needed
    }

    Parcel* extract_max() {
        if (is_empty()) {
            return nullptr; // Or handle as needed
        }

        Parcel* max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        max_heapify(0);

        return max;
    }

    void max_heapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap.size() && heap[l]->priority > heap[largest]->priority) {
            largest = l;
        }

        if (r < heap.size() && heap[r]->priority > heap[largest]->priority) {
            largest = r;
        }

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            max_heapify(largest);
        }
    }

    void insert(Parcel* item) {
        heap.push_back(item);
        int i = heap.size() - 1;

        while (i > 0 && heap[parent(i)]->priority < heap[i]->priority) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    int max_parcel_capacity;
    std::vector<Parcel*> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;
    

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel* parcel) {
        parcels.push_back(parcel);
        return ;
            //std::cout << "Parcel " << parcel->parcel_id << " loaded into the freight car." << std::endl;
        
    }

    bool can_move() {
        return sealed && parcels.size() == max_parcel_capacity;
    }

    void move(std::string destination) {
    current_location = destination;

    for (auto& parcel : parcels) {
        parcel->current_location = destination;
        parcel->time_tick += 1;

        if (parcel->current_location == parcel->destination) {
            parcel->delivered = true;
        }
    }
}

};

class Vertex {
public:
    std::string name;
    std::vector<FreightCar*> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar*>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
    std::vector<FreightCar*> sealed_freight_cars;
    std::vector<Parcel*> all_parcels;

    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity) {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    void add_neighbor(Vertex* neighbor) {
        neighbors.push_back(neighbor);
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        return this->neighbors;
    }

    std::vector<Parcel*> get_all_current_parcels() {
    std::vector<Parcel*> all_parcels;

    for (const auto& [destination, heap] : parcel_destination_heaps) {
        for (Parcel* parcel : heap.heap) {
            all_parcels.push_back(parcel);
        }
    }

    return all_parcels;
}


    void clean_unmoved_freight_cars() {
    freight_cars.erase(
        std::remove_if(freight_cars.begin(), freight_cars.end(),
            [this](FreightCar* freight_car) {
                if (!freight_car->can_move()) {
                    // Move parcels from the unmoved freight car back to the destination heap
                    for (Parcel* parcel : freight_car->parcels) {
                        parcel_destination_heaps[parcel->destination].insert(parcel);
                    }

                    // Delete the freight car object
                    delete freight_car;

                    return true; // Indicates that the freight car should be removed
                }
                return false; // Indicates that the freight car should be kept
            }
        ),
        freight_cars.end()
    );
}


    void load_parcel(Parcel* parcel) {
    // Add the parcel to the destination heap
    parcel_destination_heaps[parcel->destination].insert(parcel);
    all_parcels.push_back(parcel);

    // Ensure that the destination heap is sorted based on priority
    auto& destination_heap = parcel_destination_heaps[parcel->destination];
    
    // Assuming MaxHeap::get_max() returns the parcel with the highest priority
    Parcel* max_priority_parcel = destination_heap.get_max();

    // If there is a parcel with higher priority, move it to the front of the heap
    if (max_priority_parcel && max_priority_parcel->priority > parcel->priority) {
        destination_heap.extract_max(); // Remove the max priority parcel
        destination_heap.insert(max_priority_parcel); // Re-insert at the correct position
    }
}


    void loadFreightCars() {
    // Iterate through destination heaps and create freight cars
    for (auto& [destination, heap] : parcel_destination_heaps) {
        while (!heap.is_empty()) {
            // Create a new freight car
            FreightCar* freight_car = new FreightCar(max_parcel_capacity);
            freight_car->destination_city = destination;

            // Load parcels into the freight car until it reaches min_parcel_capacity
            for (int i = 0; i < min_freight_cars_to_move && !heap.is_empty(); ++i) {
                Parcel* parcel = heap.extract_max();
                freight_car->load_parcel(parcel);
            }

            // Add the freight car to the list of freight cars at this vertex
            freight_cars.push_back(freight_car);
        }
    }
}


    void print_parcels_in_freight_cars() {
        for (auto& [destination, heap] : this->parcel_destination_heaps) {
            for (auto& parcel : heap.heap) {
                std::cout << "Parcel ID: " << parcel->parcel_id << ", Parcel origin: " << parcel->origin << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
            }
        }
    }
};

struct BFSInfo {
    Vertex* vertex;
    std::vector<std::string> path;
};


vector <Vertex *> stations;

class Graph {
public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    void extractStations() {
    for (const auto& vertex : vertices) {
        stations.push_back(vertex);
    }
    }

    Vertex* getVertex(const std::string& s) {
    for (Vertex* station : stations) {
        if (station->name == s) {
            return station;
        }
    }
    return nullptr;  // Use nullptr instead of NULL for C++11 and later
}


    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {
        Vertex* source_vertex = find_or_create_vertex(source, min_freight_cars_to_move, max_parcel_capacity);
        Vertex* destination_vertex = find_or_create_vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
        source_vertex->add_neighbor(destination_vertex);
        destination_vertex->add_neighbor(source_vertex);
        edges.push_back({source_vertex, destination_vertex});
    }

    Vertex* find_or_create_vertex(const std::string& vertex_name, int min_freight_cars_to_move, int max_parcel_capacity) {
    auto it = std::find_if(vertices.begin(), vertices.end(),
                           [&vertex_name](const Vertex* vertex) { return vertex->name == vertex_name; });

    if (it != vertices.end()) {
        return *it; // Vertex found
    }

    // Create a new vertex if not found
    Vertex* new_vertex = new Vertex(vertex_name, min_freight_cars_to_move, max_parcel_capacity);
    new_vertex->min_freight_cars_to_move = min_freight_cars_to_move;
    new_vertex->max_parcel_capacity = max_parcel_capacity;

    vertices.push_back(new_vertex);
    return new_vertex;
}


    void print_graph() {
    std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;

    for (const auto& vertex : vertices) {
        std::cout << "Vertex: " << vertex->name << std::endl;

        std::cout << "Neighbors: ";
        for (const auto& neighbor : vertex->neighbors) {
            std::cout << neighbor->name << " ";
        }
        std::cout << std::endl;
    }
}


        Vertex* find_vertex(const std::string& vertex_name) {
    auto it = std::find_if(vertices.begin(), vertices.end(),
                           [&](const Vertex* vertex) { return vertex->name == vertex_name; });

    return (it != vertices.end()) ? *it : nullptr;
}


    std::vector<std::string> bfs(const std::string& source, const std::string& destination) {
    std::unordered_map<Vertex*, bool> visited;
    std::queue<std::vector<std::string>> bfs_queue;

    Vertex* source_vertex = find_vertex(source);
    Vertex* dest_vertex = find_vertex(destination);

    if (!source_vertex || !dest_vertex) {
        std::cerr << "Source or destination vertex not found." << std::endl;
        return {};
    }

    bfs_queue.push({source});
    visited[source_vertex] = true;

    while (!bfs_queue.empty()) {
        std::vector<std::string> current_path = bfs_queue.front();
        bfs_queue.pop();

        std::string current_vertex_name = current_path.back();
        Vertex* current_vertex = find_vertex(current_vertex_name);

        if (current_vertex == dest_vertex) {
            return current_path;  // Path found
        }

        for (auto& neighbor : current_vertex->neighbors) {
            if (!visited[neighbor]) {
                std::vector<std::string> new_path = current_path;
                new_path.push_back(neighbor->name);
                bfs_queue.push(new_path);
                visited[neighbor] = true;
            }
        }
    }

    // If no path is found
    return {};
}


    std::vector<std::string> dfs(std::string source, std::string destination) {
    std::vector<std::string> path;
    std::stack<std::pair<Vertex*, std::vector<std::string>>> stack;
    std::unordered_set<std::string> visited;

    Vertex* source_vertex = find_vertex(source);
    Vertex* destination_vertex = find_vertex(destination);

    if (!source_vertex || !destination_vertex) {
        std::cerr << "Source or destination vertex not found." << std::endl;
        return {};
    }

    stack.push({source_vertex, {source_vertex->name}});
    visited.insert(source_vertex->name);

    while (!stack.empty()) {
        auto [currentVertex, currentPath] = stack.top();
        stack.pop();

        if (currentVertex == destination_vertex) {
            return currentPath;  // Return the first path found
        }

        // Iterate through neighbors in reverse to maintain the original order
        for (auto it = currentVertex->neighbors.rbegin(); it != currentVertex->neighbors.rend(); ++it) {
            Vertex* neighbor = *it;
            if (visited.find(neighbor->name) == visited.end()) {
                visited.insert(neighbor->name);

                std::vector<std::string> newPath = currentPath;
                newPath.push_back(neighbor->name);

                stack.push({neighbor, newPath});
            }
        }
    }

    return {};  // If no path is found
}

void groupFreightCars() {
    // Iterate over all vertices in the graph
    for (auto& vertex : vertices) {
        // Clear the existing groups
        vertex->trains_to_move.clear();

        // Group freight cars based on their destination links
        std::map<std::string, std::vector<FreightCar*>> groupedCars;

        for (auto& freight_car : vertex->freight_cars) {
            std::string destination = freight_car->next_link;

            // Create a new entry in the map if it doesn't exist
            groupedCars[destination].push_back(freight_car);

            // If the group size reaches the required minimum, move the train
            if (groupedCars[destination].size() >= vertex->min_freight_cars_to_move) {
                // Move the freight cars to the next link
                for (auto& car : groupedCars[destination]) {
                    car->move(destination);
                }

                // Clear the group after moving
                groupedCars[destination].clear();
            }
        }

        // Update the trains_to_move for the current vertex
        vertex->trains_to_move = groupedCars;
    }
}



void moveTrains() {
    // Iterate over all vertices in the graph
    for (auto& vertex : vertices) {
        // Iterate through each destination (link) in the vertex
        for (auto it = vertex->trains_to_move.begin(); it != vertex->trains_to_move.end();) {
            const std::string& destination = it->first;
            std::vector<FreightCar*>& freight_cars = it->second;

            // Check if there are enough freight cars to form a train
            if (freight_cars.size() >= vertex->min_freight_cars_to_move) {
                // Move the freight cars to the next link
                for (auto& freight_car : freight_cars) {
                    freight_car->move(destination);
                }

                // Erase the destination entry from the map if all cars moved
                it = vertex->trains_to_move.erase(it);
            } else {
                // Move to the next destination in the map
                ++it;
            }
        }
    }
}
};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar*> freight_cars;
    std::map<std::string, Parcel*> parcels;
    std::map<int, std::vector<Parcel*>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move) {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};

    }

    void create_graph(std::string graph_file_name) {
    std::ifstream inputFile(graph_file_name);
    std::string line;

    while (getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> words{std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{}};

        // Ensure the line has at least two words before adding an edge
        if (words.size() >= 2) {
            // Assuming you have a method to add an edge to the graph
            graph.add_edge(words[0], words[1], min_freight_cars_to_move, max_parcel_capacity);
        }
    }

    graph.extractStations();

    inputFile.close();
}


    void process_parcels(std::string parcels_file_name) {
    std::ifstream parcels_file(parcels_file_name);

    if (!parcels_file.is_open()) {
        std::cerr << "Unable to open parcels file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(parcels_file, line)) {
        std::istringstream iss(line);
        int time_tick;
        std::string parcel_id, origin, destination;
        int priority;

        if (!(iss >> time_tick >> parcel_id >> origin >> destination >> priority)) {
            std::cerr << "Error reading parcel information from line: " << line << std::endl;
            continue;
        }

        Parcel *parcel = new Parcel(time_tick, parcel_id, origin, destination, priority);
        parcels[parcel_id] = parcel;
        parcels_with_time_tick[time_tick].push_back(parcel);
        graph.vertices.front()->load_parcel(parcel);
    }

    parcels_file.close();
}


    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel*> get_bookings(int time_tick, std::string vertex) {
    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {

        // function to run simulation
    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
    }

    bool all_parcels_delivered() {
        // function to check if all parcels are delivered
        // return true if all parcels are delivered else return false
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
    }

    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
    
    }

    std::string get_status_of_parcel(std::string parcel_id, int t) {
    for (const auto& [id, parcel] : parcels) {
        if (parcel->time_tick == t && id == parcel_id) {
            return id + " " + parcel->current_location + " " + std::to_string(parcel->delivered);
        }
    }

    return "";  // Return an empty string if parcel not found
}

    // get parcels delivered up to time tick t
    // std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
    //     return parecls_till_time_tick[t];
    // }

};


// int main() {

//     PRC prc = PRC(2, 2);
//     prc.create_graph();
//     prc.process_parcels();
//     prc.run_simulation(3);

//     return 0;
// }


