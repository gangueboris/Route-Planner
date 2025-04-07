#ifndef _VILLE_H_
#define _VILLE_H_

#include "Waypoint.hpp"

#include <string>
#include <iostream>
#include <sstream>

class Ville : public Waypoint {
    public:
       // Constructor
        Ville(std::string nom_init = "", std::string code_postal_init = "", int nb_habitants_init = 0, std::string site_init = "", float lon = 0.0, float lat = 0.0)
        : Waypoint(nom_init, lon, lat),nom(nom_init), code_postal(code_postal_init), nb_habitants(nb_habitants_init), site(site_init) {}
     
       
       // Destructor
       ~Ville(){}
       
       // Getters
        std::string getSite() const {return site;}

        std::string getInfos() const {
            std::ostringstream texte;
            texte << "Nom: " << nom << '\n' << "Code postal: " << code_postal << '\n' << "Nb habitants: " << nb_habitants << '\n' << "Site: " << site;
            return texte.str();
        }

        // Display relevent informations about the 'ville'
        void affiche() const {std::cout << "\tCode postal: " << code_postal << "\n\t Site: " << site << "\n\t nb_habitants: " << nb_habitants << "\n";}
       
    private:
       std::string nom;
       std::string code_postal;
       std::string site;
       int nb_habitants;

}; 

#endif