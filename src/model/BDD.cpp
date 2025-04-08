#include "BDD.hpp"

/**
 * @brief Get informations of the DB
 * 
 * @param host The host where the DB is
 * @param nomBDD name of the DB
 * @param login user 
 * @param pwd password
 * 
 * constructor of the Class BDD
 */
BDD::BDD (std::string host, std::string nomBDD, std::string login, std::string pwd) {
		/* Create a connection */
		sql::Driver *driver = get_driver_instance();
		con = driver->connect(host, login, pwd);

		/* Connect to the MySQL database */
		con->setSchema(nomBDD);
		setlocale(LC_ALL,"C");

		std::vector<Point> points;
		Contour contour(points);
		std::vector<Waypoint> waypoints;
		std::vector<Route> routes;
		std::vector<Ville> villes;

		readContourFromDb(contour);
		readWaypointsFromDb(waypoints);
		readVilleFromDb(villes);
		readRouteFromDb(routes, waypoints);

		this->carte = Carte(contour,routes,villes,waypoints);
}

/**
 * @brief Destructor of the class BDD
 */
BDD::~BDD(){
	std::cout << "Fermeture connection\n";
	delete con;
}

/**
 * @brief Get the points of the DB to put them into the Contour
 * 
 * @param contour contour that has a vector<Point>
 * @return void
 */
void BDD::readContourFromDb(Contour &contour){
	
	std::vector<Point> points;
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT num_pt, lat, lon FROM contour");
	

	while(res->next()){ 
		int num_pt = res->getInt("num_pt");
		float lat = res->getDouble("lat");
		float lon = res->getDouble("lon");
		points.push_back(Point(num_pt,lat,lon));
	}
    contour = Contour(points);
}

/**
 * @brief Get the waypoints form the DB
 * 
 * @param waypoint vector of Waypoint
 * @return void
 */
void BDD::readWaypointsFromDb(std::vector<Waypoint> & waypoint){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom,lat, lon FROM waypoint");
	

	while(res->next()){ 
		std::string nom = res->getString("nom");
		float lat = res->getDouble("lat");
		float lon = res->getDouble("lon");
		waypoint.push_back(Waypoint(nom,lon,lat));
	}
}

/**
 * @brief Get the villes from the DB containing all the informations about it
 * 
 * @param ville vector of ville
 * @return void
 */
void BDD::readVilleFromDb(std::vector<Ville>& ville) {
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom, code_postal, nb_habitants, site FROM ville");

	while(res->next()) { 
		std::string nom_ville = res->getString("nom");
		std::string code_postal = res->getString("code_postal");
		int nb_habitants = res->getInt("nb_habitants");
		std:: string site = res->getString("site");
        
		// Get lon and lat from db
		sql::PreparedStatement* pstmt = con->prepareStatement("SELECT lat, lon FROM waypoint WHERE nom = ?");
		pstmt->setString(1, nom_ville); // Bind the nom_ville value to the placeholder
		sql::ResultSet* res2 = pstmt->executeQuery();
		
		float lon, lat;
		if (res2->next()) { 
			lat = res2->getDouble("lat");
			lon = res2->getDouble("lon");
		} else {
			std::cout << "No results found.\n";
		}
		ville.push_back(Ville(nom_ville, code_postal, nb_habitants, site, lon, lat)); // New ville initialisation
	}
}

/**
 * @brief Get all the routes from the DB
 * 
 * @param route vector of route
 * @param waypoints vector of waypoint
 * @return void
 * 
 * Basically we implement the 2 param because the informations in the DB is not what we need in the project
 * 
 */
void BDD::readRouteFromDb(std::vector<Route>& route, std::vector<Waypoint>& waypoints){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom_debut, nom_fin, distance FROM route");
	

	while(res->next()){ 
		std:: string num_debut = res->getString("nom_debut");
		std:: string nom_fin = res->getString("nom_fin");
		int distance = res->getInt("distance");
		
		int i_debut = this->findRouteIndex(num_debut, waypoints);
		int i_fin = this->findRouteIndex(nom_fin, waypoints);
        
		route.push_back(Route(i_debut, i_fin, distance));
	}
}


/**
 * @brief Get a certain index corresponding for the route threw the waypoint
 * 
 * @param nom name of the route
 * @param waypoints vector of waypoint
 * 
 * @return the index of the route
 * 
 * This function is there to get the index of a route by comparing the name and the waypoint with the same name
 */
int BDD::findRouteIndex(std::string nom, std::vector<Waypoint> &waypoints) {
	int index = -1;
	for (int i = 0;i<static_cast<int> (waypoints.size());i++) {
		if(waypoints[i].getNom() == nom){
			index = i;
			break;
		}
	}
	return index;
}

