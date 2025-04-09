#include "Graph.hpp"
#include <iostream>

// Function to find the index of a waypoint in the vector
int findWaypointIndex(const std::vector<Waypoint>& waypoints, const std::string& wp_name) {
    for (size_t i = 0; i < waypoints.size(); ++i) {
        if (waypoints[i].getNom() == wp_name) {
            return static_cast<int>(i);
        }
    }
    return -1; // Not found
}

std::vector<Route> createRoutes(const std::vector<Waypoint>& waypoints) {
    std::vector<Route> routes;

    struct RouteData {
        std::string nom_debut;
        std::string nom_fin;
        int distance;
    };

    std::vector<RouteData> routeData = {
        {"Ancenis", "Angers", 52}, {"Ancenis", "Nantes", 37}, {"Auray", "Hennebont", 29},
        {"Auray", "Vannes", 20}, {"Barrage de la Rance", "Dinard", 6}, {"Brest", "Guipavas Aéroport", 11},
        {"Brest", "Pont de l'Iroise", 9}, {"Caen", "Avranches", 101}, {"Carhaix", "Guingamp", 49},
        {"Carhaix", "Lorient", 74}, {"Chateaulin", "Carhaix", 46}, {"Chateaulin", "Quimper", 29},
        {"Cholet", "Porte des Sorinières", 59}, {"Daoulas", "Chateaulin", 28}, {"Dinan", "Echangeur de Tramain", 31},
        {"Dinan", "Mesnil Roc'h", 12}, {"Dinard", "Dinan", 21}, {"Echangeur de la Chesnaie", "Dinan", 20},
        {"Echangeur de la Chesnaie", "Pontorson", 33}, {"Echangeur de Tramain", "Lamballe", 12},
        {"Echangeur de Tramain", "Rennes", 69}, {"Fougères", "Pontaubault", 35}, {"Fougères", "Vitré", 29},
        {"Guingamp", "Morlaix", 52}, {"Guingamp", "Saint Brieuc", 33}, {"Guipavas Aéroport", "Morlaix", 53},
        {"Hennebont", "Lorient", 10}, {"Hennebont", "Ploermel", 76}, {"La Rochelle", "Marans", 27},
        {"Lamballe", "Yffiniac", 14}, {"Lannion", "Guingamp", 34}, {"Loudéac", "Carhaix", 66},
        {"Loudéac", "Lamballe", 43}, {"Loudéac", "Rennes", 92}, {"Loudéac", "Saint Brieuc", 44},
        {"Marans", "La Roche sur Yon", 59}, {"Mesnil Roc'h", "Echangeur de la Chesnaie", 13},
        {"Morlaix", "Carhaix", 46}, {"Morlaix", "Saint Michel-en-Grève", 26}, {"Paimpol", "Guingamp", 30},
        {"Paimpol", "Lannion", 33}, {"Ploermel", "Loudéac", 43}, {"Ploermel", "Rennes", 68},
        {"Pont de l'Iroise", "Daoulas", 15}, {"Pont de la Corde", "Morlaix", 14}, {"Pont de Saint Nazaire", "Saint Nazaire", 8},
        {"Pont du Morbihan", "Pontchateau", 20}, {"Pontaubault", "Avranches", 7}, {"Pontchateau", "Savenay", 16},
        {"Pontivy", "Hennebont", 45}, {"Pontivy", "Loudéac", 23}, {"Pontorson", "Pontaubault", 15},
        {"Pornic", "Pont de Saint Nazaire", 20}, {"Pornic", "Porte des Sorinières", 52}, {"Pornic", "Villeneuve-en-Retz", 15},
        {"Porte des Sorinières", "La Roche sur Yon", 66}, {"Porte des Sorinières", "Nantes", 9},
        {"Quimper", "Pont L'Abbé", 19}, {"Quimper", "Quimperlé", 47}, {"Quimperlé", "Lorient", 24},
        {"Redon", "Ploermel", 45}, {"Redon", "Pontchateau", 29}, {"Redon", "Rennes", 65},
        {"Rennes", "Fougères", 48}, {"Rennes", "Mesnil Roc'h", 44}, {"Rennes", "Nantes", 107},
        {"Saint Brieuc", "Paimpol", 43}, {"Saint Malo", "Barrage de la Rance", 8},
        {"Saint Malo", "Echangeur de la Chesnaie", 19}, {"Saint Michel-en-Grève", "Lannion", 11},
        {"Saint Nazaire", "Pontchateau", 24}, {"Saint Pol de Léon", "Pont de la Corde", 7},
        {"Saint Pol de Léon", "Roscoff", 6}, {"Savenay", "Nantes", 38}, {"Savenay", "Saint Nazaire", 26},
        {"Vannes", "Ploermel", 49}, {"Vannes", "Pont du Morbihan", 40}, {"Villeneuve-en-Retz", "La Roche sur Yon", 64},
        {"Vitré", "Laval", 35}, {"Vitré", "Rennes", 38}, {"Yffiniac", "Saint Brieuc", 9}
    };

    for (const auto& rd : routeData) {
        int i_debut = findWaypointIndex(waypoints, rd.nom_debut);
        int i_fin = findWaypointIndex(waypoints, rd.nom_fin);
        if (i_debut != -1 && i_fin != -1) {
            routes.emplace_back(i_debut, i_fin, rd.distance);
        } else {
            std::cerr << "Error: Waypoint not found for " << rd.nom_debut << " or " << rd.nom_fin << std::endl;
        }
    }

    return routes;
}



