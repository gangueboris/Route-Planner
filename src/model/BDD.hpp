*#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "Point.hpp"
#include "Carte.hpp"
#include "Contour.hpp"
#include "Ville.hpp"
#include "Route.hpp"
#include "Point.hpp"

class BDD {
	public :
		/*Constructor and Destructor*/
		BDD (std::string host, std::string nomBDD, std::string login, std::string pwd);
		~BDD();

		/*Member Function*/
		void readContourFromDb(Contour &Contour);
		//void readRouteFromDb(std::vector<Route> & route);
		void readVilleFromDb(std::vector<Ville> & ville);
		void readWaypointsFromDb(std::vector<Waypoint> & waypoint);
		//Carte getCarte(){return carte;};

	private :
		sql::Connection *con;
		Carte carte;
};
#endif
