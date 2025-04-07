/**
 * @class Contour
 * @brief Contains all the points of the map
 * 
 * This class allows to add another point
 * 
 * @author Gaspard Vieujean
 * @date March 21, 2025
 */

 #ifndef CONTOUR_H
 #define CONTOUR_H
 
 #include <iostream>
 #include <string>
 #include <iomanip>
 #include <sstream>
 #include <vector>
 #include "Point.hpp"
 //#include "BDD.hpp"
 
 class Contour {
    public :
         /*Destructor and Constructor*/
         Contour(std::vector<Point> contour_init): contour{contour_init}{}
         Contour() {}
         ~Contour(){};
 
         /*Member Function*/
         std::vector<Point> getPoints(){return contour;}
         void ajoutUnPoint(Point p);

    private : 
        std::vector<Point> contour;

     
 };
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 #endif