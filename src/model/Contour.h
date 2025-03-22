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
 #include "Point.h"
 #include "BDD.h"
 
 class Contour {
     public :
         /*Destructor and Constructor*/
         Contour();
         ~Contour(){};
 
         /*Member Function*/
         std::vector<Point> getPoints();
         void ajoutUnPoint(Point p);
     
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 #endif;