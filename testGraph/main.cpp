# include "Graph.hpp"
#include <iostream>

int main() {
    const std::vector<Waypoint> testWaypoints = {
        {"Ancenis", 47.37333, -1.18194},
        {"Angers", 47.47361, -0.55417},
        {"Auray", 47.66861, -2.98139},
        {"Avranches", 48.68444, -1.35694},
        {"Barrage de la Rance", 48.61761, -2.02382},
        {"Brest", 48.39083, -4.48556},
        {"Caen", 49.18222, -0.37056},
        {"Carhaix", 48.27833, -3.56722},
        {"Chateaulin", 48.19750, -4.08861},
        {"Cholet", 47.06000, -0.87833},
        {"Daoulas", 48.36056, -4.25313},
        {"Dinan", 48.45639, -2.04889},
        {"Dinard", 48.63250, -2.06167},
        {"Echangeur de la Chesnaie", 48.54472, -1.92231},
        {"Echangeur de Tramain", 48.40410, -2.41352},
        {"Fougères", 48.35250, -1.19861},
        {"Guingamp", 48.56333, -3.15000},
        {"Guipavas Aéroport", 48.43875, -4.41592},
        {"Hennebont", 47.78866, -3.27653},
        {"La Roche sur Yon", 46.66944, -1.41861},
        {"La Rochelle", 46.15917, -1.15167},
        {"Lamballe", 48.46944, -2.51667},
        {"Lannion", 48.73333, -3.45417},
        {"Laval", 48.07278, -0.77000},
        {"Lorient", 47.75000, -3.36667},
        {"Loudéac", 48.17778, -2.75389},
        {"Marans", 46.30574, -0.98931},
        {"Mesnil Roc'h", 48.42840, -1.91368},
        {"Morlaix", 48.57833, -3.82667},
        {"Nantes", 47.21806, -1.55278},
        {"Paimpol", 48.77861, -3.04528},
        {"Ploermel", 47.93250, -2.39611},
        {"Pont de l'Iroise", 48.38715, -4.39767},
        {"Pont de la Corde", 48.64445, -3.95143},
        {"Pont de Saint Nazaire", 47.28622, -2.17036},
        {"Pont du Morbihan", 47.53159, -2.30062},
        {"Pont L'Abbé", 47.86806, -4.22194},
        {"Pontaubault", 48.62902, -1.33974},
        {"Pontchateau", 47.43925, -2.09457},
        {"Pontivy", 48.06917, -2.96139},
        {"Pontorson", 48.56241, -1.51062},
        {"Pornic", 47.11667, -2.10000},
        {"Porte des Sorinières", 47.17244, -1.51440},
        {"Quimper", 47.99667, -4.09639},
        {"Quimperlé", 47.87361, -3.54861},
        {"Redon", 47.65222, -2.08361},
        {"Rennes", 48.11472, -1.67944},
        {"Roscoff", 48.72722, -3.98444},
        {"Saint Brieuc", 48.51361, -2.76528},
        {"Saint Malo", 48.64722, -2.00889},
        {"Saint Michel-en-Grève", 48.68399, -3.56386},
        {"Saint Pol de Léon", 48.68611, -3.98500},
        {"Savenay", 47.37072, -1.92691},
        {"Vannes", 47.65583, -2.76028},
        {"Villeneuve-en-Retz", 47.03984, -1.94407},
        {"Vitré", 48.12000, -1.21000},
        {"Yffiniac", 48.48039, -2.68006}
    };
    
    // init the Graph
    Graph graph(testWaypoints);

    // ====================== Test of Create Adjacency List ====================
    /*std::unordered_map<std::string, std::string> adjacencyList = graph.createAdjacencyList();
    for (auto& adj : adjacencyList) {
        std::cout << adj.first << ", " << adj.second << "\n";
    }
    */

    // ====================== Test of Djisktra algorithm ====================
    std::pair<std::vector<std::string>, int> shortPath = graph.getShortestPath("Brest", "Marans");
    std::cout << shortPath.second << "\n\n";
    for(auto& city : shortPath.first) {
        std::cout << city << "\n\n";
    }

   

    return 0;
}