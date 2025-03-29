#include "Graph.hpp"

// return the distance between two waypoints
double Graph::getDistance(Waypoint A, Waypoint B) {
    std::pair<double, double> ACoords = this->latLonToMercator(A.getLatitude(), A.getLongitude());
    std::pair<double, double> BCoords = this->latLonToMercator(B.getLatitude(), B.getLongitude());

    return std::sqrt(std::pow(ACoords.first - BCoords.first, 2) + std::pow(ACoords.second - BCoords.second, 2));
}

// Function to convert lat/lon to Mercator (x, y)
std::pair<double, double> Graph::latLonToMercator(float lat, float lon) {
    const double R = 6378137.0; // Earth's radius in meters

    double x = R * lon * M_PI / 180.0;
    double y = R * log(tan(M_PI / 4.0 + (lat * M_PI / 180.0) / 2.0));
    return {x, y};
}

std::unordered_map<std::string, std::string> Graph::mapClosestWaypoints() {
    std::unordered_map<std::string, std::string> closestMap;

    for (const auto& A : this->waypoints) {
        double minDist = std::numeric_limits<double>::infinity();
        std::string nearestNeighbor;

        for (const auto& B : this->waypoints) {
            if (A.getNom() != B.getNom()) {
                double currDist = getDistance(A, B);
                if (currDist < minDist) {
                    minDist = currDist;
                    nearestNeighbor = B.getNom();
                }
            }
        }
        closestMap[A.getNom()] = nearestNeighbor;
    }
    return closestMap;
}

/*std::unordered_map<std::string, std::vector<std::string>> Graph::createAdjacencyList() {
    std::unordered_map<std::string, std::vector<std::string>> adjacencyList;
    std::unordered_map<std::string, std::string> closestMap = this->mapClosestWaypoints();

    for (const auto& pair : closestMap) {
        const std::string& waypoint = pair.first;
        const std::string& closest = pair.second;

        if (waypoint != closest) { // Prevent self-loop
            adjacencyList[waypoint].push_back(closest);
            adjacencyList[closest].push_back(waypoint);
        }
    }
    return adjacencyList;
}*/

// Dijkstra's algorithm to find the shortest path
std::pair<std::vector<std::string>, double> Graph::getShortestPath(const std::string& start, const std::string& end) {
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> graph = this->createWeightedAdjacencyList();
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous_nodes;
    std::priority_queue<pnode, std::vector<pnode>, std::greater<pnode>> pq;

    if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
        return {{}, std::numeric_limits<double>::infinity()}; // Start or end node not found
    }

    for (const auto& node : graph) {
        distances[node.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        double curr_dist = pq.top().first;
        std::string curr_node = pq.top().second;
        pq.pop();

        if (curr_node == end) {
            break;
        }

        for (const auto& [neighbor, edge_weight] : graph[curr_node]) {
            double new_dist = curr_dist + edge_weight;
            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                previous_nodes[neighbor] = curr_node;
                pq.push({new_dist, neighbor});
            }
        }
    }

    if (distances[end] == std::numeric_limits<double>::infinity()) {
        return {{}, std::numeric_limits<double>::infinity()}; // No path found
    }

    std::vector<std::string> path;
    std::string node = end;
    while (node != start) {
        path.push_back(node);
        node = previous_nodes[node];
    }
    path.push_back(start); // Add the start node
    std::reverse(path.begin(), path.end());

    return {path, distances[end]};
}


bool Graph::alreadyExists(const std::vector<std::pair<std::string, double>>& list, const std::string& target) {
    return std::any_of(list.begin(), list.end(), [&](const auto& pair) {
        return pair.first == target;
    });
}

std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> Graph::createWeightedAdjacencyList() {
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjacencyList;
    std::unordered_map<std::string, std::string> closestMap = this->mapClosestWaypoints();

    for (const auto& [waypoint, closest] : closestMap) {
        // Get distance between two waypoints, firstly, by search a waypoint by name
        double distance = getDistance(
            *std::find_if(waypoints.begin(), waypoints.end(), [&](const Waypoint& wp) { return wp.getNom() == waypoint; }),
            *std::find_if(waypoints.begin(), waypoints.end(), [&](const Waypoint& wp) { return wp.getNom() == closest; })
        );

        if (!alreadyExists(adjacencyList[waypoint], closest)) {
            adjacencyList[waypoint].emplace_back(closest, distance);
        }
        if (!alreadyExists(adjacencyList[closest], waypoint)) {
            adjacencyList[closest].emplace_back(waypoint, distance);
        }
    }

    // Affichage
    /*for (auto& [node, vect] : adjacencyList) {
        std::cout << node << " : [";
        for (auto& [neighbour, weight] : vect) {
            std::cout << "(" << neighbour << ", " << weight << "); ";
        }
        std::cout << "]\n\n";
    }*/
    return adjacencyList;
}
