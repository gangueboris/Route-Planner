#ifndef _CARTE_H_
#define _CARTE_H_

#include "Waypoint.hpp"
#include "Route.hpp"
#include "Contour.hpp"

#include <vector>

class Carte {
    public:
       // Constructor
       Carte();
       
       // Destructor
       ~Carte(){};
       
       // Getters
       Contour getContour() const;

};

#endif