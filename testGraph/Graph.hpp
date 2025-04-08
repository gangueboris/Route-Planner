#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>

#include "Route.hpp"
#include "Waypoint.hpp"

class Graph {
public:
    Graph(std::vector<Waypoint> waypoints_init, double precision_init = 50)
        : waypoints{waypoints_init}, precision{precision_init} {
        createAdjacencyList();
    }
    ~Graph() {}

    std::vector<int> getShortestPath(const Waypoint& start, const Waypoint& end);
    void visualizePath(const std::vector<int>& path);
    int getPrecision() { return precision; }
    double getDistance(const Waypoint& wp1, const Waypoint& wp2) { return this->calculateDistance(wp1, wp2); }
    void setPrecision(double new_precision) { precision = new_precision; }
    void adjacencyListToEdgeListFile(const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjacencyList, const std::string& filename);
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> getAdjacencyList() { return this->adjacencyList; }

private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjacencyList;
    std::vector<Waypoint> waypoints;
    double precision;

    void createAdjacencyList();
    double calculateDistance(const Waypoint& wp1, const Waypoint& wp2);
    int findWaypointIndex(const Waypoint& wp);
};

#endif
