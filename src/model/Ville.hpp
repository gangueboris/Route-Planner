#ifndef _VILLE_H_
#define _VILLE_H_

#include "WayPoint.hpp"

#include <string>
#include <iostream>

class Ville : public Waypoint {
    public:
       // Constructor
       Ville();
       
       // Destructor
       ~Ville(){};
       
       // Getters
        std::string getSite() const {return site;}

        std::string getInfos() const {
            std::ostringstream texte;
            texte << "Site: " << site << " | Code postal: " << code_postal << " | Nb habitants: " << nb_habitants;
            return texte.str();
        }

        // Display relevent informations about the 'ville'
        void affiche() const {std::cout << "\tCode postal: " << code_postal << "\n\t Site: " << site << "\n\t nb_habitants: " << nb_habitants << "\n";}
       
    private:
       std::string code_postal;
       std::string site;
       int nb_habitants;

}; 

#endif