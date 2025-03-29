#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>

#include "Route.hpp"
#include "Waypoint.hpp"

typedef std::pair<double, std::string> pnode;  // Pair of distance and node

class Graph {
public:
   // Constructor
   Graph(std::vector<Waypoint> waypoints_init) : waypoints{waypoints_init} {}

   // Destructor
   ~Graph() {}

   double getDistance(Waypoint A, Waypoint B);
   std::pair<std::vector<std::string>, double> getShortestPath(const std::string& start, const std::string& end);


private:
   // Helper method to convert (lat, lon) => (x, y)
   std::pair<double, double> latLonToMercator(float lat, float lon);

   // It maps a waypoint to it closest one. Mapping by string (name) instead of by Waypoint to have an easy data manipulation.
   std::unordered_map<std::string, std::string> mapClosestWaypoints();

   // Create a mapping list
   //std::unordered_map<std::string, std::vector<std::string>> createAdjacencyList();

   std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> createWeightedAdjacencyList();
   bool alreadyExists(const std::vector<std::pair<std::string, double>>& list, const std::string& target);

   std::vector<Waypoint> waypoints;

};
#endif

 