#include "BDD.hpp"

BDD::BDD ( std::string host, std::string nomBDD, std::string login, std::string pwd){
		/* Create a connection */
		sql::Driver *driver = get_driver_instance();
		con = driver->connect(host, login, pwd);

		/* Connect to the MySQL database */
		con->setSchema(nomBDD);

		setlocale(LC_ALL,"C");
		
		Contour contour(contour);
		std::vector<Waypoint> waypoints;
		std::vector<Route> routes;
		std::vector<Ville> villes;

		
		readContourFromDb(contour);
		readWaypointsFromDb(waypoints);
		readVilleFromDb(villes);
		readRouteFromDb(routes);



		this->carte = Carte(contour, routes, villes, waypoints);
}

BDD::~BDD(){
	std::cout << "Fermeture connection\n";
	delete con;
}

void BDD::readContourFromDb(Contour &Contour){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT num_pt, lat, lon FROM contour");
	

	while(res->next()){ /*when all the lines are read return FALSE and stops*/
		int num_pt = res->getInt("num_pt");
		float lat = res->getDouble("lat");
		float lon = res->getDouble("lon");
		Contour.getPoints().push_back(Point(num_pt,lat,lon));
	}
};

void BDD::readRouteFromDb(std::vector<Route> & route){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom_debut, nom_fin, distance FROM route");
	

	while(res->next()){ /*when all the lines are read return FALSE and stops*/
		std:: string num_debut = res->getString("nom_debut");
		std:: string nom_fin = res->getString("nom_fin");
		int distance = res->getInt("distance");
		route.push_back(Route(num_debut,nom_fin,distance));
	}
};

void BDD::readVilleFromDb(std::vector<Ville> & ville){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT code_postal, nb_habitants, site FROM ville");
	

	while(res->next()){ /*when all the lines are read return FALSE and stops*/
		std::string code_postal = res->getString("code_postal");
		int nb_habitants = res->getInt("nb_habitants");
		std:: string site = res->getString("site");
		ville.push_back(Ville(code_postal,nb_habitants,site));
	}
};

void BDD::readWaypointsFromDb(std::vector<Waypoint> & waypoint){
	
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res = stmt->executeQuery("SELECT nom,lat, lon FROM waypoint");
	

	while(res->next()){ /*when all the lines are read return FALSE and stops*/
		std::string nom = res->getString("nom");
		int lat = res->getInt("lat");
		int lon = res->getInt("lon");
		waypoint.push_back(Waypoint(nom,lat,lon));
	}
};

