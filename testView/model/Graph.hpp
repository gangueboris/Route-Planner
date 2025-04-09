/**
 * @class Graph
 * @brief Represents a graph of waypoints and provides pathfinding functionality.
 *
 * This class manages a set of waypoints, constructs an adjacency list,
 * and implements Dijkstra's algorithm to find the shortest path between waypoints.
 * It also includes a visualization method to display the computed paths.
 *
 * @author Boris Gangue
 * @date March 30, 2025
 */
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
      Graph(std::vector<Waypoint> waypoints_init, std::vector<Route> routes_init) : waypoints{waypoints_init}, routes{routes_init}{
         createAdjacencyList();
      }
      Graph(){}
      ~Graph(){}

      std::vector<int> getShortestPath(const Waypoint& start, const Waypoint& end);
      void visualizePath(const std::vector<int>& path);
      double getDistance();
      void adjacencyListToEdgeListFile(const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjacencyList, const std::string& filename);
      std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> getAdjacencyList() {return this->adjacencyList;}
      int findWaypointIndex(const Waypoint& wp);
      
   private:
      std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjacencyList;
      std::vector<Waypoint> waypoints;
      std::vector<Route> routes;
      std::vector<int> pathIndices;
      
      void createAdjacencyList();
     
};

#endif
