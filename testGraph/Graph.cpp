#include "Graph.hpp"

double Graph::calculateDistance(const Waypoint& wp1, const Waypoint& wp2) {
    double lat1 = wp1.getLatitude() * M_PI / 180.0;
    double lon1 = wp1.getLongitude() * M_PI / 180.0;
    double lat2 = wp2.getLatitude() * M_PI / 180.0;
    double lon2 = wp2.getLongitude() * M_PI / 180.0;

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    const int earthRadius = 6378;
    return earthRadius * c;
}

void Graph::createAdjacencyList() {
    double maxDistance = this->precision;

    for (size_t i = 0; i < waypoints.size(); ++i) {
        for (size_t j = i + 1; j < waypoints.size(); ++j) {
            double dist = calculateDistance(waypoints[i], waypoints[j]);

            if (dist <= maxDistance) {
                adjacencyList[waypoints[i].getNom()].push_back({waypoints[j].getNom(), dist});
                adjacencyList[waypoints[j].getNom()].push_back({waypoints[i].getNom(), dist});
            }
        }
    }

    // Debug: Print adjacency list
    for (const auto& pair : adjacencyList) {
        std::cout << "Node: " << pair.first << std::endl;
        for (const auto& neighbor : pair.second) {
            std::cout << "  Neighbor: " << neighbor.first << ", Distance: " << neighbor.second << std::endl;
        }
    }
}

int Graph::findWaypointIndex(const Waypoint& wp) {
    for (size_t i = 0; i < waypoints.size(); ++i) {
        if (waypoints[i].getNom() == wp.getNom()) {
            return i;
        }
    }
    return -1; // Not found
}

std::vector<int> Graph::getShortestPath(const Waypoint& start, const Waypoint& end) {
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> pq;

    for (const auto& wp : waypoints) {
        distances[wp.getNom()] = std::numeric_limits<double>::infinity();
    }
    distances[start.getNom()] = 0;
    pq.push({0, start.getNom()});

    while (!pq.empty()) {
        std::string current = pq.top().second;
        double currentDist = pq.top().first;
        pq.pop();

        if (currentDist > distances[current]) {
            continue;
        }

        for (const auto& neighbor : adjacencyList[current]) {
            double newDist = distances[current] + neighbor.second;
            if (newDist < distances[neighbor.first]) {
                distances[neighbor.first] = newDist;
                previous[neighbor.first] = current;
                pq.push({newDist, neighbor.first});
            }
        }
    }

    std::vector<int> pathIndices;
    std::string current = end.getNom();

    // Debug: Print the reconstructed path
    std::cout << "Reconstructed Path: ";
    while (previous.find(current) != previous.end()) {
        pathIndices.push_back(findWaypointIndex(Waypoint(current)));
        std::cout << current << " ";
        current = previous[current];
    }
    std::cout << std::endl;

    pathIndices.push_back(findWaypointIndex(Waypoint(start.getNom())));
    std::reverse(pathIndices.begin(), pathIndices.end());
    return pathIndices;
}

void Graph::visualizePath(const std::vector<int>& path) {
    std::cout << "Shortest Path:\n";
    for (size_t i = 0; i < path.size(); ++i) {
        int index = path[i];
        if (index >= 0 && static_cast<size_t>(index) < waypoints.size()) {
            std::cout << waypoints[index].getNom();
            if (i < path.size() - 1) {
                std::cout << " => ";
            }
        } else {
            std::cout << "Invalid index in path." << std::endl;
        }
    }
    std::cout << std::endl;
}

void Graph::adjacencyListToEdgeListFile(const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjacencyList, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& pair : adjacencyList) {
        std::string source = pair.first;
        for (const auto& neighbor : pair.second) {
            std::string destination = neighbor.first;
            outputFile << source << ", " << destination << std::endl;
        }
    }

    outputFile.close();
    std::cout << "Edge list written to " << filename << std::endl;
}
