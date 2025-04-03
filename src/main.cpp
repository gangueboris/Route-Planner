#include <iostream>

/*===Include of project===*/
#include "model/BDD.hpp"
#include "model/Carte.hpp"
#include "model/Contour.hpp"
#include "model/Graph.hpp"
#include "model/Point.hpp"
#include "model/Route.hpp"
#include "model/Ville.hpp"
#include "model/Waypoint.hpp"

int main (){
    std::string host, base, user, pwd;
    host = "localhost";
    base = "routeplanner";
    user = "routePlanner";
    pwd = "azerty1234";
    try {
        BDD("tcp://"+host+":3306",base,user,pwd);
    }
    catch (sql::SQLException &e){
        std::cout << "Erreur MYSQL, sortie du programme\n";
        return 1;
    }


    return 0;
}