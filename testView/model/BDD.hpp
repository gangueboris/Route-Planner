#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "Carte.hpp"

class BDD {
	public :
		/*Constructor and Destructor*/
		BDD (std::string host, std::string nomBDD, std::string login, std::string pwd);
		~BDD();

		/*Member Function*/
		void readContourFromDb(Contour &Contour);
		void readRouteFromDb(std::vector<Route> & route, std::vector<Waypoint>& waypoints);
		int findWaypointIndex(const std::string& wp_name, std::vector<Waypoint>& waypoints);
		void readVilleFromDb(std::vector<Ville> & ville);
		void readWaypointsFromDb(std::vector<Waypoint>& waypoint);
		Carte getCarte(){return carte;}

	private :
		sql::Connection *con;
		Carte carte;
};
#endif
