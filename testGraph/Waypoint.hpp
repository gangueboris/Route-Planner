#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class  Waypoint{
    public:
       // Constructor
       Waypoint() : nom(""), lon(0.0), lat(0.0) {} // Default constructor
        Waypoint(std::string nom, float lon = 0, float lat = 0) : nom(nom), lon(lon), lat(lat) {}
       
       // Destructor
       ~Waypoint(){}
       
       // Getters
       std::string getNom() const {return nom;}
       float getLongitude() const {return lon;}
       float getLatitude() const {return lat;}
       std::string getInfos() const {
            std::ostringstream texte;
            texte << "Waypoint: " << std::setprecision(2) << std::fixed 
                    << nom << "\n(" << lon << "," << lat << ")";
            return texte.str();
        }

        // Setters
        void setNom (std::string nom) {this->nom = nom;}
        void setLongitude (float lon) {this->lon = lon;}
        void setLatitude (float lat) {this->lat = lat;}

        void affiche() const {std::cout << "\tWayPoint: " << nom << "\n\t Longitude: " << lon << "\n\t Latitude: " << lat << "\n";}
         
        virtual bool isVille() const {return false;}
    
    private:
       std::string nom;
       float lon;
       float lat;
};

#endif