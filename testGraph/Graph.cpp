#include "Graph.hpp"

/**
 * @brief Calculates the great-circle distance between two geographical points using the Haversine formula.
 * 
 * @param wp1 The first waypoint containing latitude and longitude.
 * @param wp2 The second waypoint containing latitude and longitude.
 * @return The distance between the two points in kilometers.
 */
double Graph::calculateDistance(const Waypoint& wp1, const Waypoint& wp2) {
    // Convert latitude and longitude from degrees to radians
    double lat1 = wp1.getLatitude() * M_PI / 180.0;
    double lon1 = wp1.getLongitude() * M_PI / 180.0;
    double lat2 = wp2.getLatitude() * M_PI / 180.0;
    double lon2 = wp2.getLongitude() * M_PI / 180.0;

    // Compute differences between the coordinates
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    // Apply the Haversine formula
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    // Define Earth's radius in kilometers
    const int earthRadius = 6378;
    
    // Compute and return the distance
    return earthRadius * c;
}


/**
 * @brief Creates an adjacency list representing a sparse graph.
 * 
 * This function connects waypoints if the distance between them is within a given threshold.
 * 
 * @return void
 */
void Graph::createAdjacencyList() {
    double maxDistance = this->precision;

    for (int i = 0; i < (int)waypoints.size(); ++i) {
        for (int j = i + 1; j < (int)waypoints.size(); ++j) {
            // Compute the distance between two waypoint in km
            double dist = calculateDistance(waypoints[i], waypoints[j]);
            if (dist <= maxDistance) {
                // Add bidirectional edges for an undirected graph
                adjacencyList[waypoints[i].getNom()].push_back({waypoints[j].getNom(), dist});
                adjacencyList[waypoints[j].getNom()].push_back({waypoints[i].getNom(), dist});
            }
        }
    }
}


/**
 * @brief Finds the index of a waypoint in the waypoints list.
 * 
 * @param wp The waypoint to search for.
 * @return The index of the waypoint if found, otherwise -1.
 */
int Graph::findWaypointIndex(const Waypoint& wp) {
    for (int i = 0; i < (int)waypoints.size(); ++i) {
        if (waypoints[i].getNom() == wp.getNom()) {
            return i;
        }
    }
    return -1; // Not found
}


/**
 * @brief Implements Dijkstra's algorithm to find the shortest path between two waypoints.
 * 
 * @param start The starting waypoint.
 * @param end The destination waypoint.
 * @return A vector of indices representing the shortest path.
 */
std::vector<int> Graph::findShortestPath(const Waypoint& start, const Waypoint& end) {
    std::unordered_map<std::string, double> distances; // Stores shortest known distance to each waypoint
    std::unordered_map<std::string, std::string> previous; // Stores previous waypoint in shortest path
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> pq;

    // Initialize all distances to infinity
    for (const auto& wp : waypoints) {
        distances[wp.getNom()] = std::numeric_limits<double>::infinity();
    }
    distances[start.getNom()] = 0;
    pq.push({0, start.getNom()}); // Start processing from the initial waypoint

    while (!pq.empty()) {
        std::string current = pq.top().second; // Get waypoint with the shortest known distance
        double currentDist = pq.top().first;
        pq.pop();

        // Ignore outdated distance calculations
        if (currentDist > distances[current]) {
            continue;
        }

        // Explore neighbors of the current waypoint
        for (const auto& neighbor : adjacencyList[current]) {
            double newDist = distances[current] + neighbor.second; // Calculate potential shorter path
            if (newDist < distances[neighbor.first]) {
                distances[neighbor.first] = newDist; // Update shortest distance
                previous[neighbor.first] = current; // Store path information
                pq.push({newDist, neighbor.first}); // Push updated distance to the queue
            }
        }
    }

    std::vector<int> pathIndices;
    std::string current = end.getNom();
    
    // Reconstruct the shortest path by backtracking from the destination
    while (previous.find(current) != previous.end()) {
        pathIndices.push_back(findWaypointIndex(Waypoint(current)));
        current = previous[current];
    }
    
    // Add the start waypoint to the path
    pathIndices.push_back(findWaypointIndex(Waypoint(start.getNom())));
    std::reverse(pathIndices.begin(), pathIndices.end()); // Reverse to get correct order
    return pathIndices;
}

/**
 * @brief Visualizes the shortest path by printing it to the console.
 * 
 * @param path A vector of waypoint indices representing the path.
 * @return void
 */
void Graph::visualizePath(const std::vector<int>& path) {
    std::cout << "Shortest Path:\n";
    for (int i = 0; i < (int)path.size(); ++i) {
        int index = path[i];
        if (index >= 0 && index < (int)waypoints.size()) {
            std::cout << waypoints[index].getNom();
            if (i < (int)path.size() - 1) {
                std::cout << " => ";
            }
        } else {
            std::cout << "Invalid index in path." << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Converts the adjacency list representation of a graph into an edge list and writes it to a file.
 * 
 * This method takes an adjacency list, where each node is mapped to a list of its neighbors, 
 * and writes each edge (source, destination) into a specified file.
 * 
 * @param adjacencyList An unordered_map where the key is a node (represented as a string) and the value is a vector
 *                      of pairs, each containing a neighboring node (string) and the edge weight (double).
 * @param filename The name of the file where the edge list will be written.
 * @return void
 */
void Graph::adjacencyListToEdgeListFile(const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjacencyList, const std::string& filename) {
    // Open the output file for writing the edge list
    std::ofstream outputFile(filename);

    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Iterate through each node in the adjacency list
    for (const auto& pair : adjacencyList) {
        std::string source = pair.first; // Get the source node
        // Iterate through the neighbors of the source node
        for (const auto& neighbor : pair.second) {
            std::string destination = neighbor.first; // Get the destination node
            // Write the edge (source, destination) to the file
            outputFile << source << ", " << destination << std::endl;
        }
    }

    // Close the output file after writing the edges
    outputFile.close();
    
    // Print a confirmation message indicating the edge list has been written
    std::cout << "Edge list written to " << filename << std::endl;
}
