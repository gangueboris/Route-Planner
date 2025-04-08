#include "BDD.hpp"

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

BDD::~BDD(){
	std::cout << "Fermeture connection\n";
	delete con;
}

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

