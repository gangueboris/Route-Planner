#ifndef _ROUTE_H_
#define _ROUTE_H_

#include <iostream>
#include <string>
#include <sstream>

class Route {
    public:
       // Constructor
       Route(int i_debut = 0, int i_fin = 0, int distance = 0) : i_debut(i_debut), i_fin(i_fin), distance(distance) {}
       Route(){}
       // Destructor
       ~Route(){};
       
       // Getters
       int getDebut() const {return i_debut;}
       int getFin() const {return i_fin;}
       int getDistance() const {return distance;}
       std::string getInfos() const {
        std::ostringstream texte;
            texte << "Route: " << i_debut << " - " << i_fin
                << " | Distance: " << distance << '\n';
            return texte.str();
        }

        void affiche() const {std::cout << "\t\tRoute\n " << "\n\t Start: " << i_debut << "\n\t End: " << i_fin << "\n\t Distance: " << distance << "\n";}
    
    private:
        int i_debut;
        int i_fin;
        int distance;


};

#endif