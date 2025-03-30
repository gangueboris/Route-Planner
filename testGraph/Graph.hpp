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
      Graph(std::vector<Waypoint> waypoints_init, double precision_init = 70) : waypoints{waypoints_init}, precision{precision_init}{
         createAdjacencyList();
      }
      ~Graph(){}

      std::vector<int> findShortestPath(const Waypoint& start, const Waypoint& end);
      void visualizePath(const std::vector<int>& path);
      int getPrecision() {return precision;}
      void setPrecision(double new_precision) {precision = new_precision;}
      void adjacencyListToEdgeListFile(const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjacencyList, const std::string& filename);
      std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> getAdjacencyList() {return this->adjacencyList;}
      
   private:
      std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjacencyList;
      std::vector<Waypoint> waypoints;
      double precision;
      
      void createAdjacencyList();
      double calculateDistance(const Waypoint& wp1, const Waypoint& wp2);
      int findWaypointIndex(const Waypoint& wp);
};

#endif