int main() {
    std::vector<Waypoint> waypoints = {
        {"Ancenis", -1.18194, 47.37333},
        {"Angers", -0.55417, 47.47361},
        {"Auray", -2.98139, 47.66861},
        {"Avranches", -1.35694, 48.68444},
        {"Barrage de la Rance", -2.02382, 48.61761},
        {"Brest", -4.48556, 48.39083},
        {"Caen", -0.37056, 49.18222},
        {"Carhaix", -3.56722, 48.27833},
        {"Chateaulin", -4.08861, 48.19750},
        {"Cholet", -0.87833, 47.06000},
        {"Daoulas", -4.25313, 48.36056},
        {"Dinan", -2.04889, 48.45639},
        {"Dinard", -2.06167, 48.63250},
        {"Echangeur de la Chesnaie", -1.92231, 48.54472},
        {"Echangeur de Tramain", -2.41352, 48.40410},
        {"Fougères", -1.19861, 48.35250},
        {"Guingamp", -3.15000, 48.56333},
        {"Guipavas Aéroport", -4.41592, 48.43875},
        {"Hennebont", -3.27653, 47.78866},
        {"La Roche sur Yon", -1.41861, 46.66944},
        {"La Rochelle", -1.15167, 46.15917},
        {"Lamballe", -2.51667, 48.46944},
        {"Lannion", -3.45417, 48.73333},
        {"Laval", -0.77000, 48.07278},
        {"Lorient", -3.36667, 47.75000},
        {"Loudéac", -2.75389, 48.17778},
        {"Marans", -0.98931, 46.30574},
        {"Mesnil Roc'h", -1.91368, 48.42840},
        {"Morlaix", -3.82667, 48.57833},
        {"Nantes", -1.55278, 47.21806},
        {"Paimpol", -3.04528, 48.77861},
        {"Ploermel", -2.39611, 47.93250},
        {"Pont de l'Iroise", -4.39767, 48.38715},
        {"Pont de la Corde", -3.95143, 48.64445},
        {"Pont de Saint Nazaire", -2.17036, 47.28622},
        {"Pont du Morbihan", -2.30062, 47.53159},
        {"Pont L'Abbé", -4.22194, 47.86806},
        {"Pontaubault", -1.33974, 48.62902},
        {"Pontchateau", -2.09457, 47.43925},
        {"Pontivy", -2.96139, 48.06917},
        {"Pontorson", -1.51062, 48.56241},
        {"Pornic", -2.10000, 47.11667},
        {"Porte des Sorinières", -1.51440, 47.17244},
        {"Quimper", -4.09639, 47.99667},
        {"Quimperlé", -3.54861, 47.87361},
        {"Redon", -2.08361, 47.65222},
        {"Rennes", -1.67944, 48.11472},
        {"Roscoff", -3.98444, 48.72722},
        {"Saint Brieuc", -2.76528, 48.51361},
        {"Saint Malo", -2.00889, 48.64722},
        {"Saint Michel-en-Grève", -3.56386, 48.68399},
        {"Saint Nazaire", -2.20861, 47.28056},
        {"Saint Pol de Léon", -3.98500, 48.68611},
        {"Savenay", -1.92691, 47.37072},
        {"Vannes", -2.76028, 47.65583},
        {"Villeneuve-en-Retz", -1.94407, 47.03984},
        {"Vitré", -1.21000, 48.12000},
        {"Yffiniac", -2.68006, 48.48039}
    };
    
     
    std::vector<Route> routes = createRoutes(waypoints);

    //std::cout << waypoints.size() << '\n';
    Graph graph(waypoints, routes);

    Waypoint start("Brest");
    Waypoint end("Angers");

    std::vector<int> path = graph.getShortestPath(start, end);
    graph.visualizePath(path);

    //std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjacencyList = graph.getAdjacencyList();
    //graph.adjacencyListToEdgeListFile(adjacencyList, "edgeList.txt");

    return 0;
}


/*
- 
*/