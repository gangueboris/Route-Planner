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
		readRouteFromDb(routes,waypoints);
		for(auto &elem : routes){
			std::cout << elem.getInfos() << std::endl;
		}


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


};


void BDD::readWaypointsFromDb(std::vector<Waypoint> & waypoint){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom,lat, lon FROM waypoint");
	

	while(res->next()){ 
		std::string nom = res->getString("nom");
		int lat = res->getInt("lat");
		int lon = res->getInt("lon");
		waypoint.push_back(Waypoint(nom,lat,lon));
	}
};

void BDD::readVilleFromDb(std::vector<Ville> & ville){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom, code_postal, nb_habitants, site FROM ville");

	while(res->next()){ 
		std::string nom = res->getString("nom");
		std::string code_postal = res->getString("code_postal");
		int nb_habitants = res->getInt("nb_habitants");
		std:: string site = res->getString("site");

		/*
		   - SELECT lon, lat FROM waypoint WHERE nom = nom_ville;
		
		   - ville.push_back(Ville(nom, code_postal, nb_habitants, site, lon, lat)); // New ville initialisation
		*/
	
		ville.push_back(Ville(nom,code_postal,site,nb_habitants));
	}
};

void BDD::readRouteFromDb(std::vector<Route> & route, std::vector<Waypoint> &waypoints){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom_debut, nom_fin, distance FROM route");
	

	while(res->next()){ 
		std:: string nom_debut = res->getString("nom_debut");
		std:: string nom_fin = res->getString("nom_fin");
		int distance = res->getInt("distance");
		int index_debut = findRouteIndex(nom_debut,waypoints);
		int index_fin = findRouteIndex(nom_fin, waypoints);
		route.push_back(Route(index_debut,index_fin,distance));
	}
};


int BDD::findRouteIndex(std::string nom, std::vector<Waypoint> &waypoints){
	int index = -1;
	for (int i = 0;i<static_cast<int> (waypoints.size());i++){
		if(waypoints[i].getNom() == nom){
			index = i;
			break;
		}
	}
	return index;
}



