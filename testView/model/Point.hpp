/**
 * @class Point
 * @brief Contains a number of points
 * 
 * This class allows getting lat and lon from a point
 * 
 * @author Gaspard Vieujean
 * @date March 21, 2025
 */

 #ifndef POINT_H
 #define POINT_H
 
 #include <iostream>
 #include <string>
 #include <iomanip>
 #include <sstream>
 
 class Point {
	 public :
		 //Constructor and Destructor
		 Point (int init_num, float init_lat, float init_lon): num{init_num}, lat{init_lat}, lon{init_lon} {}
		 Point(){}
		 ~Point (){};
 
		 //Member fonction
		 float getLon(){return lon;};
		 float getLat(){return lat;};
	 private :
		 int num;
		 float lat;
		 float lon;
 
 };
 #endif
 