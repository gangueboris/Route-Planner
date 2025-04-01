// Includes VIEW
#include <QApplication>
#include <QMessageBox>
#include "view/LoginDialog.hpp"

// Includes MODEL
#include <cppconn/exception.h>
#include "model/Carte.hpp"
//#include "model/BDD.hpp"
//#include "model/SceneCarte.hpp"

// Include MAINWINDOW
#include "view/MainWindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    /*LoginDialog dlg;
    std::string host, base, user, pwd;
    
    if (!dlg.exec() ){ // Open the Dialog Box
    std::cout << "Sortie de l'application\n";
    return 1;
    }

    // Récupération des saisies après fermeture de la Dialog box
    dlg.getResult(host, base, user, pwd);
    std::cout << "Lecture base plans" << std::endl;
    */
    std::vector<Point> pointList;
    Contour contour_init(pointList);
    std::vector<Route> routes_init;
    std::vector<Ville> villes_init;
    std::vector<Waypoint> waypoints_init;

    Carte carte(contour_init, routes_init, villes_init, waypoints_init);

    /*try {
        // Connect to the database
        BDD bdd("tcp://localhost:3306", "plans", "architectUI", "admin1234");
        //BDD bdd("tcp://"+host+":3306", base, user, pwd);

        // Get the plan
        plan = bdd.getPlan(1);
        plan.affiche();

    } catch (sql::SQLException &e) {
        std::cout << "Erreur MySQL. Sortie de l'application\n";
        QMessageBox msg( QMessageBox::Critical, "Erreur mySQL", 
        e.what());
        msg.exec();
        return 1;
    }*/
    
    MainWindow mw(carte);
    mw.show();

    return app.exec();
 }
