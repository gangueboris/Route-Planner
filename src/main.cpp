#include <iostream>
#include <QApplication>
#include <QMessageBox>

/*===Include of project===*/
#include "model/BDD.hpp"
#include "model/Carte.hpp"
#include "model/Contour.hpp"
#include "model/Graph.hpp"
#include "model/Point.hpp"
#include "model/Route.hpp"
#include "model/Ville.hpp"
#include "model/Waypoint.hpp"
#include "view/LoginDialog.hpp"

int main (int argc, char **argv){
    QApplication app(argc,argv);
    LoginDialog dlg;
    std::string host, base, user, pwd;


    if(!dlg.exec()){
        std::cout << "Sortie de l'application\n";
        return 1;
    }

    //Récupération des saisies après fermeture de la Dialog box
    dlg.getResult(host, base, user, pwd);
    std::cout << "Lecture base routeplanner" << std::endl;
    Carte carte;

    /*host = "localhost";
    base = "routeplanner";
    user = "routePlanner";
    pwd = "azerty1234";*/

    try {
        BDD BDD("tcp://"+host+":3306",base,user,pwd);
        carte = BDD.getCarte();
       return 1;
    }
    catch (sql::SQLException &e){
        std::cout << "Erreur MYSQL, sortie du programme\n";
        QMessageBox msg(QMessageBox::Critical, "Erreur mySQL", e.what());
        msg.exec();
        return 1;
    }


    return app.exec();
}