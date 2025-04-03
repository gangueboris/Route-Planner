// Includes VIEW
#include <QApplication>
#include <QMessageBox>
#include "view/LoginDialog.hpp"

// Includes MODEL
#include <cppconn/exception.h>
#include "model/Carte.hpp"
#include "model/BDD.hpp"
#include "model/SceneCarte.hpp"

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
    std::cout << "Lecture " << std::endl;*/
    Carte carte;

    try {
        // Connect to the database
        BDD bdd("tcp://localhost:3306", "routeplanner", "routePlanner", "azerty1234");
        //BDD bdd("tcp://"+host+":3306", base, user, pwd);

        // Get the Carte
        carte = bdd.getCarte();
    
        std::cout << "Successfully get the map !! \n";

    } catch (sql::SQLException &e) {
        std::cout << "Erreur MySQL. Sortie de l'application\n";
        QMessageBox msg( QMessageBox::Critical, "Erreur mySQL", 
        e.what());
        msg.exec();
        return 1;
    }
    
    MainWindow mw(carte);
    mw.show();

    return app.exec();
 }
