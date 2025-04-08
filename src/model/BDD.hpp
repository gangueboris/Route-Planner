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

/**
 * @class BDD
 * @brief Collects information from a DB
 *
 * This allows to get all the informations from a DB
 * It also contains a method that can get the index of a route 
 *
 * @author Gaspard Vieujean
 * @date April 1, 2025
 */
class BDD {
	public :
		/*Constructor and Destructor*/
		BDD (std::string host, std::string nomBDD, std::string login, std::string pwd);
		~BDD();

		/*Member Function*/
		void readContourFromDb(Contour &Contour);
		void readRouteFromDb(std::vector<Route> & route, std::vector<Waypoint> &waypoints);
		void readVilleFromDb(std::vector<Ville> & ville);
		void readWaypointsFromDb(std::vector<Waypoint> & waypoint);
		Carte getCarte(){return carte;};

	private :
		sql::Connection *con;
		Carte carte;
		int findRouteIndex(std::string nom, std::vector<Waypoint> &waypoints);
};
#endif
