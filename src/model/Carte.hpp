#ifndef _CARTE_H_
#define _CARTE_H_

#include <iostream>
#include <vector>
#include <string>

#include "Waypoint.hpp"
#include "Route.hpp"
#include "Contour.hpp"

class Carte {
    public:
       // Constructor
       Carte();
       
       // Destructor
       ~Carte(){};
       
       // Getters
       Contour getContour() const {return this->contour;}

       //float getEchelleLong() const {}

       std::vector<Waypoint> getWaypoints() const {return this->waypoints;}

       std::vector<Route> getRoutes() const {return this->routes;}

       std::vector<std::string> getNomsVilles() const {         // A city's name is in a waypoint.
           std::vector<std::string> cityNames;

           for(auto& waypoint : this->waypoints) {
              cityNames.push_back(waypoint.getNom());
           }
           return cityNames;
       }

       void ajouterUnWaypoint(Waypoint* waypoint) {this->waypoints.pop_back(waypoint);}

       void insereUneVille(Ville* ville) {this->waypoints.pop_back(ville);}

       
    private:
       Contour contour;
       std::vector<Waypoint*> waypoints;
       std::vector<Route> routes;
};

#endif