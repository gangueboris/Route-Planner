#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "Point.h"

class BDD {
	public :
		/*Constructor and Destructor*/
		BDD ( std::string host, std::string nomBDD, std::string login, std::string pwd);
		~BDD();

		/*Member Function*/
		void getPointsBDD(std::vector<Point> points);


		/*Plan selectPlan(int id);
		void ajouterMurs(Plan &plan);
		void ajouterPoints(Mur &mur);
		Plan getPlan(int id);
		void inserePlan(Plan &plan);*/

	private :
		sql::Connection *con;
};
#endif
